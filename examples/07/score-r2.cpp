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
	const char * bitmap_name[] =
	{
		"n0.bmp", 
		"n1.bmp", 
		"n2.bmp", 
		"n3.bmp", 
		"n4.bmp", 
		"n5.bmp", 
		"n6.bmp", 
		"n7.bmp", 
		"n8.bmp", 
		"n9.bmp"
	};

	for (int i = 0; i < 10; i++)
	{
		load_texture(digit[i].texture, bitmap_name[i]);
		//..
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
