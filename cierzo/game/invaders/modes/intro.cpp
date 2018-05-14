#include "intro.h"
#include "game.h"

#include "../mode.h"//.. means go back a directory
#include "../controls.h"

#include "../objects/instruction.h"

struct Intro: public Mode
{
	Object *object_array[INSTRUCTION_TOTAL + 1];

    Object **objects(void)
    {
        return object_array;
    }

	void reset(void)
	{
		start_game = false;
		reset_instruction();
	}

	void update(void) 
	{
		if (start_game)
		{
			set_game_mode();
		}

		Mode::update();
	}
};

Intro intro;

void load_intro_mode(void)
{
	Object **object = intro.objects();
	object = add_instruction(object);
	*object = 0;
}

void set_intro_mode(void)
{
	set_next_mode(&intro);
}
