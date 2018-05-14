#include "laser.h"
#include "invader.h"

#include "../object.h"
#include "../audio.h"
#include "../graphics.h"
#include "../screen.h"
#include "../controls.h"

#include <stdio.h>

const int SHOT_WIDTH = 2;
const int SHOT_HEIGHT = 4;

struct Shot: public Object
{
	Mix_Chunk *sound;
	Image image;
	int position[2];
	bool alive;

	void update(void)
	{
		if (alive)
		{
			position[1] -= SHOT_HEIGHT;//Shots going down the way
			if (position[1] < PLAY_FIELD_BOTTOM)//
			{
				alive = false;
			}

			int size[] = { SHOT_WIDTH / 2, SHOT_HEIGHT / 2 };
			if (collide_invaders(position, size))
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
			::draw(image, fpos);
		}
	}
};

Shot shot;

const int LASER_FRAMES = 3;
const int LASER_WIDTH = 16;
const int LASER_HEIGHT = 8;

void respawn_laser(void);

struct Laser: public Object
{
	Image image[LASER_FRAMES];
	Mix_Chunk *explode;
	int position[2];
	bool alive;
	int time;
	int lives;

	void update(void)
	{
		if (alive)
		{
			if (move_left && position[0] > PLAY_FIELD_LEFT + LASER_WIDTH)//if the player is moving left and hasn't touched the left MARGIN (left play area less one width of the laser), then the player can continue to move left
			{
				position[0]--;
			}
			
			if (move_right && position[0] < PLAY_FIELD_RIGHT - LASER_WIDTH)
			{
				position[0]++;
			}

			if (fire_laser && !shot.alive)
			{
				shot.alive = true;
				play_sound(shot.sound);
				shot.position[0] = position[0];
				shot.position[1] = position[1];
				fire_laser = false;
			}
		}
		else
		{
			time++;
			if (time > 30)//respawn time for laser
			{
				respawn_laser();
			}
		}
	}

	void hit(void)
	{
		alive = false;
		time = 0;
		play_sound(explode);
		if (lives == 1)
		{
			game_over = true;
		}
		else
		{
			lives--;
		}
	}

	void draw(void)
	{
		GLfloat fpos[2] = { GLfloat(position[0]), GLfloat(position[1]) };
		if (alive)
		{
			::draw(image[0], fpos);
		}
		else
		{
			int frame = 1 + ((time / 5) % 2);
			::draw(image[frame], fpos);
		}
	}
};

Laser laser;

void load_laser(void)
{
	char filename[] = "white?.bmp";
	for (int i = 0; i < LASER_FRAMES; i++)
	{
		sprintf_s(filename, sizeof(filename), "white%d.bmp", i);
		load_texture(laser.image[i].texture, filename);
		laser.image[i].dimension[0] = LASER_WIDTH / 2;
		laser.image[i].dimension[1] = LASER_HEIGHT / 2;
	}

	load_audio(laser.explode, "explode.wav");

	reset_laser();

	load_audio(shot.sound, "shot.wav");
	load_texture(shot.image.texture, "pill.bmp");
	shot.image.dimension[0] = SHOT_WIDTH / 2;
	shot.image.dimension[1] = SHOT_HEIGHT / 2;
	shot.alive = false;
	shot.position[0] = PLAY_FIELD_LEFT;
	shot.position[1] = PLAY_FIELD_TOP;//
}

Object **add_laser(Object **object_array)
{
	*object_array = &laser;
	object_array++;

	*object_array = &shot;
	object_array++;

	return object_array;
}

void reset_laser(void)
{
	laser.lives = 5;//extra lives over usual amount because of the increased speed and difficulty of the enemies
	shot.alive = false;
	fire_laser = false;
	move_left = false;
	move_right = false;
	respawn_laser();
}

void respawn_laser(void)
{
	laser.alive = true;
	laser.time = 0;
	laser.position[0] = PLAY_FIELD_LEFT + LASER_WIDTH;
	laser.position[1] = PLAY_FIELD_TOP - LASER_HEIGHT;
}

bool collide_laser(int position[], int size[])
{
	bool hit = false;

	if (position[0] - size[0] >= laser.position[0] - LASER_WIDTH  / 2 &&
		position[0] + size[0] <= laser.position[0] + LASER_WIDTH  / 2 &&
		position[1] - size[1] >= laser.position[1] - LASER_HEIGHT / 2 &&
		position[1] + size[1] <= laser.position[1] + LASER_HEIGHT / 2)
	{
		laser.hit();
		hit = true;
	}

	return hit;
}

void laser_invaded(void)
{
	laser.hit();
}
