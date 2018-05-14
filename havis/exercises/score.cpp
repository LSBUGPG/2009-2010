#include "score.h"

#include <cstdio>
#include "graphics.h"
#include "audio.h"


Image digit[10];

Mix_Chunk *score_sound = NULL;

void init_score(void)
{
	load_texture(digit[0].texture,"n0.bmp");
	digit[0].dimension[0] = 100.0f;
	digit[0].dimension[1] = 100.0f;

	load_texture(digit[1].texture,"n1.bmp");
	digit[1].dimension[0] = 100.0f;
	digit[1].dimension[1] = 100.0f;

	load_texture(digit[2].texture,"n2.bmp");
	digit[2].dimension[0] = 100.0f;
	digit[2].dimension[1] = 100.0f;

	load_texture(digit[3].texture,"n3.bmp");
	digit[3].dimension[0] = 100.0f;
	digit[3].dimension[1] = 100.0f;

	load_texture(digit[4].texture,"n4.bmp");
	digit[4].dimension[0] = 100.0f;
	digit[4].dimension[1] = 100.0f;

	load_texture(digit[5].texture,"n5.bmp");
	digit[5].dimension[0] = 100.0f;
	digit[5].dimension[1] = 100.0f;

	load_texture(digit[6].texture,"n6.bmp");
	digit[6].dimension[0] = 100.0f;
	digit[6].dimension[1] = 100.0f;

	load_texture(digit[7].texture,"n7.bmp");
	digit[7].dimension[0] = 100.0f;
	digit[7].dimension[1] = 100.0f;

	load_texture(digit[8].texture,"n8.bmp");
	digit[8].dimension[0] = 100.0f;
	digit[8].dimension[1] = 100.0f;

	load_texture(digit[9].texture,"n9.bmp");
	digit[9].dimension[0] = 100.0f;
	digit[9].dimension[1] = 100.0f;

load_audio(score_sound, "score.wav"); 
		 

}
void draw_score(int score, const GLfloat *position)
{ 
	draw(digit[score],position);
	
}

void add_point(int &score)
{

	score ++;

	const int AUTO_SELECT_CHANNEL = -1;
		const int NO_LOOP = 0;
		const int PLAY_TO_END = -1;
		Mix_PlayChannelTimed(AUTO_SELECT_CHANNEL, score_sound, NO_LOOP, PLAY_TO_END);

}
