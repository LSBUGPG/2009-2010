#include "lose.h"
#include "intro.h"

#include "../mode.h"

#include "../objects/game_over.h"
#include "../audio.h"

struct Lose: public Mode
{
	int time;
	Mix_Music *music;

	Object *object_array[GAME_OVER_TOTAL + 1];

    Object **objects(void)
    {
        return object_array;
    }

	void reset(void)
	{
		time = 0;
		Mix_PlayMusic(music, 1);
	}

	void update(void) 
	{
		time++;

		if (time > 60 * 5)
		{
			set_intro_mode();
		}

		Mode::update();
	}
};

Lose lose;

void load_lose_mode(void)
{
	load_music(lose.music, "GameOverYeah.ogg");
	Object **object = lose.objects();
	object = add_game_over(object);
	*object = 0;
}

void set_lose_mode(void)
{
	set_next_mode(&lose);
}
