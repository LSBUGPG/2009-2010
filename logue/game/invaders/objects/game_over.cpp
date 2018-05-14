#include "game_over.h"

#include "../object.h"
#include "../graphics.h"

struct GameOver: public Object
{
	Image message;

	void update(void) {}

	void draw(void) 
	{
		GLfloat pos[] = { 0.f, 0.f };
		::draw(message, pos);
	}
};

GameOver game_over;

void load_game_over(void)
{
	load_text_line(game_over.message, "The diseases spread too fast - you are dead!");
}

Object **add_game_over(Object **object_array)
{
	*object_array = &game_over;
	object_array++;

	return object_array;
}
