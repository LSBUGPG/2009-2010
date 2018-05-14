#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_cross = false;
	bool zombie_alive = true;

	printf(
		"\n"
		"Welcome to hell on Earth! To play, I will describe your situation, and you must\n"
		"type what to do. Ensure that your answers are capitalized, as these are the only"
		"words that I can understand in this stormy weather!\n"
		"\n"
		"Be brave in the face of horror comrade!\n"
		"\n");

describe_graveyard:
	printf(
		"You are in a foggy graveyard. Ahead is a winding path. There are \n"
		"groaning sounds coming from the graveyard. There is a mausoleum behind you.\n"
		"Its front is cracked open, revealing a chamber inside.\n"
		"\n"
		"Will you ENTER the MAUSOLEUM or FOLLOW the PATH?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "MAUSOLEUM") && strstr(answer, "ENTER"))
	{
	    goto enter_mausoleum;
	}
	else if (strstr(answer, "PATH") && strstr(answer, "FOLLOW"))
	{
	    goto follow_path;
	}
	else
	{
		goto unknown_graveyard;
	}

enter_mausoleum:
    printf(
        "\n"
        "You enter the dark mausoleum.\n"
        "\n");

    goto describe_mausoleum;

follow_path:
    printf(
        "\n"
        "You follow the path through the graveyard until you suddenly encounter\n"
        "an obstacle.\n"
        "\n");

    goto describe_gap;

unknown_graveyard:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_graveyard;

describe_mausoleum:
	printf(
		"You are inside a dank and dark cobwebbed mausoleum.\n"
		"\n");

	if (have_cross)
	{
		printf(
			"There is an ornate metal cross hanging on the wall. Will you RETURN the CROSS\n"
			"to the hook, or GO back OUTSIDE?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "OUTSIDE") && strstr(answer, "GO"))
		{
			goto leave_mausoleum;
		}
		else if (strstr(answer, "CROSS") && strstr(answer, "RETURN"))
		{
			goto return_cross;
		}
		else
		{
			goto unknown_mausoleum;
		}
	}
	else
	{
		printf(
			"There is an ornate metal cross hanging on the wall. Will you TAKE the CROSS,\n"
			"or GO back OUTSIDE?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "OUTSIDE") && strstr(answer, "GO"))
		{
			goto leave_mausoleum;
		}
		else if (strstr(answer, "CROSS") && strstr(answer, "TAKE"))
		{
			goto take_cross;
		}
		else
		{
			goto unknown_mausoleum;
		}
	}

leave_mausoleum:
	printf(
		"\n"
		"You leave the mausoleum.\n"
		"\n");

	goto describe_graveyard;

return_cross:
	printf(
		"\n"
		"You replace the cross back on the wall.\n"
		"\n");

	have_cross = false;
	goto describe_mausoleum;

unknown_mausoleum:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_mausoleum;

take_cross:
	printf(
		"\n"
		"You take the cross and leave the mausoleum.\n"
		"\n");

	have_cross = true;
	goto describe_graveyard;

describe_gap:
	printf(
		"You are facing a gap in the graveyard wall. There is no other way out.\n"
		"standing in the space of the gap is a zombie.\n"
		"\n");

	if (zombie_alive && have_cross)
	{
		printf(
			"The zombie is looking at you. The cross you have may hurt the zombie. Will you\n"
			"use the cross to KILL the ZOMBIE or GO back up the PATH?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "PATH") && strstr(answer, "GO"))
		{
			goto return_to_graveyard;
		}
		else if (strstr(answer, "ZOMBIE") && strstr(answer, "KILL"))
		{
			goto zombie_dead;
		}
		else
		{
			goto unknown_gap;
		}
	}
	else if (zombie_alive)
	{
		goto return_for_cross;
	}
	else if (have_cross)
	{
		printf(
			"The zombie is motionless. Will you TAKE the cross out of the ZOMBIE, \n"
			"ENTER the gap past the ZOMBIE, or GO back up the PATH?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "PATH") && strstr(answer, "GO"))
		{
			goto return_to_graveyard;
		}
		else if (strstr(answer, "ZOMBIE") && strstr(answer, "ENTER"))
		{
			goto enter_mansion;
		}
		else if (strstr(answer, "TAKE") && strstr(answer, "ZOMBIE"))
		{
			goto alive_zombie;
		}
		else
		{
			goto unknown_gap;
		}
	}
	else
	{
		printf(
			"The zombie is motionless. Will you ENTER the gap past the ZOMBIE or GO back up the PATH?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "PATH") && strstr(answer, "GO"))
		{
			goto return_to_graveyard;
		}
		else if (strstr(answer, "ZOMBIE") && strstr(answer, "ENTER"))
		{
			goto enter_mansion;
		}
		else
		{
			goto unknown_gap;
		}
	}

return_to_graveyard:
	printf(
		"\n"
		"You follow path back to the graveyard.\n"
		"\n");

	goto describe_graveyard;

zombie_dead:
	printf(
		"\n"
		"The cross twists in the zombie's innards, making it moan in pain.\n"
		"\n");

	zombie_alive = false;
	goto describe_gap;

alive_zombie:
	printf(
		"\n"
		"As you take the cross out of the zombie, it suddenly comes to life and bites\n"
		"your face off!\n");

	zombie_alive = true;
	goto failed_adventurer;

unknown_gap:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_gap;

return_for_cross:
	printf(
		"The zombie is alive. You'll need a weapon like a cross to kill it. You go back\n"
		"up the path to look for one.\n"
		"\n");

	goto describe_graveyard;

enter_mansion:
	printf(
		"\n"
		"You proceed through the gap in the wall and journey through the eerie and \n"
		"claustrophobic forest\n");

	goto describe_mansion;

describe_mansion:
	printf(
		"You are in a decrepit mansion. All around in the gloom, you can hear the \n"
		"unmistakeable shuffles and groans of zombies. They slowly encircle you\n"
		"and get ready to pounce.\n"
        "\n"
		"Will you BURN the MOB, or ESCAPE back through the forest?"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "BURN") && strstr(answer, "MOB"))
	{
		goto last_chance;
	}
	else if (strstr(answer, "ESCAPE"))
	{
		goto escape;
	}
	else
	{
		goto unknown_mansion;
	}

last_chance:
	printf(
		"\n"
		"With a lighter! Are you sure? Will you BURN the MOB SHORTRANGE, or come \n"
		"to your senses and ESCAPE back through the forest?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "BURN") &&
        strstr(answer, "MOB") &&
        strstr(answer, "SHORTRANGE"))
	{
		goto burn_mob;
	}
	else if (strstr(answer, "ESCAPE"))
	{
		goto escape;
	}
	else
	{
		goto unknown_mansion;
	}

escape:
	printf(
		"\n"
		"Watching too much about what's behind you as you run away, you\n"
		"don't see the zombie approaching from the front. You run headlong into it\n"
		"and get instantly chewed to death.\n"
		"\n");

	goto survivor;

unknown_mansion:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_mansion;

burn_mob:
	printf(
		"\n"
		"Against all odds, you manage to burn every zombie to death with your trusty \n"
		"zippo. You truly have no fear.\n"
		"\n");

	goto the_end;

survivor:
	printf(
		"The ordeal is over, and all that remains is to clean up the charred mess of \n"
		"bodies in the mansion. It will be a long day.\n"
		"\n");

	goto the_end;

failed_adventurer:
	printf(
		"You find peace in death, and take some comfort in the knowledge that your\n"
        "body is providing sustenance for a family of zombies.\n"
		"\n");

the_end:
	printf("THE END\n");

	return 0;
}
