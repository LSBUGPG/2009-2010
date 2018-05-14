#include <windows.h>
#include <SDL.h>
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

void quit(int code)
{
    SDL_Quit();
    exit(code);
}

void handle_key_down(SDL_keysym *key)
{
    switch (key->sym) 
	{
    case SDLK_ESCAPE:
        quit(0);
        break;
    default:
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
        case SDL_KEYDOWN:
            handle_key_down(&evnt.key.keysym);
            break;
        case SDL_QUIT:
            quit(0);
            break;
        }
    }
}

void send_vertex(const Vertex &UV, const Vertex &pos)
{
	glTexCoord2fv(UV.coordinate); 
	glVertex2fv(pos.coordinate);
}

void draw_screen(GLuint texture)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	GLfloat size = 50.0f;

	const Vertex vertex[4] =
	{
		Vertex(-size,  size ),
		Vertex( size,  size ),
		Vertex( size, -size ),
		Vertex(-size, -size )
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

void load_bitmap(const char *bitmap)
{
	SDL_Surface *surface = SDL_LoadBMP(bitmap);
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
		printf("Failed to load bitmap file: %s\n", bitmap);
	}
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
	{
		printf("Video initialization failed: %s\n", SDL_GetError());
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

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	load_bitmap("ball.bmp");

	while (true) 
	{
		process_events();
		draw_screen(texture);
    }

	return 0;
}
