#include <windows.h>
#include <SDL.h>
#include <math.h>

#include "graphics.h"

void quit(int code)
{
    SDL_Quit();
    exit(code);
}

enum { replace, additive, blended } compose = replace;
bool background = false;

void handle_key(SDL_keysym *key)
{
	switch (key->sym)
	{
	case SDLK_ESCAPE:
		quit(0);
		break;
	case SDLK_1:
		compose = replace;
		break;
	case SDLK_2:
		compose = additive;
		break;
	case SDLK_3:
		compose = blended;
		break;
	case SDLK_b:
		background = !background;
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
		    handle_key(&evnt.key.keysym);
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

	if (!init_graphics())
	{
		quit(1);
	}

	Point centre(0.0f, 0.0f);
	Image check;
	Image text;

	load_texture(check.texture, "background.bmp");
	check.dimension[0] = 100.0f;
	check.dimension[1] = 100.0f;

	load_text_line(text, "1234");

	while (true)
	{
		process_events();

		start_render();

		switch (compose)
		{
		case replace:
			glDisable(GL_BLEND);
			break;
		case additive:
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		case blended:
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			break;
		}

		if (background)
		{
			draw(check, centre.coordinate);
		}

		draw(text, centre.coordinate);
		end_render();
    }

	return 0;
}
