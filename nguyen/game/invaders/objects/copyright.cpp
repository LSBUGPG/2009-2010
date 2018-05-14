#include "copyright.h"

#include "../object.h"
#include "../graphics.h"

struct Copyright: public Object
{
	Image message;

	void update(void) {}

	void draw(void) 
	{
		GLfloat pos[] = { 0.f, 0.f };
		::draw(message, pos);
	}
};

Copyright copyright;

void load_copyright(void)
{
	load_text_line(copyright.message, "Copyright © 2010 by Oanh Nguyen");
}

Object **add_copyright(Object **object_array)
{
	*object_array = &copyright;
	object_array++;

	return object_array;
}
