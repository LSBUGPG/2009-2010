#include <windows.h>
#include <SDL.h>
#include <math.h>

#include "graphics.h"
#include "audio.h"
#include "console.h"

void quit(int code)
{
	Mix_CloseAudio();
    SDL_Quit();
    exit(code);
}

void handle_key(SDL_keysym *key)
{
	switch (key->sym)
	{
	case SDLK_ESCAPE:
		quit(0);
		break;
	default:
		console_put_key(char(key->sym));
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

void game(void)
{
	console_print("Welcome to the adventure.");
	console_print(" ");
	console_print("To play, I will describe your situation, and you must "
				  "choose what to do.");
	console_print("");
	console_print("Good luck adventurer!");
	console_print("");
	console_print("");

retry:
	console_print("You are in a mysterious forest. Beside you is a small "
				  "stream. The forest is unexpectedly quiet. The only sound "
				  "is the gentle trickle of the water. There is also a small "
				  "wooden hut nearby. The door appears unlocked.");
	console_print("");
	console_print("Will you:");
	console_print("  1) enter the hut");
	console_print("  2) follow the stream");
	console_print("?");
	char key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("You enter the hut.");
		goto the_end;
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You follow the stream.");
		goto the_end;
	}
	else
	{
		console_print("");
		console_print("unknown option");
		console_print("");
		console_print("");
		goto retry;
	}

the_end:
		console_print("");
		console_print("THE END.");
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

	if (!init_console(game))
	{
		quit(1);
	}

	while (true)
	{
		process_events();
		console_update();
		console_draw();
    }

	return 0;
}
