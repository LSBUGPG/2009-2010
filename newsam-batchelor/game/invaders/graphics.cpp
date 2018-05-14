#include "graphics.h"

#include <SDL.h>
#include <SDL_ttf.h>

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

TTF_Font *font = 0;

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
	
	if (TTF_Init() == -1)
	{
		printf("Font init failed: %s\n", TTF_GetError());
		return false;
	}

	font = TTF_OpenFont("VeraMoBd.ttf", 16);

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	return true;
}

void load_texture(GLuint &image, SDL_Surface *surface)
{
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

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		SDL_FreeSurface(surface);
	}
	else
	{
		printf("Failed to load bitmap file: %s\n", bitmap_filename);
	}
}

void load_text_line(Image &image, const char *text)
{
	glGenTextures(1, &image.texture);
	glBindTexture(GL_TEXTURE_2D, image.texture);

	if (font)
	{
		int width = 8;
		int height = 8;

		SDL_Color col = {255, 255, 255};

		SDL_Surface *surface = 
			TTF_RenderUTF8_Blended(font, text, col);

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

		image.dimension[0] = GLfloat(surface->w) / 4.0f;
		image.dimension[1] = GLfloat(surface->h) / 4.0f;

		SDL_FreeSurface(surface);
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
