#include "instruction.h"

#include "../object.h"
#include "../graphics.h"

const int MESSAGES = 9;

const char *message_text[MESSAGES] =
{
	"A long time ago",
	"in a galaxy far far away",
	"the evil Galatic Empire are causing",
	"destruction and devastation",
	"to all who oppose them.",
	"You are the rebellions only hope",
	"Use LEFT and RIGHT keys to move",
	"LEFT CTRL key to shoot",
	"SPACE to start"
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
		GLfloat pos[] = { 0.f, 70.f };
		
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
