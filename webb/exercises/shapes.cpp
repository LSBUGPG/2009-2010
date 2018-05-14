#include <windows.h>
#include <SDL.h>
#include <GL/gl.h>

struct triangle
{
	GLubyte colour[3]; // RGB
	GLfloat point[3][2]; // 3 * XY points
};

const triangle t[] = 
{
	{ 
		{ 0, 0, 200 }, // blue
		{
			{  200.0f,  200.0f }, // point 1
			{ -200.0f,  200.0f }, // point 2
			{    0.0f, -200.0f }  // point 3
		}
	},
	{ 
		{ 200, 0, 0 }, // red
		{
			{    0.0f,  100.0f }, // point 1
			{  100.0f, 0.0f }, // point 2
			{ -100.0f, 0.0f }  // point 3
		}
	},

	{ 
		{ 0, 0, 200 }, // blue
		{
			{ -50.0f,   100.0f }, // point 1
			{ 50.0f,   100.0f }, // point 2
			{    0.0f, 0.0f }  // point 3
		}
	}
};

const triangle *star[] = 
{ 
	&t[0], 
	&t[1], 
	&t[2],
	0 
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

void draw_screen(const triangle *shape[])
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_TRIANGLES);

    while (*shape)
	{
		glColor3ubv((*shape)->colour);

		for (int p = 0; p < 3; p++)
		{
			glVertex2fv((*shape)->point[p]);
		}
		shape++;
	}

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
}

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
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

	while (true) 
	{
		process_events();
		draw_screen(star);
    }

	return 0;
}
