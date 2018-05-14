#include "score.h"
#include <windows.h>

#include <cstdio>
#include "graphics.h"
#include "audio.h"

Image digit[10];
Mix_Chunk *score_sound = NULL;

void init_score(void)
{

	/*int i = 0; 
	const char x = i;
	
	while (i <= 10)
	{
		load_texture (digit[i].texture, ("n%d.bmp",x));   //this was my attempt to create a loop for the array
		digit[i].dimension[0] = 150;				 //Couldnt figure out how to make it target differnt filenames
		digit[i].dimension[1] = 150;

		i++;
	}*/

	load_texture (digit[0].texture, "n0.bmp");
	digit[0].dimension[0] = 150;
	digit[0].dimension[1] = 150;

	load_texture (digit[1].texture, "n1.bmp");
	digit[1].dimension[0] = 150;
	digit[1].dimension[1] = 150;

	load_texture (digit[2].texture, "n2.bmp");
	digit[2].dimension[0] = 150;
	digit[2].dimension[1] = 150;
	
	load_texture (digit[3].texture, "n3.bmp");
	digit[3].dimension[0] = 150;
	digit[3].dimension[1] = 150;
	
	load_texture (digit[4].texture, "n4.bmp");
	digit[4].dimension[0] = 150;
	digit[4].dimension[1] = 150;

	load_texture (digit[5].texture, "n5.bmp");
	digit[5].dimension[0] = 150;
	digit[5].dimension[1] = 150;

	load_texture (digit[6].texture, "n6.bmp");
	digit[6].dimension[0] = 150;
	digit[6].dimension[1] = 150;

	load_texture (digit[7].texture, "n7.bmp");
	digit[7].dimension[0] = 150;
	digit[7].dimension[1] = 150;

	load_texture (digit[8].texture, "n8.bmp");
	digit[8].dimension[0] = 150;
	digit[8].dimension[1] = 150;

	load_texture (digit[9].texture, "n9.bmp");
	digit[9].dimension[0] = 150;
	digit[9].dimension[1] = 150;
	
	load_audio (score_sound, "score.wav");
}

void draw_score(int score, const GLfloat *position)
{
	draw(digit[score], position);
}

void add_point(int &score)
{
	score ++;
	play_sound(score_sound);
}