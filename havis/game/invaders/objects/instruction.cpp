#include "instruction.h"

#include "../object.h"
#include "../graphics.h"

const int MESSAGES = 10;

const char *message_text[MESSAGES] =
{

	"The Story:",
	"Evil clowns are taking over the world!", 
	"They can only be killed by throwing juggling balls at them!",
	"Go now and save the world!",
	"Your Mission:",
	"Kill as many, evil clowns as you can!",
	"Avoid the cream pies that they are throwing at you!",
	"LEFT and RIGHT arrows to move",
	"LEFT CTRL to shoot",
	"SPACE bar to start"
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
		GLfloat pos[] = { 0.f, 60.f };
		
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
