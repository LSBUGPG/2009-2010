#include "invader.h"

#include <stdio.h>
#include "object.h"
#include "graphics.h"
#include "game.h"
#include "laser.h"
#include "audio.h"
#include "score.h"

const int INVADER_TYPES = 3;
const int INVADER_FRAMES = 2;
const int INVADER_WIDTH = 16;
const int INVADER_HEIGHT = 8;
const int INVADER_START_X = PLAY_FIELD_LEFT + INVADER_WIDTH;
const int INVADER_START_Y = PLAY_FIELD_BOTTOM + INVADER_HEIGHT * 16;

struct InvaderType
{
	Image image[INVADER_FRAMES];
	int points;
};

struct Bomb;

Bomb *get_bomb(void);

const int BOMB_WIDTH = 4;
const int BOMB_HEIGHT = 8;
const int BOMB_SPEED = 2;
const int BOMB_FRAMES = 2;

Image bomb_image[BOMB_FRAMES];

struct Bomb: public Object
{
	int position[2];
	int step;
	bool alive;

	void update(void)
	{
		if (alive)
		{
			step++;
			position[1] -= BOMB_SPEED;
			if (position[1] < PLAY_FIELD_BOTTOM)
			{
				alive = false;
			}

			int size[] = { BOMB_WIDTH / 2, BOMB_HEIGHT / 2 };
			if (collide_laser(position, size))
			{
				alive = false;
			}
		}
	}

	void draw(void)
	{
		GLfloat fpos[2] = { GLfloat(position[0]), GLfloat(position[1]) };
		if (alive)
		{
			::draw(bomb_image[((step / 3) % 2)], fpos);
		}
	}
};

void reset_invaders(void);

const int INVADER_BEATS = 4;

struct Commander: public Object
{
	Mix_Chunk *beat[INVADER_BEATS];
	int order_given;	// invader given an order this frame
	int last_order;		// invader we gave an order to last frame
	int last_request;	// last invader that requested an order
	int first_request;	// first invader to request an order
	bool edge;
	bool win;
	bool descend;
	int direction;
	int step;
	int count;
	int time;

	Commander()
	{
		for (int i = 0; i < INVADER_BEATS; i++)
		{
			beat[i] = 0;
		}
		reset();
	}

	void reset(void)
	{
		// -1 is used as an unset value
		last_order    = -1;
		order_given   = -1;
		last_request  = -1;
		first_request = -1;
		direction = 1;
		edge = false;
		descend = false;
		win = false;
		step = 0;
		count = 0;
		time = 0;
	}

	void update(void)
	{
		int freq = 5 + (count * 50) / (INVADER_ROWS * INVADER_COLUMNS);
		count = 0;
		time++;
		if (time > freq)
		{
			time = 0;
			play_sound(beat[step % INVADER_BEATS]);
			step++;
		}

		if (win || last_request == -1)
		{
			reset_invaders();
			reset();
		}

		if (order_given == last_request)
		{
			last_order = -1;
			if (descend)
			{
				descend = false;
				direction *= -1;
			}
			else if (edge)
			{
				edge = false;
				descend = true;
			}
		}
		else
		{
			last_order = order_given;
		}

		order_given   = -1;
		last_request  = -1;
		first_request = -1;
	}

