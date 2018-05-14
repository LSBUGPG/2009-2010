#include "console.h"

#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>
#include "graphics.h"

const char *FONT_NAME = "VeraMoBd.ttf";
const int FONT_SIZE = 18;
const int LINE_SPACE = 20;
const int NUMBER_OF_LINES = (SCREEN_HEIGHT / LINE_SPACE) + 2;
const int MAX_WIDTH = 100;
const char DELIMITERS[] = " -"; // valid points to break a string

struct Line
{
	bool empty;
	Image image;
	GLfloat position[2];
};

Line line_array[NUMBER_OF_LINES];

TTF_Font *font = NULL;
SDL_mutex *mutex = NULL;
SDL_cond *newline = NULL;
SDL_cond *input = NULL;
int scroll = 0;
int next = 0;
const char *lineText = NULL;
char inputKey = 0;

int thread_function(void *data)
{
	typedef void (*func)(void);
	func f = (func)data;
	if (f)
	{
		f();
	}
	return 0;
}

const char *load_text_line(Line &line, const char *text)
{
	if (text && *text == 0)
	{
		return NULL;
	}

	if (font)
	{
		char buffer[MAX_WIDTH];
		
		size_t last_delim = 0;
		size_t last_char = 0;

		for (size_t i = 0; i < sizeof(buffer) - 1; i++)
		{
			buffer[i] = text[i];
			buffer[i+1] = 0;
			int width;
			int height;
			int getSize = TTF_SizeUTF8(font, buffer, &width, &height);
			if (width < SCREEN_WIDTH)
			{
				if (text[i] == 0 || strchr(DELIMITERS, text[i]) != 0)
				{
					last_delim = i;
				}
				else
				{
					last_char = i;
				}
			}
			else
			{
				break;
			}

			if (text[i] == 0)
			{
				break;
			}
		}

		if (last_delim)
		{
			last_char = last_delim - 1;
		}

		buffer[last_char+1] = 0;
		text = text + last_char + 1;
		if (*text && strchr(DELIMITERS, *text) != 0)
		{
			text++;
		}

		SDL_Color col = {255, 255, 255};

		SDL_Surface *surface = 
			TTF_RenderUTF8_Blended(font, buffer, col);

		if (surface)
		{
			line.empty = false;
			glGenTextures(1, &line.image.texture);
			glBindTexture(GL_TEXTURE_2D, line.image.texture);

			const GLint MIPMAP_LEVEL = 0;
			const GLint NO_BORDER = 0;

			glTexImage2D(GL_TEXTURE_2D,
				MIPMAP_LEVEL,
				GL_ALPHA,
				surface->w,
				surface->h,
				NO_BORDER,
				GL_BGRA_EXT,
				GL_UNSIGNED_BYTE,
				surface->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
			line.image.dimension[0] = GLfloat(surface->w) / 2.0f;
			line.image.dimension[1] = GLfloat(surface->h) / 2.0f;

			SDL_FreeSurface(surface);
		}

		if (*text == 0)
		{
			text = 0;
		}
	}
	else
	{
		text = 0;
	}

	return text;
}

bool init_console(func f)
{
	mutex = SDL_CreateMutex();
	newline = SDL_CreateCond();
	input = SDL_CreateCond();
	if (!mutex)
	{
		printf("Could not create mutex\n");
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("Font init failed: %s\n", TTF_GetError());
		return false;
	}

	font = TTF_OpenFont(FONT_NAME, FONT_SIZE);

	for (int i = 0; i < NUMBER_OF_LINES; i++)
	{
		line_array[i].empty = true;
	}

	SDL_Thread *thread = SDL_CreateThread (thread_function, f);
	return thread != 0;
}

void quit_console(void)
{
	SDL_DestroyCond(input);
	SDL_DestroyCond(newline);
	SDL_DestroyMutex(mutex);
}

void console_print(const char *text)
{
	SDL_mutexP(mutex);
	SDL_CondWait(newline, mutex);
	lineText = text;
	SDL_CondWait(newline, mutex);
	SDL_mutexV(mutex);
}

void console_put_key(char key)
{
	SDL_mutexP(mutex);
	inputKey = key;
	SDL_CondSignal(input);
	SDL_mutexV(mutex);
}

char console_get_key(void)
{
	char key = 0;
	SDL_mutexP(mutex);
	SDL_CondWait(input, mutex);
	key = inputKey;
	SDL_mutexV(mutex);
	return key;
}

void console_update(void)
{
	SDL_mutexP(mutex);
	
	if (scroll)
	{
		for (int i = 0; i < NUMBER_OF_LINES; i++)
		{
			line_array[i].position[1] += 1.0f;
		}

		scroll--;
	}
	else if (lineText)
	{
		if (!line_array[next].empty)
		{
			glDeleteTextures(1, &line_array[next].image.texture);
			line_array[next].empty = true;
		}
		lineText = load_text_line(line_array[next], lineText);
		line_array[next].position[0] = GLfloat(SCREEN_LEFT) + line_array[next].image.dimension[0];
		line_array[next].position[1] = GLfloat(SCREEN_BOTTOM - LINE_SPACE / 2);

		next = (next + 1) % NUMBER_OF_LINES;
		scroll = LINE_SPACE;
		if (lineText == NULL)
		{
			SDL_CondSignal(newline);
		}
	}
	else
	{
		SDL_CondSignal(newline);
	}
	
	SDL_mutexV(mutex);
}

void console_draw(void)
{
	SDL_mutexP(mutex);
	start_render();
	for (int i = 0; i < NUMBER_OF_LINES; i++)
	{
		if (!line_array[i].empty)
		{
			draw(line_array[i].image, line_array[i].position);
		}
	}
	end_render();
	SDL_mutexV(mutex);
}
