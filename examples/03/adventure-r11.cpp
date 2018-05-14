#include <cstdio>
#include <cstring>

const int MAXIMUM_COMMAND_LENGTH = 80;
char answer[MAXIMUM_COMMAND_LENGTH];
bool have_key = false;
bool grate_locked = true;
bool last_chance = false;
enum location { introduction, forest, hut, streambed, cave, end };
location next = introduction;

// the answer testing data

const char *words_enter_hut[] = 
{
	"ENTER", 
	"HUT", 
	0
};

const char *words_follow_stream[] = 
{
	"FOLLOW", 
	"STREAM", 
	0
};

const char *words_go_outside[] = 
{
	"GO", 
	"OUTSIDE", 
	0
};

const char *words_return_key[] = 
{
	"RETURN", 
	"KEY", 
	0
};

const char *words_take_key[] = 
{
	"TAKE", 
	"KEY", 
	0
};

const char *words_go_upstream[] = 
{
	"GO", 
	"UPSTREAM", 
	0
};

const char *words_open_grate[] = 
{
	"OPEN", 
	"GRATE", 
	0
};

const char *words_enter_grate[] = 
{
	"ENTER", 
	"GRATE", 
	0
};

const char *words_lock_grate[] = 
{
	"LOCK", 
	"GRATE", 
	0
};

const char *words_fight_dragon[] = 
{
	"FIGHT", 
	"DRAGON", 
	0
};

const char *words_fight_dragon_barehanded[] = 
{
	"FIGHT", 
	"DRAGON", 
	"BAREHANDED", 
	0
};

const char *words_flee[] = 
{
	"FLEE", 
	0
};

const char *words_take_inventory[] =
{
	"TAKE",
	"INVENTORY",
	0
};

// answer functions

bool answer_contains(const char *word[])
{
	bool found = true;
	while (*word)
	{
		if (strstr(answer, *word) == 0)
		{
			found = false;
			break;
		}
		word++;
	}

	return found;
}

struct option
{
	const char **words;
	void (*action)(void);
};

void get_answer(void)
{
	bool repeat = true;
	do 
	{
		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (answer_contains(words_take_inventory))
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

void do_answer(const option *choice)
{
	if (choice->words)
	{
		get_answer();
	}

	while (true)
	{
		if (choice->words == 0 || answer_contains(choice->words))
		{
			choice->action();
			break;
		}
		choice++;
	}
}

// The result functions

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

// choices of options

const option forest_options [] =
{
	{ words_enter_hut, enter_hut },
	{ words_follow_stream, follow_stream },
	{ 0, unknown_forest }
};

const option hut_options_with_key [] =
{
	{ words_go_outside, leave_hut },
	{ words_return_key, return_key },
	{ 0, unknown_hut }
};

const option hut_options_without_key [] =
{
	{ words_go_outside, leave_hut },
	{ words_take_key, take_key },
	{ 0, unknown_hut }
};

const option streambed_options_with_key_but_locked [] =
{
	{ words_go_upstream, return_to_forest },
	{ words_open_grate, unlock_grate },
	{ 0, unknown_streambed }
};

const option streambed_options_without_key_and_locked [] =
{
	{ 0, return_for_key }
};

const option streambed_options_with_key_and_unlocked [] =
{
	{ words_go_upstream, return_to_forest },
	{ words_enter_grate, enter_cave },
	{ words_lock_grate, lock_grate },
	{ 0, unknown_streambed }
};

const option streambed_options_without_key_but_unlocked [] =
{
	{ words_go_upstream, return_to_forest },
	{ words_enter_grate, enter_cave },
	{ 0, unknown_streambed }
};

const option cave_options [] =
{
	{ words_fight_dragon, barehanded_are_you_sure },
	{ words_flee, flee },
	{ 0, unknown_cave }
};

const option cave_options_last_chance [] =
{
	{ words_fight_dragon_barehanded, kill_dragon },
	{ words_flee, flee },
	{ 0, unknown_cave }
};

// the description functions

void describe_forest(void)
{
	printf(
		"You are in a mysterious forest. Beside you is a small stream. The forest is\n"
		"unexpectedly quiet. The only sound is the gentle trickle of the water. There is\n"
		"also a small wooden hut nearby. The door appears unlocked.\n"
		"\n"
		"Will you ENTER the HUT or FOLLOW the STREAM?\n"
		"\n>");

	do_answer(forest_options);
}

void describe_hut(void)
{
	printf(
		"You are inside a musty old wooden hut.\n"
		"\n");

	if (have_key)
	{
		printf(
			"There is a small metal key hook on the wall. Will you RETURN the KEY to the\n"
			"hook, or GO back OUTSIDE?\n"
			"\n>");

		do_answer(hut_options_with_key);
	}
	else
	{
		printf(
			"There is a small metal key hanging from a hook on the wall.\n"
			"\n"
			"Will you TAKE the KEY or GO back OUTSIDE?\n"
			"\n>");

		do_answer(hut_options_without_key);
	}
}

void describe_streambed(void)
{
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

		do_answer(streambed_options_with_key_but_locked);
	}
	else if (grate_locked)
	{
		do_answer(streambed_options_without_key_and_locked);
	}
	else if (have_key)
	{
		printf(
			"The grate is unlocked. Will you LOCK the GRATE, ENTER through the GRATE, or GO\n"
			"back UPSTREAM?\n"
			"\n>");

		do_answer(streambed_options_with_key_and_unlocked);
	}
	else
	{
		printf(
			"The grate is unlocked. Will you ENTER through the GRATE or GO back UPSTREAM?\n"
			"\n>");

		do_answer(streambed_options_without_key_but_unlocked);
	}
}

void describe_cave(void)
{
	printf(
		"You are in a dank cavern. Before you, in the darkness, you can make out the\n"
		"shape of an ancient dragon. The dragon bares its teeth and prepares to strike.\n"
		"\n");

	if (!last_chance)
	{
		printf(
			"Will you FIGHT the DRAGON, or FLEE back through the grate?"
			"\n>");

		do_answer(cave_options);
	}
	else
	{
		printf(
			"Will you FIGHT the DRAGON BAREHANDED, or think better of it and FLEE back to\n"
			"the surface?\n"
			"\n>");

		do_answer(cave_options_last_chance);
	}
}

void describe_introduction(void)
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

	next = forest;
}

void describe_end(void)
{
	printf("THE END\n");
}

int main(int argc, char *argv[])
{
	do
	{
		switch (next)
		{
		case introduction:
			describe_introduction();
			break;
		case forest: 
			describe_forest();
			break;
		case hut: 
			describe_hut();
			break;
		case streambed:
			describe_streambed();
			break;
		case cave:
			describe_cave();
			break;
		case end:
			describe_end();
			break;
		}
	}
	while (next != end);

	return 0;
}
