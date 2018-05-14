#include "laser.h"

#include <stdio.h>
#include "object.h"
#include "graphics.h"
#include "game.h"
#include "invader.h"
#include "audio.h"

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
			position[1] += SHOT_HEIGHT;//
			if (position[1] > PLAY_FIELD_TOP)//
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

void reset_laser(void);

struct Laser: public Object
{
	Image image[LASER_FRAMES];
	Mix_Chunk *explode;
	int position[2];
	bool alive;
	int time;

	void update(void)
	{
		if (alive)
		{
			if (move_left && position[0] > PLAY_FIELD_LEFT + LASER_WIDTH)//
			{
				position[0]--;
			}
			
			if (move_right && position[0] < PLAY_FIELD_RIGHT - LASER_WIDTH)//
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
			if (time > 60)
			{
				reset_laser();
			}
		}
	}

	void hit(void)
	{
		alive = false;
		time = 0;
		play_sound(explode);
	}

	void draw(void)
	{
		GLfloat fpos[2] = { GLfloat(position[0]), GLfloat(position[1]) };
		if (alive)
		{
			::draw(image[0], fpos);//draws first laser image (ie. non-exploded one)
		}
		else
		{
			int frame = 1 + ((time / 5) % 2);
			::draw(image[frame], fpos);
		}
	}
};

Laser laser;

int load_laser(Object *object_array[])
{
	char filename[] = "laser?.bmp";
	for (int i = 0; i < LASER_FRAMES; i++)
	{
		sprintf_s(filename, sizeof(filename), "laser%d.bmp", i);
		load_texture(laser.image[i].texture, filename);
		laser.image[i].dimension[0] = LASER_WIDTH / 2;
		laser.image[i].dimension[1] = LASER_HEIGHT / 2;
	}

	load_audio(laser.explode, "explode.wav");

	reset_laser();

	*object_array = &laser;
	object_array++;

	load_audio(shot.sound, "shot.wav");
	load_texture(shot.image.texture, "shot.bmp");
	shot.image.dimension[0] = SHOT_WIDTH / 2;
	shot.image.dimension[1] = SHOT_HEIGHT / 2;
	shot.alive = false;
	shot.position[0] = PLAY_FIELD_LEFT;
	shot.position[1] = PLAY_FIELD_BOTTOM;//

	*object_array = &shot;
	object_array++;

	return 2;
}

void reset_laser(void)
{
	laser.alive = true;
	laser.time = 0;
	laser.position[0] = PLAY_FIELD_LEFT + LASER_WIDTH;
	laser.position[1] = PLAY_FIELD_BOTTOM + LASER_HEIGHT;//
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