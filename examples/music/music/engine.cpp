#include <windows.h>
#include <SDL.h>
#include <math.h>

#include "graphics.h"
#include "audio.h"

bool pause = false;
bool reset_game = true;

void quit(int code)
{
	Mix_CloseAudio();
    SDL_Quit();
    exit(code);
}

void handle_key(SDL_keysym *key, bool down)
{
	if (!down)
	{
		switch (key->sym)
		{
		case SDLK_ESCAPE:
			quit(0);
			break;
		case SDLK_p:
			pause = !pause;
			break;
		case SDLK_r:
			reset_game = true;
			break;
		}
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

	Mix_Music *music;
	load_music(music, "music.ogg");
	
	int LOOP_MUSIC_FOREVER = -1;
	Mix_PlayMusic(music, LOOP_MUSIC_FOREVER);

	while (true)
	{
		process_events();
		if (reset_game)
		{
			reset_game = false;
			Mix_RewindMusic ();
		}

		if (pause)
		{
			Mix_PauseMusic ();
		}
		else
		{
			Mix_ResumeMusic ();
		}

		start_render();
		end_render();
    }

	return 0;
}
