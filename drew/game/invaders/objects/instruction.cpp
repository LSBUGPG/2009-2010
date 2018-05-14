#include "instruction.h"

#include "../object.h"
#include "../graphics.h"


struct Instruction: public Object
{
Image image;

	void update(void) {}

	void draw(void) 
	{
		GLfloat pos[] = { 0.f, 0.f };
		::draw(image, pos);
	}

};

Instruction instruction;

void load_instruction(void)
{

	load_texture(instruction.image.texture, "Instructions.bmp");
	instruction.image.dimension[0] = 256;
	instruction.image.dimension[1] = 192;

}

Object **add_instruction(Object **object_array)
{
	*object_array = &instruction;
	object_array++;

	return object_array;
}

void reset_instruction(void)
{

}
