#include <windows.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <GL/gl.h>
#include <cstring>

bool pause = false;
bool frame_advance = false;
bool reset_object = true;
int count = 0;
const int MAXIMUM_COMMAND_LENGTH = 80;
char answer[MAXIMUM_COMMAND_LENGTH];
bool first = true;
bool keyPressLeft = false;
bool keyPressRight;
bool keyPressSpace = false;

struct Colour
{
	GLubyte channels[3]; // RGB
	Colour(GLubyte r, GLubyte g, GLubyte b)
	{
		channels[0] = r;
		channels[1] = g;
		channels[2] = b;
	}
};

const Colour white  (255, 255, 255);

struct Point
{
	GLfloat coordinate[2]; // XY
	Point(GLfloat x, GLfloat y)
	{
		coordinate[0] = x;
		coordinate[1] = y;
	}
};

struct Vector
{
	GLfloat coordinate[2]; // XY
	Vector(GLfloat x, GLfloat y)
	{
		coordinate[0] = x;
		coordinate[1] = y;
	}
};

struct Object
{
	GLuint image;
	GLfloat position[2];
	GLfloat velocity[2];
	GLfloat radius;
	Mix_Chunk *sound;
};

void quit(int code)
{
	Mix_CloseAudio();
    SDL_Quit();
    exit(code);
}

void handle_key(SDL_keysym *key, Object &object)
{
    switch (key->sym)
	{
	case SDLK_LEFT:
		keyPressLeft = true;
		break;
	//case SDLK_RIGHT:
	//	object.position[0]++;
	//	break;
	case SDLK_SPACE:
		keyPressSpace = true;
		break;
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
		reset_object = true;
		break;
	}
}

