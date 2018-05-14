#include "score.h"

#include <cstdio>
#include "graphics.h"
#include "audio.h"


Image digit[10];

	const int Number = 10;
	const char *num[] =		// initialise the 10 digits here...
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

Mix_Chunk *score_sound = NULL;

void init_score(void)
{
	
for (int i = 0; i < Number; i++)
{
	load_texture(digit[i].texture,num[i]);
	digit[i].dimension[0] = 100.0f;
	digit[i].dimension[1] = 100.0f;
}

	// use the load_texture function to load "n0.bmp", "n1.bmp", ...
	
load_audio(score_sound, "score.wav"); 
		 
	// use load_audio to load "score.wav"

}
void draw_score(int score, const GLfloat *position)
{ 
	draw(digit[score],position);
	
}

void add_point(int &score)
{

	score ++;// add to the score value

	const int AUTO_SELECT_CHANNEL = -1;
		const int NO_LOOP = 0;
		const int PLAY_TO_END = -1;
		Mix_PlayChannelTimed(AUTO_SELECT_CHANNEL, score_sound, NO_LOOP, PLAY_TO_END);


// and optionally play the score sound
}
