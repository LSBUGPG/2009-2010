#include "score.h"

#include <cstdio>
#include "graphics.h"
#include "audio.h"

Image digit[10];
Mix_Chunk *score_sound = NULL;

void init_score(void)
{
	const int IMAGE = 10;
	const char *score_new_image[] =			// initialise the 10 digits here...
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
									// use the load_texture function to load "n0.bmp", "n1.bmp", ...

	for (int i = 0; i < IMAGE; i++)
	{
		load_texture(digit[i].texture, score_new_image[i]);
		digit[i].dimension[0] = 160.0f;
		digit[i].dimension[1] = 160.0f;
	}	

	load_audio(score_sound, "1.Epic Fail.wav");	// use load_audio to load "score.wav"
}

void draw_score(int score, const GLfloat *position)
{
	GLfloat pos[] = { position[0], position[1] };
	draw(digit[score%10], pos);				// draw the given score at the given position...
	
	pos[0] -= digit[0].dimension[0] * 1.5f;
	draw(digit[score/10], pos);				// use the draw_image function and pass the correct digit
}

void add_point(int &score)
{
	if (score < 21)
	{
		score ++;							// add to the score value
	}
	play_sound(score_sound);				// and optionally play the score sound
}