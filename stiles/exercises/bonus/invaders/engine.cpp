#include <windows.h>
#include <SDL.h>
#include <math.h>

#include "graphics.h"
#include "audio.h"
#include "score.h"

#include "object.h"
#include "invader.h"
#include "laser.h"
#include "game.h"

bool pause = true;
bool frame_advance = false;
bool reset_game = true;

void quit(int code)
{
	Mix_CloseAudio();
    SDL_Quit();
    exit(code);
}

void handle_key(SDL_keysym *key, bool down)
{
	if (down)
	{
		if (key->sym == SDLK_LCTRL)
		{
			fire_laser = true;
		}
	}
	else
	{
		switch (key->sym)
		{
		case SDLK_ESCAPE:
			quit(0);
			break;
		case SDLK_p:
			pause = !pause;
			break;
		case SDLK_f:
			frame_advance = true;
			break;
		case SDLK_r:
			reset_game = true;
			break;
		}
	}

	switch (key->sym)
	{
	case SDLK_LEFT:
		move_left = down;
		break;
	case SDLK_RIGHT:
		move_right = down;
		break;
	}
}

void process_events(void)
{
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) 
	{
        switch (evnt.type) 
		{
		case SDL_KEYUP:
		    handle_key(&evnt.key.keysym, false);
			break;
		case SDL_KEYDOWN:
		    handle_key(&evnt.key.keysym, true);
			break;
		case SDL_QUIT:
		    quit(0);
		    break;
        }
    }
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
	{
		printf("Audio / video initialization failed: %s\n", SDL_GetError());
        quit(1);
    }

	if (!init_audio())
	{
		quit(1);
	}

	if (!init_graphics())
	{
		quit(1);
	}

	const int OBJECT_TOTAL = INVADER_TOTAL + LASER_TOTAL + SCORE_TOTAL;
	Object *object_array[OBJECT_TOTAL];

	int object_count = 0;
	object_count += load_invaders(&object_array[object_count]);
	object_count += load_laser(&object_array[object_count]);
	object_count += load_score(&object_array[object_count]);
	while (true) 
	{
		int i;
		process_events();
		if (reset_game)
		{
			reset_game = false;
		}
		else if (!pause || frame_advance)
		{
			for (i = 0; i < object_count; i++)
			{
				object_array[i]->update();
			}
			frame_advance = false;
		}
		start_render();
		for (i = 0; i < object_count; i++)
		{
			object_array[i]->draw();
		}
		end_render();
    }

	return 0;
}
