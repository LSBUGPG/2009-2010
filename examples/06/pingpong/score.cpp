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