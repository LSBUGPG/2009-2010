#include <windows.h>
#include <GL/gl.h>

void init_score(void);
void draw_score(int score, const GLfloat *position);
void add_point(int &score);
void minus_point(int &score);
