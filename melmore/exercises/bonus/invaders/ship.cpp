#include "object.h"
#include "graphics.h"
#include "ship.h"
#include "game.h"

const int SHIP_WIDTH = 24;
const int SHIP_HEIGHT = 16;



int SHIP_START_X = PLAY_FIELD_LEFT - SHIP_WIDTH * 50;
int SHIP_START_Y = PLAY_FIELD_TOP - SHIP_HEIGHT * 2;


struct Ship: public Object
{
	Image image;
	int position[2];
	bool alive;


	void update(void)
	{
		if(SHIP_START_X > PLAY_FIELD_RIGHT + SHIP_WIDTH)
		{
			SHIP_START_X = PLAY_FIELD_LEFT - SHIP_WIDTH * 50;
		}
	

		SHIP_START_X++;

	
	}

	void draw(void)


	{   alive = true;
		GLfloat fpos[] = { SHIP_START_X, SHIP_START_Y };
		if (alive)
		{
			::draw(image, fpos);
		}
	}

};

Ship ship;

int load_ship(Object *object_array[])
{
	load_texture(ship.image.texture, "ship.bmp");
	ship.image.dimension[0] = SHIP_WIDTH / 2;
	ship.image.dimension[1] = SHIP_HEIGHT / 2;
	
	*object_array = &ship;
	object_array++;
	return SHIP_TOTAL;
}