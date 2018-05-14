#include <windows.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <GL/gl.h>

bool pause = true;
bool frame_advance = false;
bool reset_object = true;
bool wall_sound = false;
bool hit_sound = false;
bool move_left_top = false;
bool move_right_top = false;
bool move_left_bottom = false;
bool move_right_bottom = false;

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

struct Ball
{
	GLuint image;
	GLfloat position[2];
	GLfloat velocity[2];
	GLfloat radius;
	Mix_Chunk *sound;
	Mix_Chunk *hitSound;
};

struct Paddle
{
	GLuint image;
	GLfloat position[2];
	GLfloat radius;
	Mix_Chunk *sound;
	Mix_Chunk *hitSound;
};

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

	switch (key->sym)
	{
	case SDLK_a:
		move_left_top = down;
		break;
	case SDLK_d:
		move_right_top = down;
		break;
	case SDLK_LEFT:
		move_left_bottom = down;
		break;
	case SDLK_RIGHT:
		move_right_bottom = down;
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

void start_render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw(const GLuint image, GLfloat *position, GLfloat radius)
{
	const GLfloat size = radius;

	const Point vertex[] =
	{
		Point(position[0] - size, position[1] + size ),
		Point(position[0] + size, position[1] + size ),
		Point(position[0] + size, position[1] - size ),
		Point(position[0] - size, position[1] - size )
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

	glBindTexture(GL_TEXTURE_2D, image);
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
	const Uint32 one_frame = 16;
	static Uint32 frame_start_time = 0;
	Uint32 now = SDL_GetTicks();
	int wait = min(one_frame, (frame_start_time + one_frame) - now);
	if (wait > 0)
	{
		SDL_Delay(wait);
		now += wait;
	}
	frame_start_time = now;
    SDL_GL_SwapBuffers();
}

const int SCREEN_WIDTH	= 500;
const int SCREEN_HEIGHT	= 800;

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

void set_start(Ball &object)
{
	object.position[0] = 0.0f;
	object.position[1] = 0.0f;
	object.velocity[0] = 100.0f;
	object.velocity[1] = 100.0f;
}
void set_paddle_top(Paddle &object)
{
	object.position[0] = 0.0f;
	object.position[1] = 300.0f;
}

void set_paddle_bottom(Paddle &object)
{
	object.position[0] = 0.0f;
	object.position[1] = -300.0f;
}

const GLfloat BASE = GLfloat(SCREEN_BOTTOM);
const GLfloat LEFT = GLfloat(SCREEN_LEFT);
const GLfloat RIGHT = GLfloat(SCREEN_RIGHT);
const GLfloat TOP = GLfloat(SCREEN_TOP);

GLfloat distance_to_bottom(const Ball &object)
{
	return (object.position[1] - object.radius) - BASE;
};
GLfloat distance_to_left(const Ball &object)
{
return (object.position[0] - object.radius) - LEFT;
};
GLfloat distance_to_right(const Ball &object)
	{
		return (object.position[0] + object.radius) - RIGHT;
	};
GLfloat distance_to_top(const Ball &object)
{
	return (object.position[1] + object.radius) - TOP;
};

void update_ball(Ball &object, float t)
{
	object.position[0] += object.velocity[0] * t;
	object.position[1] += object.velocity[1] * t;

	GLfloat d = distance_to_bottom(object);
	GLfloat l = distance_to_left(object);
	GLfloat r = distance_to_right(object);
	GLfloat c = distance_to_top(object);
	
	if (d < 0.0f)
	{
		object.position[1] = BASE + object.radius - d;
		object.velocity[1] *= -1.0f;
		wall_sound = true;

	}
	 if	(l < 0.0f)
	{
		object.position[0] = LEFT + object.radius - l;
		object.velocity[0]  *= -1.0f;
		wall_sound = true;
	}
	if	(r > 0.0f)
	{
		object.position[0] = RIGHT - object.radius - r;
		object.velocity[0]  *= -1.0f;
		wall_sound = true;
	}
	if	(c > 0.0f)
	{
		object.position[1] = TOP - object.radius - c;
		object.velocity[1]  *= -1.0f;
		wall_sound = true;
	}

	if (wall_sound)
	{
		const int AUTO_SELECT_CHANNEL = -1;
					const int NO_LOOP = 0;
					const int PLAY_TO_END = -1;

					Mix_PlayChannelTimed(AUTO_SELECT_CHANNEL,
										 object.sound, 
										 NO_LOOP, 
										 PLAY_TO_END);
			wall_sound = false;
	}
}

GLfloat square(GLfloat x)
{
	return x * x;
}

void update_paddle(Paddle &paddle, Ball &ball, bool left, bool right, float t)
{
	GLfloat dx = paddle.position[0] - ball.position[0];
	GLfloat dy = paddle.position[1] - ball.position[1];

	if (square(dx) + square(dy) < square(ball.radius + paddle.radius))
	{
		ball.velocity[0] *= -1.0f;
		ball.velocity[1] *= -1.0f;
	}

	if (left && paddle.position[0] > SCREEN_LEFT + paddle.radius)
	{
		paddle.position[0]-= paddle.radius * t * 7;
		hit_sound = true;
	}
				
	if (right && paddle.position[0] < SCREEN_RIGHT - paddle.radius)
	{
		paddle.position[0]+= paddle.radius * t * 7;
		hit_sound = true;
	}
	if (hit_sound)
	{
		const int AUTO_SELECT_CHANNEL = -1;
					const int NO_LOOP = 0;
					const int PLAY_TO_END = -1;

					Mix_PlayChannelTimed(AUTO_SELECT_CHANNEL,
										 paddle.hitSound, 
										 NO_LOOP, 
										 PLAY_TO_END);
					hit_sound = false;
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

	Ball ball;
	load_texture(ball.image, "puck.bmp");
	load_audio(ball.sound, "bounce.wav");
	load_audio(ball.hitSound, "hit.wav");
	ball.radius = 40.0f;

	Paddle paddle_top;
	load_texture(paddle_top.image, "paddle.bmp");
	load_audio(paddle_top.hitSound, "hit.wav");
	paddle_top.radius = 40.0f;

	Paddle paddle_bottom;
	load_texture(paddle_bottom.image, "paddle.bmp");
	load_audio(paddle_bottom.hitSound, "hit.wav");
	paddle_bottom.radius = 40.0f;

	while (true) 
	{
		const float t = 1.0f / 60.f;

		process_events();
		if (reset_object)
		{
			set_start(ball);
			set_paddle_top(paddle_top);
			set_paddle_bottom(paddle_bottom);
			reset_object = false;
		}
		else if (!pause || frame_advance)
		{
			update_ball(ball, t);
			update_paddle(paddle_top, ball, move_left_top, move_right_top, t);
			update_paddle(paddle_bottom, ball, move_left_bottom, move_right_bottom, t);
			frame_advance = false;
		}
		start_render();
		draw(ball.image, ball.position, ball.radius);
		draw(paddle_top.image, paddle_top.position, paddle_top.radius);
		draw(paddle_bottom.image, paddle_bottom.position, paddle_bottom.radius);
		end_render();
    }

	return 0;
}
