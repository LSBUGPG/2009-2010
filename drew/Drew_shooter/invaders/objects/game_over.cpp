#include "game_over.h"

#include "../object.h"
#include "../graphics.h"

struct GameOver: public Object
{
	Image image;

	void update(void) {}

	void draw(void) 
	{
		GLfloat pos[] = { 0.f, 0.f };
		::draw(image, pos);
	}
};

GameOver game_over;

void load_game_over(void)
{


	load_texture(game_over.image.texture, "GameOver.bmp");
	game_over.image.dimension[0] = 256;
	game_over.image.dimension[1] = 192;

}

Object **add_game_over(Object **object_array)
{
	*object_array = &game_over;
	object_array++;

	return object_array;
}
