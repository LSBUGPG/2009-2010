#include "game.h"
#include "lose.h"

#include "../mode.h"
#include "../controls.h"

#include "../objects/invader.h"
#include "../objects/laser.h"
#include "../objects/score.h"
#include "../objects/level.h"

#include "../audio.h"

struct Game: public Mode
{
	int time;
	Mix_Music *music;

    Object *object_array[INVADER_TOTAL + LASER_TOTAL + SCORE_TOTAL + LEVEL_TOTAL + 1];

    Object **objects(void)
    {
        return object_array;
    }

	void reset(void)
	{
		reset_invaders();
		reset_laser();
		reset_score();
		reset_level();		 // reset function for level
		reset_levelbottom(); // reset function for bottom half of level.
		game_over = false;
		time = 0;
		Mix_PlayMusic(music, -1);
	}

	void update(void)
	{
		if (game_over)
		{
			time++;

			if (time > 60)
			{
				set_lose_mode();
			}
		}

		Mode::update();
	}
};

Game game;

void load_game_mode(void)
{
	load_music(game.music, "LevelMusic.ogg");

    Object **object = game.objects();
	object = add_level(object);       // top half of level
	object = add_levelbottom(object); // bottom half of level
    object = add_invaders(object);
    object = add_laser(object);
    object = add_score(object);

    *object = 0;
	
}

void set_game_mode(void)
{
	set_next_mode(&game);
}
