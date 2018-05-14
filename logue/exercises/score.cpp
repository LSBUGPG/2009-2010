#include "score.h"//Kevin Logue

#include <cstdio>
#include "graphics.h"
#include "audio.h"

Image number [10]; //empty array,so load for all 10 digits and corresponding bitmaps


Mix_Chunk *score_sound = NULL;

void init_score(void)
{
	const int image = 10;
	const char *score_new_image [] = 
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
	
for (int i = 0; i < image; i++)
	{
	load_texture(number [i].texture, score_new_image [i]);
	number [i].dimension [0] = 200.0f;
	number [i].dimension [1] = 200.0f;
	}	

	load_audio(score_sound, "score.wav");

//a 'for' function would be handy here
	// initialise the 10 digits here...
	// use the load_texture function to load "n0.bmp", "n1.bmp", ...
	//set each digit to be same size, eg 32x32
	// use load_audio to load "score.wav"
}

void draw_score(int score, const GLfloat *position)
{
	GLfloat pos [] = { position [0], position [1] };
	draw(number [score%10], pos);				
	
	pos [0] -= number [0].dimension [0] * 1.2f;
	draw(number [score/10], pos);			
	// draw the given score at the given position...
	// use the draw function and pass the correct digit
}

void add_point(int &score)
{
    if (score < 10) 

	{
	score++;
	}

    play_sound(score_sound);
	// add to the score value '&score', something like score++
	// and optionally play the score sound
	//basically just add point & play_sound
}