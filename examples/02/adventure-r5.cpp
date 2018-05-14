#include <cstdio>
#include <cstring>

const int MAXIMUM_COMMAND_LENGTH = 80;
char answer[MAXIMUM_COMMAND_LENGTH];
bool have_key = false;
bool grate_locked = true;
bool last_chance = false;
enum location { forest, hut, streambed, cave, end };
location next = forest;

void get_answer(void)
{
	bool repeat = true;
	do 
	{
		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "TAKE") && strstr(answer, "INVENTORY"))
		{
			if (have_key)
			{
				printf(
					"\n"
					"You have a small metal key.\n");
			}
			else
			{
				printf(
					"\n"
					"You have nothing.\n");
			}

			printf("\n>");
		}
		else
		{
			repeat = false;
		}
	}
	while (repeat);
}

void enter_hut(void)
{
	printf(
		   "\n"
		   "You enter the small wooden hut.\n"
		   "\n");

	next = hut;
}

void follow_stream(void)
{
	printf(
		   "\n"
		   "You follow the course of the stream through the forest until you reach a point\n"
		   "where it suddenly ends.\n"
		   "\n");

	next = streambed;
}

void unknown_forest(void)
{
	printf(
		   "\n"
		   "I did not understand that answer.\n"
		   "\n");

	next = forest;
}

void leave_hut(void)
{
	printf(
		"\n"
		"You leave the hut.\n"
		"\n");

	next = forest;
}

void return_key(void)
{
	printf(
		"\n"
		"You return the small key to its hook.\n"
		"\n");

	have_key = false;
	next = hut;
}

void unknown_hut(void)
{
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	next = hut;
}

void take_key(void)
{
	printf(
		"\n"
		"You take the small key and leave the hut.\n"
		"\n");

	have_key = true;
	next = forest;
}

void return_to_forest(void)
{
	printf(
		"\n"
		"You follow the stream back into the forest.\n"
		"\n");

	next = forest;
}

void unlock_grate(void)
{
	printf(
		"\n"
		"The key turns reluctantly in the rusty old lock.\n"
		"\n");

	grate_locked = false;
	next = streambed;
}

void survivor(void)
{
	printf(
		"Your adventure is at an end. You have faced a dragon and yet live to tell the\n"
		"tale. You are a true survivor.\n"
		"\n");

	next = end;
}

void failed_adventurer(void)
{
	printf(
		"Your adventure is at an end. You realise you do not have what it takes.\n"
		"\n");

	next = end;
}

void lock_grate(void)
{
	printf(
		"\n"
		"As you lock the grate you suddenly wake.\n"
		"\n");

	grate_locked = true;
	failed_adventurer();
}

void unknown_streambed(void)
{
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	next = streambed;
}

void return_for_key(void)
{
	printf(
		"The grate is locked. You'll need a key to open it. You go back upstream to look\n"
		"for one.\n"
		"\n");

	next = forest;
}

void enter_cave(void)
{
	printf(
		"\n"
		"You descend through the grate and into the darkness.\n"
		"\n");

	next = cave;
}

void flee(void)
{
	printf(
		"\n"
		"Your heart races as you climb back out of the cave. But, as you slam the grate\n"
		"shut behind you, you suddenly wake.\n"
		"\n");

	survivor();
}

void unknown_cave(void)
{
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	next = cave;
}

void kill_dragon(void)
{
	printf(
		"\n"
		"Incredibly, you fight and kill the dragon with your bare hands! You wake, with\n"
		"newfound confidence. You are a true adventurer.\n"
		"\n");

	next = end;
}

void barehanded_are_you_sure(void)
{
	printf(
		"\n"
		"Barehanded! Are you sure?\n"
		"\n");

	last_chance = true;
}