	bool order(int number, int move[])
	{
		count++;
		last_request = number;
		if (first_request == -1)
		{
			first_request = number;
		}

		if (order_given == -1 && number > last_order)
		{
			order_given = number;
			if (descend)
			{
				move[0] = 0;
				move[1] = -INVADER_HEIGHT;
			}
			else
			{
				move[0] = direction * (INVADER_WIDTH / 8);
				move[1] = 0;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	
	void finished_move(void)
	{
		edge = true;
	}

	void landed(void)
	{
		win = true;
	}

	void draw(void) {}
};

Mix_Chunk *invader_hit = NULL;

struct Invader: public Object
{
	const InvaderType *type;
	Commander *commander;
	int position[2];
	int step;
	bool alive;
	bool can_shoot;
	int number;

	void update(void)
	{
		int move[2];
		if (alive && commander->order(number, move))
		{
			step = (step + 1) % INVADER_FRAMES;
			position[0] += move[0];
			position[1] += move[1];

			if (move[0] != 0)
			{
				const GLfloat LEFT_MARGIN  = PLAY_FIELD_LEFT  + INVADER_WIDTH;
				const GLfloat RIGHT_MARGIN = PLAY_FIELD_RIGHT - INVADER_WIDTH;

				if (position[0] < LEFT_MARGIN || position[0] > RIGHT_MARGIN)
				{
					commander->finished_move();
				}
			}

			if (move[1] != 0)
			{
				if (position[1] <= PLAY_FIELD_BOTTOM + INVADER_HEIGHT)
				{
					commander->landed();
					laser_invaded();
				}
			}

			if (can_shoot && (rand() % 10) == 0)
			{
				Bomb *bomb = get_bomb();
				if (bomb)
				{
					bomb->position[0] = position[0];
					bomb->position[1] = position[1];
					bomb->alive = true;
					bomb->step = 0;
				}
			}
		}
	}

	void draw(void)
	{
		if (alive)
		{
			GLfloat fpos[2] = { GLfloat(position[0]), GLfloat(position[1]) };
			::draw(type->image[step], fpos);
		}
	}

	void hit(void)
	{
		add_points(type->points);
		play_sound(invader_hit);
		alive = false;
	}
};

InvaderType invader_type_array[INVADER_TYPES];
Invader invader_array[INVADER_ROWS][INVADER_COLUMNS];
Bomb bomb_array[INVADER_SHOTS];
Commander commander;

int load_invaders(Object *object_array[])
{
	char filename[] = "type??.bmp";
	int i;
	for (i = 0; i < INVADER_BEATS; i++)
	{
		sprintf_s(filename, sizeof(filename), "walk%d.wav", i);
		load_audio(commander.beat[i], filename);
	}

	*object_array = &commander;
	object_array++;

	int j;
	for (i = 0; i < INVADER_TYPES; i++)
	{
		for (j = 0; j < INVADER_FRAMES; j++)
		{
			sprintf_s(filename, sizeof(filename), "type%d%d.bmp", i, j);
			load_texture(invader_type_array[i].image[j].texture, filename);
			invader_type_array[i].image[j].dimension[0] = INVADER_WIDTH / 2.0f;
			invader_type_array[i].image[j].dimension[1] = INVADER_HEIGHT / 2.0f;
		}
		invader_type_array[i].points = (i + 1) * 10;
	}

	load_audio(invader_hit, "hit.wav");

	int number = 0;
	int formation[] = { 0, 0, 1, 1, 2 };
	for (i = 0; i < INVADER_ROWS; i++)
	{
		for (j = 0; j < INVADER_COLUMNS; j++)
		{
			Invader *invader = &invader_array[i][j];
			invader->type = &invader_type_array[formation[i]];
			invader->number = number;
			invader->commander = &commander;

			*object_array = invader;
			object_array++;
			number++;
		}
	}

	for (i = 0; i < BOMB_FRAMES; i++)
	{
		sprintf_s(filename, sizeof(filename), "bomb%d.bmp", i);
		load_texture(bomb_image[i].texture, filename);
		bomb_image[i].dimension[0] = BOMB_WIDTH / 2;
		bomb_image[i].dimension[1] = BOMB_HEIGHT / 2;
	}

	for (i = 0; i < INVADER_SHOTS; i++)
	{
		Bomb *bomb = &bomb_array[i];
		bomb->alive = false;
		bomb->position[0] = PLAY_FIELD_LEFT;
		bomb->position[1] = PLAY_FIELD_BOTTOM;
		
		*object_array = bomb;
		object_array++;
	}

	return INVADER_TOTAL;
}

void reset_invaders(void)
{
	for (int i = 0; i < INVADER_ROWS; i++)
	{
		for (int j = 0; j < INVADER_COLUMNS; j++)
		{
			Invader *invader = &invader_array[i][j];
			invader->position[0] = INVADER_START_X + j * INVADER_WIDTH;
			invader->position[1] = INVADER_START_Y + i * INVADER_HEIGHT * 2;
			invader->alive = true;
			invader->can_shoot = (i == 0);
			invader->step = 0;
		}
	}
}

bool collide_invaders(int position[], int size[])
{
	bool hit = false;

	for (int i = 0; i < INVADER_ROWS && !hit; i++)
	{
		for (int j = 0; j < INVADER_COLUMNS && !hit; j++)
		{
			Invader *invader = &invader_array[i][j];
			if (invader->alive)
			{
				if (position[0] - size[0] >= invader->position[0] - INVADER_WIDTH  / 2 &&
					position[0] + size[0] <= invader->position[0] + INVADER_WIDTH  / 2 &&
					position[1] - size[1] >= invader->position[1] - INVADER_HEIGHT / 2 &&
					position[1] + size[1] <= invader->position[1] + INVADER_HEIGHT / 2)
				{
					invader->hit();
					hit = true;
					
					// find a living invader above the one that we hit
					for (i = i + 1; i < INVADER_ROWS; i++)
					{
						invader = &invader_array[i][j];
						if (invader->alive)
						{
							invader->can_shoot = true;
							break;
						}
					}
				}
			}
		}
	}

	return hit;
}

Bomb *get_bomb(void)
{
	Bomb *bomb = 0;

	for (int i = 0; i < INVADER_SHOTS; i++)
	{
		if (!bomb_array[i].alive)
		{
			bomb = &bomb_array[i];
			break;
		}
	}

	return bomb;
}