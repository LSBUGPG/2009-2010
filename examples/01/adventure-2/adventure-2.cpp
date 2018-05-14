#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool grate_locked = true;

	printf(
		"\n"
		"Welcome to the adventure. To play, I will describe your situation, and you must\n"
		"type what to do. Ensure that you include the capitalized words in your answer as\n"
		"these are the only words I understand.\n"
		"\n"
		"Good luck adventurer!\n"
		"\n");

describe_forest:
	printf(
		"You are in a mysterious forest. Beside you is a small stream. The forest is\n"
		"unexpectedly quiet. The only sound is the gentle trickle of the water. There is\n"
		"also a small wooden hut nearby. The door appears unlocked.\n"
		"\n"
		"Will you ENTER the HUT or FOLLOW the STREAM?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "HUT") && strstr(answer, "ENTER"))
	{
	    goto enter_hut;
	}
	else if (strstr(answer, "STREAM") && strstr(answer, "FOLLOW"))
	{
	    goto follow_stream;
	}
	else
	{
		goto unknown_forest;
	}

enter_hut:
    printf(
        "\n"
        "You enter the small wooden hut.\n"
        "\n");

    goto the_end;

follow_stream:
    printf(
        "\n"
        "You follow the course of the stream through the forest until you reach a point\n"
        "where it suddenly ends.\n"
        "\n");

    goto describe_streambed;

unknown_forest:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_forest;

describe_streambed:
	printf(
		"You are at the end of a small stream. It trickles down into a small hole in the\n"
		"ground. Beyond the hole, the stream bed is dry. There is a large metal grate in\n"
		"the dry earth.\n"
		"\n");

	if (grate_locked)
	{
		goto return_for_key;
	}
	else
	{
		printf(
			"The grate is unlocked. Will you ENTER through the GRATE or GO back UPSTREAM?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "UPSTREAM") && strstr(answer, "GO"))
		{
			goto return_to_forest;
		}
		else if (strstr(answer, "GRATE") && strstr(answer, "ENTER"))
		{
			goto enter_cave;
		}
		else
		{
			goto unknown_streambed;
		}
	}

return_to_forest:
	printf(
		"\n"
		"You follow the stream back into the forest.\n"
		"\n");

	goto describe_forest;

unknown_streambed:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_streambed;

return_for_key:
	printf(
		"The grate is locked. You'll need a key to open it. You go back upstream to look\n"
		"for one.\n"
		"\n");

	goto describe_forest;

enter_cave:
	printf(
		"\n"
		"You descend through the grate and into the darkness.\n"
		"\n");

	goto the_end;

the_end:
	printf("THE END\n");

	return 0;
}
