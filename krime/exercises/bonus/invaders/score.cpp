#include "score.h"

#include <cstdio>
#include "graphics.h"
#include "audio.h"
#include "object.h"
#include "game.h"

const int SCORE_WIDTH = 8;
const int SCORE_HEIGHT = 8;
const int SCORE_X = PLAY_FIELD_RIGHT - SCORE_WIDTH;
const int SCORE_Y = PLAY_FIELD_TOP - SCORE_HEIGHT;

struct Score: public Object
{
	Image digit[10];
	int points;

	void update(void) {}
	void draw(void)
	{
		GLfloat fpos[] = { SCORE_X, SCORE_Y };
		const int SCORE_DIGITS = 5;
		int number = points;
		for (int i = 0; i < SCORE_DIGITS; i++)
		{
			::draw(digit[number % 10], fpos);
			fpos[0] -= 8.0f;
			number /= 10;
			if (number == 0)
			{
				break;
			}
		}
	}
};

Score score;

int load_score(Object *object_array[])
{
	char bitmap_name[] = "n?.bmp";

	// initialise the 10 digits here...
	// use the load_texture function to load "n0.bmp", "n1.bmp", ...
	for (int i = 0; i < 10; i++)
	{
		sprintf_s(bitmap_name, sizeof(bitmap_name), "n%d.bmp", i);
		load_texture(score.digit[i].texture, bitmap_name);
		score.digit[i].dimension[0] = SCORE_WIDTH / 2;
		score.digit[i].dimension[1] = SCORE_HEIGHT / 2;
	}
	score.points = 0;

	*object_array = &score;

	return 1;
}

void add_points(int value)
{
	score.points += value;
}
