#include <windows.h>
#include <SDL.h>
#include <math.h>

#include "graphics.h"
#include "audio.h"
#include "controls.h"

#include "mode.h"

bool pause = false;
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
		switch (key->sym)
		{
		case SDLK_LCTRL:
			fire_laser = true;
			break;
		case SDLK_SPACE:
			start_game = true;
			break;
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

	Mix_Music *music;
	load_music(music, "WP.wav");
	
	int LOOP_MUSIC_FOREVER = -1;
	Mix_PlayMusic(music, LOOP_MUSIC_FOREVER);


    Mode *mode = load_modes();

	Image background;
	load_texture(background.texture, "background.bmp");
	background.dimension[0] = SCREEN_WIDTH / 4;
	background.dimension[1] = SCREEN_HEIGHT / 4;
		
	while (true)
	{
		process_events();
		if (reset_game)
		{
			mode->reset();
			reset_game = false;
		}
		else if (!pause || frame_advance)
		{
			mode->update();
			frame_advance = false;
		}

		start_render();
		GLfloat centre[] = { 0.0f, 0.0f };
		draw(background, centre);
		mode->draw();
		end_render();

		mode = next_mode();
    }

	return 0;
}
