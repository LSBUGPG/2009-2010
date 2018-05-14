#include "laser.h"
#include "invader.h"
#include "level.h"

#include "../object.h"
#include "../audio.h"
#include "../graphics.h"
#include "../screen.h"
#include "../controls.h"

#include <stdio.h>

const int LEVEL_WIDTH = SCREEN_WIDTH;   // Stretched to near double size of original bmp
const int LEVEL_HEIGHT = 1346;          // Size needed for other maths. Need to replace direct numbers with figures used globally (+ 2 to force overlap)


int LEVEL_TOP_START_X = 0;              // set to zero as background should be aligned to middle
int LEVEL_TOP_START_Y = 192;			// Start position for level

int LEVEL_BOTTOM_START_X = 0;           // set to zero as background should be aligned to middle
int LEVEL_BOTTOM_START_Y = 1536;		// 8 * start position of the top part
int LOOP_MUSIC_FOREVER = -1;
	

struct Level: public Object
{
	Image image;
	int position[2];
	bool alive;


	void update(void)
	{



		if (alive)
		{
		position[1] --;
		position[1] --;

		}

		if (position[1] < -1152) // By my calculations this should be the perfect point to reset, but strangely I'm left with one pixel?
		{
			position[1] = LEVEL_BOTTOM_START_Y; // Moves level to top in order to re-scroll
			
		}

	}

	void draw(void)


	{   GLfloat fpos[2] = { GLfloat(position[0]), GLfloat(position[1]) };  
		if (alive)
		{
			::draw(image, fpos);
			
		}
	}

};

Level level;


void load_level(void)
{

		load_texture(level.image.texture, "Level01-Top.bmp"); //Loads texture for level
		level.image.dimension[0] = LEVEL_WIDTH / 2;
		level.image.dimension[1] = LEVEL_HEIGHT / 2;

		
		level.position[0] = LEVEL_TOP_START_X;
		level.position[1] = LEVEL_TOP_START_Y;



}

Object **add_level(Object **object_array)
{
	*object_array = &level;
	object_array++;

	return object_array;
}

void reset_level(void)  
{
	
	level.alive = true;
	level.position[0] = LEVEL_TOP_START_X;
	level.position[1] = LEVEL_TOP_START_Y;

	// ******************************************************* PLACE MUSIC RELEASE IN HERE *********************************************//
	
}


//           ***************************************** SECOND PART OF LEVEL *****************************************************   //

struct LevelBottom: public Object
{
	Image image;
	int position[2];
	bool alive;


	void update(void)
	{
		

		
		if (alive)
		{
		position[1] --;
		position[1] --;
		
		}

		if (position[1] < -1152) // By my calculations this should be the perfect point to reset, but strangely I'm left with one pixel?
		{
			position[1] = LEVEL_BOTTOM_START_Y; // Moves level to top in order to re-scroll
			
		}

	}

	void draw(void)


	{   GLfloat fpos[2] = { GLfloat(position[0]), GLfloat(position[1]) };  
		if (alive)
		{
			::draw(image, fpos);
			
		}
	}

};

LevelBottom levelbottom;


void load_levelbottom(void)
{

		load_texture(levelbottom.image.texture, "Level01-Bottom.bmp"); //Loads texture for level
		levelbottom.image.dimension[0] = LEVEL_WIDTH / 2;
		levelbottom.image.dimension[1] = LEVEL_HEIGHT / 2;

	

		levelbottom.position[0] = LEVEL_BOTTOM_START_X;
		levelbottom.position[1] = LEVEL_BOTTOM_START_Y;

}

Object **add_levelbottom(Object **object_array)
{
	*object_array = &levelbottom;
	object_array++;

	return object_array;
}

void reset_levelbottom(void) 
{
	
	levelbottom.alive = true;
	levelbottom.position[0] = LEVEL_BOTTOM_START_X;
	levelbottom.position[1] = LEVEL_BOTTOM_START_Y;
	
}
