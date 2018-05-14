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
	const char *audio;
	SDLKey keycode;
	SDLKey answer;
	bool down;
	Vertex pos;

	SoundKey(const char *image_bitmap_filename,
			 const char *audio_filename,
			 const Vertex &bitmap_offset, 
			 SDLKey activate_keycode,
			 SDLKey valid_answer)
	{
		image_bitmap = image_bitmap_filename;
		audio = audio_filename;
		keycode = activate_keycode;
		down = false;
		pos = bitmap_offset;
		answer = valid_answer;
	}
};

SoundKey sound_key[] =
{
	SoundKey("1.bmp",
	         "TR1.wav",
			 Vertex(-450.0f, 700.0f),
			 SDLK_a,
			 SDLK_3),

	SoundKey("3.bmp",
			 "StreetsOfRage3.wav",
			 Vertex(150.0f, 700.0f),
			 SDLK_c,
			 SDLK_1),

    SoundKey("2.bmp", 
			 "Sonic2.wav",
		  	 Vertex(-150.0f, 700.0f),
			 SDLK_b,
			 SDLK_6),

    SoundKey("4.bmp", 
		"Audio2.wav",
		Vertex(450.0f, 700.0f),
		SDLK_d,
			 SDLK_2),

    SoundKey("5.bmp", 
		"TR4.wav",
		Vertex(-450.0f, 400.0f),
		SDLK_e,
			 SDLK_3),

    SoundKey("6.bmp", 
		"StreetsOfRage5.wav",
		Vertex(-150.0f, 400.0f),                                                                                                                                                                                                                                                                                                                                                                     
		SDLK_f,
			 SDLK_1),

    SoundKey("7.bmp", 
		"Banjo1.wav",
		Vertex(150.0f, 400.0f),
		SDLK_g,
			 SDLK_4),

     SoundKey("8.bmp", 
		"Crash2.wav",
		Vertex(450.0f, 400.0f),
		SDLK_h,
			 SDLK_7),

     SoundKey("9.bmp", 
		"Audio.wav",
		Vertex(-450.0f, 100.0f),
		SDLK_i,
			 SDLK_2),

     SoundKey("10.bmp", 
		"Sonic3.wav",
		Vertex(-150.0f, 100.0f),
		SDLK_j,
			 SDLK_6),

   SoundKey("11.bmp", 
		"Gears of War.wav",
		Vertex(150.0f, 100.0f),
		SDLK_k,
			 SDLK_5),

     SoundKey("12.bmp", 
		"Lar_die2.wav",
		Vertex(450.0f, 100.0f),
		SDLK_l,
			 SDLK_3),

 SoundKey("13.bmp", 
		"Audio5.wav",
		Vertex(-450.0f, -200.0f),
		SDLK_m,
			 SDLK_2),

     SoundKey("14.bmp", 
		"Audio6.wav",
		Vertex(-150.0f, -200.0f),
		SDLK_n,
			 SDLK_2),

   SoundKey("15.bmp", 
		"StreetsOfRage6.wav",
		Vertex(150.0f, -200.0f),
		SDLK_o,
			 SDLK_1),

     SoundKey("16.bmp", 
		"medi_fix.wav",
		Vertex(450.0f, -200.0f),
		SDLK_p,
			 SDLK_3),


}; 

int selected_sound = -1;

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

					selected_sound = i;
				}
				sound_key[i].down = down;
			}
		}

		if (selected_sound >= 0 && key->sym == sound_key[selected_sound].answer)
		{
			printf("score a point\n");
			// score a point
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

void draw_bitmap(GLuint texture, const Vertex &pos, GLfloat w, GLfloat h)
{
	const Vertex vertex[4] =
	{
		Vertex(pos.coordinate[0] - w, pos.coordinate[1] + h ),
		Vertex(pos.coordinate[0] + w, pos.coordinate[1] + h ),
		Vertex(pos.coordinate[0] + w, pos.coordinate[1] - h ),
		Vertex(pos.coordinate[0] - w, pos.coordinate[1] - h )
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

	draw_bitmap(key.image, pos, size, size);
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

	const GLdouble left = -width / 1.0;
	const GLdouble right = width / 1.0;
	const GLdouble top = height / 1.0;
	const GLdouble bottom = -height / 1.0;
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

	int width = 800;
    int height = 800;
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

	GLuint prompt;
	glGenTextures(1, &prompt);
	glBindTexture(GL_TEXTURE_2D, prompt);
	load_bitmap("Games.bmp");

	while (true) 
	{
		process_events();
		start_render();
		for (i = 0; i < SOUNDS; i++)
		{
			draw(sound_key[i]);
		}
		if (selected_sound >= 0)
		{
			draw_bitmap(prompt, Vertex(0.0f, -600.0f), 764.0f, 245.0f);
			// draw prompt if sound selected
		}
		end_render();
    }

	return 0;
}
