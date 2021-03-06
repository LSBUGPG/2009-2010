#include "graphics.h"

#include <SDL.h>

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

bool init_graphics(void)
{
	const SDL_VideoInfo *info = SDL_GetVideoInfo();
    if (!info) 
	{
		printf("Video query failed: %s\n", SDL_GetError());
        return false;
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
        return false;
    }
	
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

	return true;
}

void premultiply_alpha(SDL_Surface *surface)
{
	for (int x = 0; x < surface->w; x++)
	{
		for (int y = 0; y < surface->h; y++)
		{
			size_t offset = (y * surface->pitch + x * 4);
			unsigned char *channel = (unsigned char*)surface->pixels + offset;
												
			channel[0] = (channel[0] * channel[3]) / 255;
			channel[1] = (channel[1] * channel[3]) / 255;
			channel[2] = (channel[2] * channel[3]) / 255;
		}
	}
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
		
		GLint internal_format; // how GL should store the texture
		GLint bitmap_format;   // the layout of the data in the bitmap

		if (surface->format->BitsPerPixel == 32)
		{
			premultiply_alpha(surface);

			internal_format = GL_RGBA8;
			bitmap_format = GL_BGRA_EXT;
		}
		else
		{
			internal_format = GL_RGB8;
			bitmap_format = GL_BGR_EXT;
		}

		glTexImage2D(GL_TEXTURE_2D,
					 MIPMAP_LEVEL,
					 internal_format,
					 surface->w,
					 surface->h,
					 NO_BORDER,
					 bitmap_format,
					 GL_UNSIGNED_BYTE,
					 surface->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		SDL_FreeSurface(surface);
	}
	else
	{
		printf("Failed to load bitmap file: %s\n", bitmap_filename);
	}
}


void start_render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw(const Image &image, const GLfloat *position)
{
	const Point vertex[] =
	{
		Point(position[0] - image.dimension[0], position[1] + image.dimension[1] ),
		Point(position[0] + image.dimension[0], position[1] + image.dimension[1] ),
		Point(position[0] + image.dimension[0], position[1] - image.dimension[1] ),
		Point(position[0] - image.dimension[0], position[1] - image.dimension[1] )
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

	glBindTexture(GL_TEXTURE_2D, image.texture);
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
