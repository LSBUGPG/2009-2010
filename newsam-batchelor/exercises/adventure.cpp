#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];

	printf(
		"\n"
		"The journey begins in Southbound where everything isn't what it seems.\n"
		"You must type what to do in capital letters for your answer as for me\n"
		"these are the only words I understand.\n"
		"\n"
		"I wish you well and good luck!\n"
		"\n");

describe_forest:
	printf(
		"You are in a mysterious park but you have a small pathway. The park is\n"
		"eerie and looks scary. you have two routes to go through.\n"
		"\n"
		"Will you ENTER the PARK or FOLLOW the PATHWAY?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "PARK") && strstr(answer, "ENTER"))
	{
	    goto enter_park;
	}
	else if (strstr(answer, "PATHWAY") && strstr(answer, "FOLLOW"))
	{
	    goto follow_pathway;
	}
	else
	{
		goto unknown_park;
	}

enter_park:
    printf(
        "\n"
        "You entered the mysterious park where you get attacked without warning!.\n"
        "\n");

    goto the_end;

follow_pathway:
    printf(
        "\n"
        "You follow the course of the stream through the forest until you reach a point\n"
        "where it suddenly ends. The pathway ends by leading to the town district.\n"
        "\n");

    goto describe_town;

unknown_park:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_forest;

describe_town:
	printf(
		"You are in the town district which has now become eerie and silent.\n"
		"As you look around for any person, you are confronted by a large\n"
		"monster. The monster roars loudly and prepares to strike at you!\n"
		"\n"
		"Will you BATTLE the MONSTER, or RUN back as fast as you can?"
		"\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "BATTLE") && strstr(answer, "MONSTER"))
	{
		goto last_call;
	}
	else if (strstr(answer, "RUN"))
	{
		goto run;
	}
	else
	{
		goto unknown_town;
	}

last_call:
	printf(
		"\n"
		"With your fists! Are you sure?\n"
		"Will you BATTLE the MONSTER with your ABILITIES or think\n"
		"better of it and RUN back as fast as you can?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "BATTLE") &&
        strstr(answer, "MONSTER") &&
        strstr(answer, "ABILITIES"))
	{
		goto defeat_monster;
	}
	else if (strstr(answer, "RUN"))
	{
		goto run;
	}
	else
	{
		goto unknown_town;
	}

run:
	printf(
		"\n"
		"Your heart races as you get away from the monster in one piece!\n"
		"\n");

	goto barely_survived;

unknown_town:
	printf(
		"\n"
		"I need to rethink again.\n"
		"\n");

	goto describe_town;

defeat_monster:
	printf(
		"\n"
		"Incredibly, you fought and defeated the monster with your bare hands!\n"
		"You have great courage and spirit. You are a true warrior.\n"
		"\n");

	goto the_end;

barely_survived:
	printf(
		"Your journey has come to an end. You have come face to face with the\n"
		"monster and will fight another day. You survived this battle, barely.\n"
		"\n");

	goto the_end;

the_end:
	printf("THE END\n");

	return 0;
}

