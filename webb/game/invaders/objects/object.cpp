#include "../object.h"

#include "invader.h"
#include "copyright.h"
#include "laser.h"
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
	load_game_over();
}