void process_events(void)
{
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt, Object &object)) 
	{
        switch (evnt.type) 
		{
		//case SDL_KEYUP:
        //    handle_key(&evnt.key.keysym, ball);
		//	break;
		case SDL_KEYDOWN:
			handle_key(&evnt.key.keysym, ball);
			break;
        cawse SDL_QUIT:
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

void draw(const Object &object)
{
	const GLfloat size = object.radius;

	const Point vertex[] =
	{
		Point(object.position[0] - size, object.position[1] + size ),
		Point(object.position[0] + size, object.position[1] + size ),
		Point(object.position[0] + size, object.position[1] - size ),
		Point(object.position[0] - size, object.position[1] - size )
	};

	const Point UV[] =
	{
		Point(0.0f, 0.0f),
		Point(1.0f, 0.0f),
		Point(1.0f, 1.0f),
		Point(0.0f, 1.0f)
	};

	const int index[] = 
	{ 
		0, 1, 2, 
		2, 3, 0 
	};

	const int NUMBER_OF_VERTS = sizeof(index) / sizeof(index[0]);

	glBindTexture(GL_TEXTURE_2D, object.image);
	glBegin(GL_TRIANGLES);
	glColor3ubv(white.channels);

	for (int i = 0; i < NUMBER_OF_VERTS; i++)
	{
		glTexCoord2fv(UV	[index[i]].coordinate);
		glVertex2fv	 (vertex[index[i]].coordinate);
	}

	glEnd();
}

void end_render(void)
{
    SDL_GL_SwapBuffers();
}

const int SCREEN_WIDTH	= 640;
const int SCREEN_HEIGHT	= 480;

const GLdouble SCREEN_LEFT	 =  -SCREEN_WIDTH / 2.0;
const GLdouble SCREEN_RIGHT	 =   SCREEN_WIDTH / 2.0;
const GLdouble SCREEN_TOP	 =  SCREEN_HEIGHT / 2.0;
const GLdouble SCREEN_BOTTOM = -SCREEN_HEIGHT / 2.0;

const GLdouble SCREEN_FRONT	=   0.0;
const GLdouble SCREEN_BACK	= 100.0;

void setup_opengl(void)
{
    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glOrtho(SCREEN_LEFT, 
			SCREEN_RIGHT, 
			SCREEN_BOTTOM, 
			SCREEN_TOP, 
			SCREEN_FRONT, 
			SCREEN_BACK);

	glEnable(GL_TEXTURE_2D);
}

void load_texture(GLuint &image, const char *bitmap_filename)
{
	glGenTextures(1, &image);
	glBindTexture(GL_TEXTURE_2D, image);

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

void load_audio(Mix_Chunk *&sound, const char *audio_filename)
{
	sound = Mix_LoadWAV(audio_filename);
	if (!sound)
	{
		printf("Failed to load audio file: %s\n", audio_filename);
	}
}

void play_sound(const Object &object)
{
	const int AUTO_SELECT_CHANNEL = -1;
	const int NO_LOOP = 0;
	const int PLAY_TO_END = -1;

		Mix_PlayChannelTimed(AUTO_SELECT_CHANNEL,
							 object.sound, 
							 NO_LOOP, 
							 PLAY_TO_END);
}

void set_start(Object &object)
{
	object.position[0] = 0.0f;
	object.position[1] = -240.0f + object.radius;
	object.velocity[0] = 0.0f;
	object.velocity[1] = 0.0f;
}

const GLfloat BASE = GLfloat(SCREEN_BOTTOM);
const GLfloat LEFT = GLfloat(SCREEN_LEFT);
const GLfloat RIGHT = GLfloat(SCREEN_RIGHT);

GLfloat distance_to_bottom(const Object &object)
{
	return (object.position[1] - object.radius) - BASE;
}

GLfloat distance_to_left(const Object &object)
{
	return (object.position[0] - object.radius) - LEFT;
}

GLfloat distance_to_right(const Object &object)
{
	return (object.position[0] + object.radius) - RIGHT;
}

void moveBallLeft(Object &object)
{
	object.position[0] -= 20;
}

void jumpBall(Object &object)
{
	object.velocity[1] = 75.0f;

}

void update(Object &object, float t)
{
	object.position[0] += object.velocity[0] * t;
	object.position[1] += object.velocity[1] * t;

	GLfloat dtb = distance_to_bottom(object);
	GLfloat dtl = distance_to_left(object);
	GLfloat dtr = distance_to_right(object);

	if (dtb < 0.0f)
	{
		object.position[1] = BASE + object.radius - dtb;
		object.velocity[1] = 0.0f;
	}
	if (dtl < 0.0f)
	{
		play_sound(object);
		object.position[0] = LEFT + object.radius - dtl;
		object.velocity[0] *= -1.0f;
	}
	else if (dtr > 0.0f)
	{
		play_sound(object);
		object.position[0] = RIGHT - object.radius + dtr;
		object.velocity[0] *= -1.0f;
	}

	object.velocity[1] -= 75.0f * t;
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

		const int bpp = info->vfmt->BitsPerPixel;
		const Uint32 flags = SDL_OPENGL;

		if (SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, bpp, flags) == 0) 
		{
			printf("Video mode set failed: %s\n", SDL_GetError());
			quit(1);
		}

		setup_opengl();

		Object ball;

		load_texture(ball.image, "ball.bmp");
		load_audio(ball.sound, "bounce.wav");
		ball.radius = 40.0f;


		while (true) 
		{
			const int UPDATES = 10;
			const float t = 1.0f / float(60 * UPDATES);

			process_events(ball);
			if (reset_object)
			{
				set_start(ball);
				reset_object = false;
			}
			else if (!pause || frame_advance)
			{
				for (int i = 0; i < UPDATES; i++)
				{
					update(ball, t);
				}
				frame_advance = false;
			}
			else if (keyPressLeft)
			{
				moveBallLeft(ball);
				keyPressLeft = false;
			}
			else if (keyPressSpace)
			{
				jumpBall(ball);
				keyPressSpace = false;
			}
			start_render();
			draw(ball);
			end_render();
		}
	}

