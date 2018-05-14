#include <windows.h>
#include <GL/gl.h>

const int SCREEN_WIDTH	= 620;
const int SCREEN_HEIGHT	= 480;

const GLdouble SCALE = 0.5f;
const GLdouble SCREEN_LEFT	 =  -SCREEN_WIDTH / 2.0 * SCALE;
const GLdouble SCREEN_RIGHT	 =   SCREEN_WIDTH / 2.0 * SCALE;
const GLdouble SCREEN_TOP	 =  SCREEN_HEIGHT / 2.0 * SCALE;
const GLdouble SCREEN_BOTTOM = -SCREEN_HEIGHT / 2.0 * SCALE;

const GLdouble SCREEN_FRONT	=   0.0;
const GLdouble SCREEN_BACK	= 100.0;

struct Point
{
	GLfloat coordinate[2]; // XY
	Point(GLfloat x, GLfloat y)
	{
		coordinate[0] = x;
		coordinate[1] = y;
	}
};

struct Image
{
	GLuint texture;
	GLfloat dimension[2];
};

struct SDL_Surface;

bool init_graphics(void);
void load_texture(GLuint &image, const char *bitmap_filename);
void load_text_line(Image &image, const char *text);
void end_render(void);
void draw(const Image &image, const GLfloat *position);
void start_render(void);
