#include "../object.h"

#include "invader.h"
#include "copyright.h"
#include "laser.h"
#include "level.h"  // including level.h to load it in to objects
#include "score.h"
#include "game_over.h"
#include "instruction.h"

void load_objects(void)
{
	load_copyright();
	load_instruction();
    load_invaders();
	load_laser();
	load_score();
	load_level();  // loading the level object
	load_levelbottom();  // loading the level object
	load_game_over();
}
