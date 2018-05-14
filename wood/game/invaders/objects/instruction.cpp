#include "instruction.h"

#include "../object.h"
#include "../graphics.h"

const int MESSAGES = 7;

const char *message_text[MESSAGES] =
{
	"Instructions:",
	" ",
	"Stop the politicians!",
	"Avoid the LIES!",
	"LEFT and RIGHT arrows to move Boris Johnson",
	"LEFT CTRL to shoot bananas",
	"Press SPACE to start"
};

struct Instruction: public Object
{
	Image message[MESSAGES];
	int time;

	void update(void) 
	{
		time++;
	}

	void draw(void) 
	{
		GLfloat pos[] = { 0.f, 120.f };
		
		for (int i = 0; i < MESSAGES; i++)
		{
			if (time > i * 60)
			{
				::draw(message[i], pos);
			}
			pos[1] -= 20.f;
		}
	}
};

Instruction instruction;

void load_instruction(void)
{
	for (int i = 0; i < MESSAGES; i++)
	{
		load_text_line(instruction.message[i], message_text[i]);
	}
	instruction.time = 0;
}

Object **add_instruction(Object **object_array)
{
	*object_array = &instruction;
	object_array++;

	return object_array;
}

void reset_instruction(void)
{
	instruction.time = 0;
}
