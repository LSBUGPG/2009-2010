#include "object.h"
#include "graphics.h"
#include "mother.h"
#include "game.h"

const int MOTHER_WIDTH = 16;
const int MOTHER_HEIGHT = 8;

int MOTHER_START_X = PLAY_FIELD_LEFT - MOTHER_WIDTH * 50;
int MOTHER_START_Y = PLAY_FIELD_TOP - MOTHER_HEIGHT * 2;


struct Mother: public Object
{
	Image image;
	int position[2];
	bool alive;


	void update(void)
	{
		if(MOTHER_START_X > PLAY_FIELD_RIGHT + MOTHER_WIDTH)
		{
			MOTHER_START_X = PLAY_FIELD_LEFT - MOTHER_WIDTH * 50;
		}
	

		MOTHER_START_X++;

	
	}

	void draw(void)


	{   alive = true;
		GLfloat fpos[] = { MOTHER_START_X, MOTHER_START_Y };
		if (alive)
		{
			::draw(image, fpos);
		}
	}

};

Mother mother;

int load_mother(Object *object_array[])
{
	load_texture(mother.image.texture, "Mother01.bmp");
	mother.image.dimension[0] = MOTHER_WIDTH / 2;
	mother.image.dimension[1] = MOTHER_HEIGHT / 2;
	
	*object_array = &mother;
	object_array++;
	return MOTHER_TOTAL;
}