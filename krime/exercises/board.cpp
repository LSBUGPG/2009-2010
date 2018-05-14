#include <windows.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <GL/gl.h>


struct Colour
{
	GLubyte channels[3]; // RGB
	Colour(GLubyte r, GLubyte g, GLubyte b)
	{
		channels[0] = r;
		channels[1] = g;
		channels[2] = b;
	}
	Colour(){}
};

const Colour white  (255, 255, 255);

struct Vertex
{
	GLfloat coordinate[2]; // XY
	Vertex(GLfloat x, GLfloat y)
	{
		coordinate[0] = x;
		coordinate[1] = y;
	}
	Vertex(){}
};

struct SoundKey
{
	GLuint image;
	GLuint letter;
	Mix_Chunk *stream;
	const char *image_bitmap;
	const char *letter_bitmap;
	const char *audio;
	SDLKey keycode;
	bool down;
	Vertex pos;

	SoundKey(const char *image_bitmap_filename,
			 const char *letter_bitmap_filename,
			 const char *audio_filename,
			 const Vertex &bitmap_offset, 
			 SDLKey activate_keycode)
	{
		image_bitmap = image_bitmap_filename;
		letter_bitmap = letter_bitmap_filename;
		audio = audio_filename;
		keycode = activate_keycode;
		down = false;
		pos = bitmap_offset;
	}
};

SoundKey sound_key[] =
{
	SoundKey("ball.bmp",
			 "letter_b.bmp",
			 "bounce.wav",
			 Vertex(-150.0f, 16.0f),
			 SDLK_b),

 // I've changed the following Soundkey bellow.

	SoundKey("BUAFL.bmp",
			 "letter_B.bmp",
			 "Throw.wav",
			 Vertex(   0.0f, 16.0f),
			 SDLK_f),

	SoundKey("paddle.bmp",
			 "letter_p.bmp", 
			 "hit.wav",
			 Vertex( 150.0f, 16.0f),
			 SDLK_p)
};

const int SOUNDS = sizeof(sound_key) / sizeof(SoundKey);

void quit(int code)
{
	Mix_CloseAudio();
    SDL_Quit();
    exit(code);
}

void handle_key(SDL_keysym *key, bool down)
{
    if (key->sym == SDLK_ESCAPE)
	{
        quit(0);
	}
	else
	{
		for (int i = 0; i < SOUNDS; i++)
		{
			if (key->sym == sound_key[i].keycode)
			{
				if (!sound_key[i].down && down && sound_key[i].stream)
				{
					const int AUTO_SELECT_CHANNEL = -1;
					const int NO_LOOP = 0;
					const int PLAY_TO_END = -1;

					Mix_PlayChannelTimed(AUTO_SELECT_CHANNEL,
										 sound_key[i].stream, 
										 NO_LOOP, 
										 PLAY_TO_END);
				}
				sound_key[i].down = down;
			}
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
        case SDL_KEYDOWN:
            handle_key(&evnt.key.keysym, true);
            break;
		case SDL_KEYUP:
            handle_key(&evnt.key.keysym, false);
			break;
        case SDL_QUIT:
            quit(0);
            break;
        }
    }
}

void start_render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void send_vertex(const Vertex &UV, const Vertex &pos)
{
	glTexCoord2fv(UV.coordinate); 
	glVertex2fv(pos.coordinate);
}

void draw_bitmap(GLuint texture, const Vertex &pos, GLfloat size)
{
	const Vertex vertex[4] =
	{
		Vertex(pos.coordinate[0] - size, pos.coordinate[1] + size ),
		Vertex(pos.coordinate[0] + size, pos.coordinate[1] + size ),
		Vertex(pos.coordinate[0] + size, pos.coordinate[1] - size ),
		Vertex(pos.coordinate[0] - size, pos.coordinate[1] - size )
	};

	const Vertex UV[4] =
	{
		Vertex(0.0f, 0.0f),
		Vertex(1.0f, 0.0f),
		Vertex(1.0f, 1.0f),
		Vertex(0.0f, 1.0f)
	};

	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLES);
	glColor3ubv(white.channels);

	send_vertex(UV[0], vertex[0]);
	send_vertex(UV[1], vertex[1]);
	send_vertex(UV[2], vertex[2]);

	send_vertex(UV[2], vertex[2]);
	send_vertex(UV[3], vertex[3]);
	send_vertex(UV[0], vertex[0]);

    glEnd();
}

