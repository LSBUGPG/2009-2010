#include "copyright.h"

#include "../object.h"
#include "../graphics.h"

struct Copyright: public Object
{


		
	Image image;
	void update(void) {}

	void draw(void) 
	{
		GLfloat pos[] = { 0.f, 0.f };
		::draw(image, pos);
	}
};

Copyright copyright;

void load_copyright(void)
{
	
	load_texture(copyright.image.texture, "Winners_Dont_Use_Drugs.bmp");
	copyright.image.dimension[0] = 256;
	copyright.image.dimension[1] = 192;

	

}

Object **add_copyright(Object **object_array)
{
	*object_array = &copyright;
	object_array++;

	return object_array;
}
