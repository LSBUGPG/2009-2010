#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_code = false;

	printf(
		"\n"
		"				Hello and Welcome\n"
		"\n"
		"You're transport has just crashed on a strang ilsand and you are the\n"
		"only one left. You are on the beach at the edge of a strange isalnd and\n"
		"you need to find a way off the island but when you get near the forest\n"
		"you hear threatening noises...\n"
		"What will you do?\n");
		
island_choice_01:
	printf(
		"\n"
		"Stay on the BEACH or go in the JUNGLE?\n"
		"\n");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "BEACH"))
	{
	    goto stay_on_beach;
	}
	else if (strstr(answer, "JUNGLE"))
	{
	    goto into_the_jungle;
	}
	else
	{
		printf(
		"\n"
		"Choise one of the capital words!\n");

		goto island_choice_01;
	}

stay_on_beach:
	printf(
		"\n"
		"Great idea, but it doesn't get you anywhere\n");

	goto island_choice_01;

into_the_jungle:
	printf(
		"\n"
		"As you walk through the jungle noices get closer!\n"
		"\n"
		"What will you do?\n"
		"\n");

island_choice_02:
	printf(
		"RUN forwards or turn BACK?\n"
		"\n");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "RUN"))
	{
	    goto run_fast;
	}
	else if (strstr(answer, "BACK"))
	{
	    goto youre_dead;
	}
	else
	{
		printf(
		"\n"
		"Choise one of the capital words!\n");

		goto island_choice_02;
	}

run_fast:
	printf(
		"\n"
		"You run through the jungle with mosters chasing you!\n"
		"You reach a building and lock the door behind you.\n"
		"You are safe.\n"
		"\n"
		"What will do?\n");

island_choice_03:
	printf(
		"\n"
		"LOOK around or find the COMMUNICATION station?\n"
		"\n");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "LOOK"))
	{
	    goto found_paper;
	}
	else if (strstr(answer, "COMMUNICATION"))
	{
	    goto the_ending;
	}
	else
	{
		printf(
		"\n"
		"Choise one of the capital words!\n");

		goto island_choice_03;
	}

youre_dead:
	printf(
		"\n"
		"A monster grabs you and you die!\n");

	goto the_end;

found_paper:
	printf(
		"\n"
		"While looking around you find a piece of paper with the communication code on!\n"
		"\n"
		"What will you do?\n"
		"\n");

island_choice_04:
	printf(
		"Go to the COMMUNICATION station or go OUTSIDE?\n"
		"\n");

	have_code = true;

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "COMMUNICATION"))
	{
	    goto the_ending;
	}
	else if (strstr(answer, "OUTSIDE"))
	{
	    goto youre_dead;
	}
	else
	{
		printf(
		"\n"
		"Choise one of the capital words!\n");

		goto island_choice_04;
	}

the_ending:
		
	if (have_code)
	{
		printf(
			"\n"
			"You unlocked the controls and called for help.\n"
			"You are saved!\n");

		goto the_end;
	}
else
{
		printf(
		"\n"
		"You find the communication station but the controls are locked!\n"
		"\n"
		"What will you do?\n"
		"\n");

island_choice_05:
		printf(
		"LOOK around or go OUTSIDE?\n"
		"\n");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "LOOK"))
	{
	    goto found_paper;
	}
	else if (strstr(answer, "OUTSIDE"))
	{
	    goto youre_dead;
	}
	else
	{
		printf(
		"\n"
		"Choise one of the capital words!\n");

		goto island_choice_05;
	}
	}
	
the_end:
		printf(
			"\n"
			"The End...\n");

	return 0;

}