#include <windows.h>
#include <SDL.h>
#include <math.h>

#include "graphics.h"
#include "audio.h"
#include "score.h"

struct Object
{
	virtual void update(GLfloat t) = 0;
	virtual void draw(void) = 0;
};

struct Table: public Object
{
	void update(GLfloat t);
	void draw(void);
	Image image;
	GLfloat position[2];
};

struct Ball: public Object
{
	void update(GLfloat t);
	void draw(void);
	Image image;
	GLfloat position[2];
	GLfloat velocity[2];
	GLfloat radius;
	Mix_Chunk *sound;
};

struct Paddle: public Object
{
	void update(GLfloat t);
	void draw(void);
	GLfloat position[2];
	GLfloat charge;
	GLfloat side;   // -1 is left, +1 is right
	Mix_Chunk *sound;
	int score;
	bool serving;
};

bool pause = true;
bool frame_advance = false;
bool reset_game = true;
GLfloat wait = 1.0f;
Ball ball;
Paddle left, right;
Table table;
Paddle *server = &left;
Paddle *receiver = &right;
GLfloat bounce_side = 0.0f;

Paddle *swap(Paddle *paddle)
{
	if (paddle == &left)
	{
		paddle = &right;
	}
	else
	{
		paddle = &left;
	}

	return paddle;
}

void serve(Ball &ball)
{
	if (server == &left)
	{
		server = &right;
		receiver = &left;
	}
	else
	{
		server = &left;
		receiver = &right;
	}

	server->serving = true;
	wait = 1.0f;
	reset_game = true;
	pause = true;
}

void hit_ball(Paddle &paddle, Ball &ball, bool charge)
{
	GLfloat ball_side = 0.0f;

	if (ball.position[0] < -ball.radius * 2.0f && 
		(paddle.serving || ball.velocity[0] < 0.0f))
	{
		ball_side = -1.0f;
	}
	else if (ball.position[0] > ball.radius * 2.0f && 
		     (paddle.serving || ball.velocity[0] > 0.0f))
	{
		ball_side = 1.0f;
	}

	if (ball_side == paddle.side && wait == 0.0f)
	{
		if (charge)
		{
			pause = false; // start service
		}
		else if (paddle.charge > 0.0f)
		{
			play_sound(paddle.sound);

			GLfloat power = (0.5f + min(0.5f, paddle.charge)) * -1.0f;
			if (!paddle.serving)
			{
				power *= 2.0f;
				receiver = swap(receiver);
			}

			if (!paddle.serving && bounce_side == paddle.side)
			{
				add_point(receiver->score);
				serve(ball); // foul (hit before bounce)
			}
			else
			{
				ball.velocity[0] = power * paddle.side * 2000.0f;
				ball.velocity[1] = fabs(ball.velocity[0] * 0.5f);
				paddle.serving = false;
			}
		}
	}
	paddle.charge = 0.0f;
}

const GLfloat TABLE_WIDTH = 2740.0f;
const GLfloat TABLE_LEFT = -TABLE_WIDTH / 2.0f;
const GLfloat TABLE_RIGHT = TABLE_WIDTH / 2.0f;
const GLfloat TABLE_HEIGHT = 760.0f;
const GLfloat TABLE_TOP = GLfloat(SCREEN_BOTTOM) + TABLE_HEIGHT;
const GLfloat NET_HEIGHT = 152.5f;

void set_start(Ball &ball)
{
	bounce_side = server->side;

	ball.position[0] = TABLE_RIGHT * server->side * 1.2f;
	ball.position[1] = TABLE_TOP + ball.radius * 2.0f;
	
	ball.velocity[0] =    0.0f;
	ball.velocity[1] = 3200.0f;
}

const GLfloat BASE = GLfloat(SCREEN_BOTTOM);

GLfloat distance_to_table_top(const Ball &ball)
{
	return (ball.position[1] - ball.radius) - TABLE_TOP;
}

void Table::update(GLfloat t)
{
}

