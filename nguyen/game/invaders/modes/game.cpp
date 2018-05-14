#include "game.h"
#include "lose.h"

#include "../mode.h"
#include "../controls.h"
#include "../audio.h"

#include "../objects/invader.h"
#include "../objects/laser.h"
#include "../objects/score.h"

struct Game: public Mode
{
	int time;

    Object *object_array[INVADER_TOTAL + LASER_TOTAL + SCORE_TOTAL + 1];

    Object **objects(void)
    {
        return object_array;
    }

	void reset(void)
	{
		reset_invaders();
		reset_laser();
		reset_score();
		game_over = false;
		time = 0;

		Mix_Music *music; 
		load_music(music, "pirate.ogg"); 

		int LOOP_MUSIC_FOREVER = -1; 
		Mix_PlayMusic(music, LOOP_MUSIC_FOREVER);  
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
    Object **object = game.objects();
    object = add_invaders(object);
    object = add_laser(object);
    object = add_score(object);
    *object = 0;
}

void set_game_mode(void)
{
	set_next_mode(&game);
}