void draw(const SoundKey &key)
{
	const GLfloat NORMAL_IMAGE_SIZE = 50.0f;
	const GLfloat ZOOM_IMAGE_SIZE	= 70.0f;
	const GLfloat PROMPT_SIZE		= 16.0f;

	GLfloat size;
	if (key.down)
	{
		size = ZOOM_IMAGE_SIZE;
	}
	else
	{
		size = NORMAL_IMAGE_SIZE;
	}

	Vertex pos = key.pos;

	draw_bitmap(key.image, pos, size);

	pos.coordinate[0] -= ZOOM_IMAGE_SIZE;
	pos.coordinate[1] -= ZOOM_IMAGE_SIZE + PROMPT_SIZE;
	size = PROMPT_SIZE;

	draw_bitmap(key.letter, pos, size);
}

void end_render(void)
{
    SDL_GL_SwapBuffers();
}

void setup_opengl(GLdouble width, GLdouble height)
{
    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	const GLdouble left = -width / 2.0;
	const GLdouble right = width / 2.0;
	const GLdouble top = height / 2.0;
	const GLdouble bottom = -height / 2.0;
	const GLdouble front = 0.0;
	const GLdouble back = 100.0;

	glOrtho(left, right, bottom, top, front, back);

	glEnable(GL_TEXTURE_2D);
}

void load_bitmap(const char *bitmap_filename)
{
	SDL_Surface *surface = SDL_LoadBMP(bitmap_filename);
	if (surface)
	{
		const GLint MIPMAP_LEVEL = 0;
		const GLint NO_BORDER = 0;
		
		glTexImage2D(GL_TEXTURE_2D,
					 MIPMAP_LEVEL,
					 GL_RGB8,
					 surface->w,
					 surface->h,
					 NO_BORDER,
					 GL_BGR_EXT,
					 GL_UNSIGNED_BYTE,
					 surface->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SDL_FreeSurface(surface);
	}
	else
	{
		printf("Failed to load bitmap file: %s\n", bitmap_filename);
	}
}

void load(SoundKey &key)
{
	glGenTextures(1, &key.image);
	glGenTextures(1, &key.letter);

	glBindTexture(GL_TEXTURE_2D, key.image);
	load_bitmap(key.image_bitmap);

	glBindTexture(GL_TEXTURE_2D, key.letter);
	load_bitmap(key.letter_bitmap);

	key.stream = Mix_LoadWAV(key.audio);
	if (!key.stream)
	{
		printf("Failed to load audio file: %s\n", key.audio);
	}
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
	{
		printf("Video initialization failed: %s\n", SDL_GetError());
        quit(1);
    }

	const int FREQUENCY = 44100;
	const int STEREO = 2;
	const int BUFFER_SIZE = 1024;

	if (Mix_OpenAudio(FREQUENCY, AUDIO_S16, STEREO, BUFFER_SIZE))
	{
		printf("Unable to open audio!\n");
		quit(1);
	}

	const SDL_VideoInfo *info = SDL_GetVideoInfo();
    if (!info) 
	{
		printf("Video query failed: %s\n", SDL_GetError());
        quit(1);
    }

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	int width = 640;
    int height = 480;
    int bpp = info->vfmt->BitsPerPixel;
	Uint32 flags = SDL_OPENGL;

	if (SDL_SetVideoMode(width, height, bpp, flags) == 0) 
	{
		printf("Video mode set failed: %s\n", SDL_GetError());
        quit(1);
    }

	setup_opengl(GLdouble(width), GLdouble(height));

	int i = 0;
	for (i = 0; i < SOUNDS; i++)
	{
		load(sound_key[i]);
	}

	while (true) 
	{
		process_events();
		start_render();
		for (i = 0; i < SOUNDS; i++)
		{
			draw(sound_key[i]);
		}
		end_render();
    }

	return 0;
}