void Ball::update(GLfloat t)
{
	GLfloat previous = this->position[0];

	this->position[0] += this->velocity[0] * t;
	this->position[1] += this->velocity[1] * t;

	GLfloat d = distance_to_table_top(*this);
	if (previous > 0.0f && this->position[0] < 0.0f && d < NET_HEIGHT)
	{
		add_point(left.score);
		serve(*this);
	}
	else if (previous < 0.0f && this->position[0] > 0.0f && d < NET_HEIGHT)
	{
		add_point(right.score);
		serve(*this);
	}
	else if (d < 0.0f)
	{
		if (this->position[0] > TABLE_LEFT && this->position[0] < TABLE_RIGHT)
		{
			this->position[1] = TABLE_TOP + this->radius - d;
			this->velocity[1] *= -1.0f;

			play_sound(this->sound);

			if (this->position[0] > 0.0f)
			{
				if (bounce_side == -1.0f)
				{
					add_point(receiver->score);
					serve(*this);
				}
				else
				{
					bounce_side = -1.0f;
				}
			}
			else if (this->position[0] < 0.0f)
			{
				if (bounce_side == 1.0f)
				{
					add_point(receiver->score);
					serve(*this);
				}
				else
				{
					bounce_side = 1.0f;
				}
			}
		}
		else
		{
			if (bounce_side != receiver->side)
			{
				receiver = swap(receiver);
			}
			add_point(receiver->score);
			serve(*this);
		}
	}
	else
	{
		this->velocity[1] -= 9810.0f * t;
	}
}

void Paddle::update(GLfloat t)
{
	this->charge += t;
}

void Table::draw(void)
{
	::draw(this->image, this->position);
}

void Ball::draw(void)
{
	::draw(this->image, this->position);
}

void Paddle::draw(void)
{
	draw_score(this->score, this->position);
}

void quit(int code)
{
	Mix_CloseAudio();
    SDL_Quit();
    exit(code);
}

void handle_key(SDL_keysym *key, bool down)
{
	if (!down)
	{
		switch (key->sym)
		{
		case SDLK_ESCAPE:
			quit(0);
			break;
		case SDLK_1:
			add_point(left.score);
			break;
		case SDLK_p:
			pause = !pause;
			break;
		case SDLK_f:
			frame_advance = true;
			break;
		case SDLK_r:
			reset_game = true;
			break;
		}
	}

	switch (key->sym)
	{
	case SDLK_LCTRL:
		hit_ball(left, ball, down);
		break;
	case SDLK_RCTRL:
		hit_ball(right, ball, down);
		break;
	}
}

void process_events(void)
{
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) 
	{
        switch (evnt.type) 
		{
		case SDL_KEYUP:
		    handle_key(&evnt.key.keysym, false);
			break;
		case SDL_KEYDOWN:
		    handle_key(&evnt.key.keysym, true);
			break;
		case SDL_QUIT:
		    quit(0);
		    break;
        }
    }
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
	{
		printf("Audio / video initialization failed: %s\n", SDL_GetError());
        quit(1);
    }

	if (!init_audio())
	{
		quit(1);
	}

	if (!init_graphics())
	{
		quit(1);
	}

	init_score();

	load_texture(ball.image.texture, "ball.bmp");
	load_audio(ball.sound, "bounce.wav");
	ball.radius = 40.0f;
	ball.image.dimension[0] = ball.radius;
	ball.image.dimension[1] = ball.radius;

	load_texture(table.image.texture, "table.bmp");
	table.image.dimension[0] = TABLE_RIGHT;
	table.image.dimension[1] = NET_HEIGHT;
	table.position[0] = 0.0f;
	table.position[1] = TABLE_TOP;

	left.side = -1.0f;
	load_audio(left.sound, "hit.wav");
	left.score = 0;
	left.serving = false;
	left.position[0] = TABLE_LEFT;
	left.position[1] = GLfloat(SCREEN_TOP) - TABLE_HEIGHT;

	right.side = 1.0f;
	right.sound = left.sound;
	right.score = 0;
	right.serving = false;
	right.position[0] = TABLE_RIGHT;
	right.position[1] = GLfloat(SCREEN_TOP) - TABLE_HEIGHT;

	Object *object_array[] =
	{
		&table,
		&ball,
		&left,
		&right
	};

	const int object_count = sizeof (object_array) / sizeof(Object*);
	int i = 0;

	serve(ball);

	while (true) 
	{
		const GLfloat t = 1.0f / GLfloat(60);

		process_events();
		wait = max(0.0f, wait - t);
		if (reset_game)
		{
			set_start(ball);
			reset_game = false;
		}
		else if (!pause || frame_advance)
		{
			for (i = 0; i < object_count; i++)
			{
				object_array[i]->update(t);
			}
			frame_advance = false;
		}
		start_render();
		for (i = 0; i < object_count; i++)
		{
			object_array[i]->draw();
		}
		end_render();
    }

	return 0;
}
