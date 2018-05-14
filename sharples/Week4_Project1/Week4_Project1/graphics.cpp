#include "game.h"

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