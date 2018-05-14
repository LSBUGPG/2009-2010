#include "legal.h"
#include "game.h"
#include "lose.h"
#include "intro.h"

#include "../mode.h"
#include "../object.h"

Mode *mode = 0;

Mode *load_modes(void)
{
    load_objects();

	load_legal_mode();
	load_intro_mode();
	load_game_mode();
	load_lose_mode();

//	set_legal_mode();
	set_legal_mode();
    return mode;
}

Mode *next_mode(void)
{
    return mode;
}

void set_next_mode(Mode *next_mode)
{
	mode = next_mode;
	mode->reset();
}

void Mode::update(void)
{
	Object **object = objects();
	while (*object)
	{
		(*object)->update();
		object++;
	}
}

void Mode::draw(void)
{
	Object **object = objects();
	while (*object)
	{
		(*object)->draw();
		object++;
	}
}
