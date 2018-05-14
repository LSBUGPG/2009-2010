#include "instruction.h"

#include "../object.h"
#include "../graphics.h"

const int MESSAGES = 6;

const char *message_text[MESSAGES] =
{
	"Instructions:",
	"Aliens are attacking Earth!",
	"Escape them shooting at you!",
	"LEFT,RIGHT,UP and DOWN arrows to move",
	"LEFT CTRL to shoot",
	"SPACE to start, ESC to end game"
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
		GLfloat pos[] = { 0.f, 40.f };
		
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