int main(int argc, char *argv[])
{
	printf(
		"\n"
		"Welcome to the adventure. To play, I will describe your situation, and you must\n"
		"type what to do. Ensure that you include the capitalized words in your answer\n"
		"as these are the only words I understand. If you want to know what you are\n"
		"holding at any time, ask to TAKE your INVENTORY.\n"
		"\n"
		"Good luck adventurer!\n"
		"\n");

next_location:
	switch (next)
	{
	case forest: 
		goto describe_forest;
	case hut: 
		goto describe_hut;
	case streambed:
		goto describe_streambed;
	case cave:
		goto describe_cave;
	case end:
		goto the_end;
	}

describe_forest:
	printf(
		"You are in a mysterious forest. Beside you is a small stream. The forest is\n"
		"unexpectedly quiet. The only sound is the gentle trickle of the water. There is\n"
		"also a small wooden hut nearby. The door appears unlocked.\n"
		"\n"
		"Will you ENTER the HUT or FOLLOW the STREAM?\n"
		"\n>");

	get_answer();
	if (strstr(answer, "HUT") && strstr(answer, "ENTER"))
	{
	    enter_hut();
	}
	else if (strstr(answer, "STREAM") && strstr(answer, "FOLLOW"))
	{
	    follow_stream();
	}
	else
	{
		unknown_forest();
	}
	goto next_location;


describe_hut:
	printf(
		"You are inside a musty old wooden hut.\n"
		"\n");

	if (have_key)
	{
		printf(
			"There is a small metal key hook on the wall. Will you RETURN the KEY to the\n"
			"hook, or GO back OUTSIDE?\n"
			"\n>");

		get_answer();
		if (strstr(answer, "OUTSIDE") && strstr(answer, "GO"))
		{
			leave_hut();
		}
		else if (strstr(answer, "KEY") && strstr(answer, "RETURN"))
		{
			return_key();
		}
		else
		{
			unknown_hut();
		}
	}
	else
	{
		printf(
			"There is a small metal key hanging from a hook on the wall.\n"
			"\n"
			"Will you TAKE the KEY or GO back OUTSIDE?\n"
			"\n>");

		get_answer();
		if (strstr(answer, "OUTSIDE") && strstr(answer, "GO"))
		{
			leave_hut();
		}
		else if (strstr(answer, "KEY") && strstr(answer, "TAKE"))
		{
			take_key();
		}
		else
		{
			unknown_hut();
		}
	}
	goto next_location;

describe_streambed:
	printf(
		"You are at the end of a small stream. It trickles down into a small hole in the\n"
		"ground. Beyond the hole, the stream bed is dry. There is a large metal grate in\n"
		"the dry earth.\n"
		"\n");

	if (grate_locked && have_key)
	{
		printf(
			"The grate is locked. It looks like the key you have will fit the lock. Will you\n"
			"use the key to OPEN the GRATE or GO back UPSTREAM?\n"
			"\n>");

		get_answer();
		if (strstr(answer, "UPSTREAM") && strstr(answer, "GO"))
		{
			return_to_forest();
		}
		else if (strstr(answer, "GRATE") && strstr(answer, "OPEN"))
		{
			unlock_grate();
		}
		else
		{
			unknown_streambed();
		}
	}
	else if (grate_locked)
	{
		return_for_key();
	}
	else if (have_key)
	{
		printf(
			"The grate is unlocked. Will you LOCK the GRATE, ENTER through the GRATE, or GO\n"
			"back UPSTREAM?\n"
			"\n>");

		get_answer();
		if (strstr(answer, "UPSTREAM") && strstr(answer, "GO"))
		{
			return_to_forest();
		}
		else if (strstr(answer, "GRATE") && strstr(answer, "ENTER"))
		{
			enter_cave();
		}
		else if (strstr(answer, "LOCK") && strstr(answer, "GRATE"))
		{
			lock_grate();
		}
		else
		{
			unknown_streambed();
		}
	}
	else
	{
		printf(
			"The grate is unlocked. Will you ENTER through the GRATE or GO back UPSTREAM?\n"
			"\n>");

		get_answer();
		if (strstr(answer, "UPSTREAM") && strstr(answer, "GO"))
		{
			return_to_forest();
		}
		else if (strstr(answer, "GRATE") && strstr(answer, "ENTER"))
		{
			enter_cave();
		}
		else
		{
			unknown_streambed();
		}
	}
	goto next_location;

describe_cave:
	printf(
		"You are in a dank cavern. Before you, in the darkness, you can make out the\n"
		"shape of an ancient dragon. The dragon bares its teeth and prepares to strike.\n"
		"\n");

	if (!last_chance)
	{
		printf(
			"Will you FIGHT the DRAGON, or FLEE back through the grate?"
			"\n>");

		get_answer();
		if (strstr(answer, "FIGHT") && strstr(answer, "DRAGON"))
		{
			barehanded_are_you_sure();
		}
		else if (strstr(answer, "FLEE"))
		{
			flee();
		}
		else
		{
			unknown_cave();
		}
	}
	else
	{
		printf(
			"Will you FIGHT the DRAGON BAREHANDED, or think better of it and FLEE back to\n"
			"the surface?\n"
			"\n>");

		get_answer();
		if (strstr(answer, "FIGHT") &&
			strstr(answer, "DRAGON") &&
			strstr(answer, "BAREHANDED"))
		{
			kill_dragon();
		}
		else if (strstr(answer, "FLEE"))
		{
			flee();
		}
		else
		{
			unknown_cave();
		}
	}
	goto next_location;

the_end:
	printf("THE END\n");

	return 0;
}
