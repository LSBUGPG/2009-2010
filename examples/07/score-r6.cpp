#include "score.h"

#include <cstdio>
#include "graphics.h"
#include "audio.h"

Image digit[10];
Mix_Chunk *score_sound = NULL;

void init_score(void)
{
	// initialise the 10 digits here...
	// use the load_texture function to load "n0.bmp", "n1.bmp", ...
	load_texture(digit[0].texture, "n0.bmp");
	load_texture(digit[1].texture, "n1.bmp");
	load_texture(digit[2].texture, "n2.bmp");
	load_texture(digit[3].texture, "n3.bmp");
	load_texture(digit[4].texture, "n4.bmp");
	load_texture(digit[5].texture, "n5.bmp");
	load_texture(digit[6].texture, "n6.bmp");
	load_texture(digit[7].texture, "n7.bmp");
	load_texture(digit[8].texture, "n8.bmp");
	load_texture(digit[9].texture, "n9.bmp");

	for (int i = 0; i < 10; i++)
	{
		digit[i].dimension[0] = 100.0f;
		digit[i].dimension[1] = 100.0f;
	}

	// use load_audio to load "score.wav"
}

void draw_score(int score, const GLfloat *position)
{
	// draw the given score at the given position...
	// use the draw_image function and pass the correct digit
}

void add_point(int &score)
{
	// add to the score value
	// and optionally play the score sound
}
