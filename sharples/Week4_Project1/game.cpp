#include <windows.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <GL/gl.h>

bool pause = false;
bool frame_advance = false;
bool reset_ball = true;
bool left = false;
bool right = false;
bool jump = false;
bool down = false;

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
	GLuint image[3];
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

void handle_key(SDL_keysym *key)
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
		case SDLK_f:
			frame_advance = true;
			break;
		case SDLK_r:
			reset_ball = true;
			break;
		case SDLK_LEFT:
			left = true;
			break;
		case SDLK_RIGHT:
			right = true;
			break;
		case SDLK_SPACE:
			jump = true;
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
			down = false;
            handle_key(&evnt.key.keysym);
			break;
		case SDL_KEYDOWN:
			down = true;
			handle_key(&evnt.key.keysym);
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

void draw(const Object &ball)
{
	const GLfloat size = ball.radius;

	const Point vertex[] =
	{
		Point(ball.position[0] - size, ball.position[1] + size ),
		Point(ball.position[0] + size, ball.position[1] + size ),
		Point(ball.position[0] + size, ball.position[1] - size ),
		Point(ball.position[0] - size, ball.position[1] - size )
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

	glBindTexture(GL_TEXTURE_2D, ball.image[1]);
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

void play_audio(Object &ball)
{
		const int AUTO_SELECT_CHANNEL = -1;
		const int NO_LOOP = 0;
		const int PLAY_TO_END = -1;

					Mix_PlayChannelTimed(AUTO_SELECT_CHANNEL,
										 ball.sound, 
										 NO_LOOP, 
										 PLAY_TO_END);
}

void set_start(Object &ball, Object &bg, Object &platform)
{
	ball.position[0] = 0.0f;
	ball.position[1] = SCREEN_HEIGHT / 2 * -1 + ball.radius;
	ball.velocity[0] = 0.0f;
	ball.velocity[1] = -900.0f;
	bg.position[0] = 0.0f;
	bg.position[1] = 0.0f;
	platform.position[0] = 0.0f;
	platform.position[1] = 0.0f;
}

const GLfloat BASE = GLfloat(SCREEN_BOTTOM);
const GLfloat LEFT = GLfloat(SCREEN_LEFT);
const GLfloat RIGHT = GLfloat(SCREEN_RIGHT);

GLfloat distance_to_bottom(const Object &ball)
{
	return (ball.position[1] - ball.radius) - BASE;
}
GLfloat distance_to_left(const Object &ball)
{
	return (ball.position[0] - ball.radius) - LEFT;
}
GLfloat distance_to_right(const Object &ball)
{
	return (ball.position[0] + ball.radius) - RIGHT;
}

void keyEvent(Object &ball, float t)
{
	ball.position[0] += ball.velocity[0] * t;
	ball.position[1] += ball.velocity[1] * t;

	if (left)
	{
		ball.position[0] -= 20.0f;
		left = false;
	}
	else if (right)
	{
		ball.position[0] += 20.0f;
		right = false;
	}
	//else if (jump)
	//{
	//	ball.velocity[1] *= -1.0f * t;
	//	jump = false;
	//}
}

void update(Object &ball, Object &platform, float t)
{
	int i = 0;
	ball.position[0] += ball.velocity[0] * t;
	ball.position[1] += ball.velocity[1] * t;

	GLfloat dtb = distance_to_bottom(ball);
	GLfloat dtl = distance_to_left(ball);
	GLfloat dtr = distance_to_right(ball);

	GLfloat ballCollider = ball.position[0];
	GLfloat platformCollider = platform.position[0];

	if (dtb < 0.0f)
	{
		ball.position[1] = BASE + ball.radius - dtb;
		//ball.velocity[1] = 0.0f;
	}
	else if (dtl < 0.0f)
	{
		play_audio(ball);

		ball.position[0] = LEFT + ball.radius;
		//ball.velocity[0] = 0.0f;
	}
	else if (dtr > 0.0f)
	{
		play_audio(ball);

		ball.position[0] = RIGHT - ball.radius;
		//ball.velocity[0] = 0.0f;
	}
	else if (ballCollider == platformCollider)
	{
		ball.velocity[1] = 0.0f;
	}

	if (jump)
	{
		while (i < 60)
		{
			ball.velocity[1] = 9000.0f * t;
			i++;
		}
		i = 0;
		ball.velocity[1] = -9000.0f * t;
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

    const int bpp = info->vfmt->BitsPerPixel;
	const Uint32 flags = SDL_OPENGL;

	if (SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, bpp, flags) == 0) 
	{
		printf("Video mode set failed: %s\n", SDL_GetError());
        quit(1);
    }

	setup_opengl();

	Object ball;
	load_texture(ball.image[1], "ball.bmp");
	load_texture(ball.image[2], "ball2.bmp");
	load_texture(ball.image[3], "ball3.bmp");
	load_audio(ball.sound, "bounce.wav");
	ball.radius = 40.0f;

	Object bg;
	load_texture(bg.image[1], "bg.bmp");
	bg.radius = 320.0f;

	Object platform;
	load_texture(platform.image[1], "platform.bmp");
	platform.radius = 20.0f;
	

	while (true) 
	{
		const int UPDATES = 10;
		const float t = 1.0f / float(60 * UPDATES);

		process_events();
		keyEvent(ball, t);
		if (reset_ball)
		{
			set_start(ball, bg, platform);
			reset_ball = false;
		}
		else if (!pause || frame_advance)
		{
			for (int i = 0; i < UPDATES; i++)
			{
				update(ball, platform, t);
			}
			frame_advance = false;
		}
		start_render();
		draw(bg);
		draw(platform);
		draw(ball);
		end_render();
    }

	return 0;
}
