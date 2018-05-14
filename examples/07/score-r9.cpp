#include "score.h"

#include <cstdio>
#include "graphics.h"
#include "audio.h"

Image digit[10];
Mix_Chunk *score_sound = NULL;

void init_score(void)
{
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
		digit[i].dimension[0] = 100.0f;
		digit[i].dimension[1] = 100.0f;
	}
	// use load_audio to load "score.wav"
}

void draw_score(int score, const GLfloat *position)
{
	draw(digit[min(score, 9)], position);
}

void add_point(int &score)
{
	score++;
	// and optionally play the score sound
}
