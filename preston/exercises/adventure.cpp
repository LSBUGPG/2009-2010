#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_shotgun = false;
	bool door_locked = true;

	printf(
		"\n"
		"Welcome vigilante!\n"
		"To play, I will describe your situation, and you must\n"
		"type what to do. Ensure that you include the capitalized words\n"
		"in your answer as these are the only words I can understand.\n"
		"\n"
		"Good luck adventurer!\n"
		"\n");

describe_estate:
	printf(
		"Your journey begins in a dangerous council estate.\n"
		"You are walking along an empty road. The estate is unexpectedly quiet.\n"
		"The only sound you can hear is that of a distant Vauxhall Nova misfiring.\n"
		"You spot a battered old phonebox up ahead. The door appears vandalised.\n"
		"\n"
		"Will you ENTER the PHONEBOX or FOLLOW the ROAD?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "PHONEBOX") && strstr(answer, "ENTER"))
	{
	    goto enter_phonebox;
	}
	else if (strstr(answer, "ROAD") && strstr(answer, "FOLLOW"))
	{
	    goto follow_road;
	}
	else
	{
		goto unknown_estate;
	}

enter_phonebox:
    printf(
        "\n"
        "You enter the battered old phone box.\n"
        "\n");

    goto describe_phonebox;

follow_road:
    printf(
        "\n"
        "You follow the road through the dangerous estate until you reach a point\n"
        "where it suddenly ends.\n"
        "\n");

    goto describe_underpass;

unknown_estate:
	printf(
		"\n"
		"I didn't understand that answer.\n"
		"\n");

	goto describe_estate;

describe_phonebox:
	printf(
		"You are inside the dirty old phone box.\n"
		"Calling cards are stuck to every surface\n"
		"\n");

	if (have_shotgun)
	{
		printf(
			"There is a loaded shotgun hanging on the wall.\n"
			"Will you RETURN the SHOTGUN to the rack, or GO back OUTSIDE?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "OUTSIDE") && strstr(answer, "GO"))
		{
			goto leave_phonebox;
		}
		else if (strstr(answer, "SHOTGUN") && strstr(answer, "RETURN"))
		{
			goto return_shotgun;
		}
		else
		{
			goto unknown_phonebox;
		}
	}
	else
	{
		printf(
			"There is a shotgun hanging from a rack on the wall.\n"
			"\n"
			"Will you TAKE the SHOTGUN or GO back OUTSIDE?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "OUTSIDE") && strstr(answer, "GO"))
		{
			goto leave_phonebox;
		}
		else if (strstr(answer, "SHOTGUN") && strstr(answer, "TAKE"))
		{
			goto take_shotgun;
		}
		else
		{
			goto unknown_phonebox;
		}
	}

leave_phonebox:
	printf(
		"\n"
		"You leave the phonebox and continue on your journey.\n"
		"\n");

	goto describe_estate;

return_shotgun:
	printf(
		"\n"
		"You return the shotgun to its gunrack.\n"
		"\n");

	have_shotgun = false;
	goto describe_phonebox;

unknown_phonebox:
	printf(
		"\n"
		"Sorry, I didn't understand that answer.\n"
		"\n");

	goto describe_phonebox;

take_shotgun:
	printf(
		"\n"
		"You take the loaded shotgun and leave the phonebox.\n"
		"\n");

	have_shotgun = true;
	goto describe_estate;

describe_underpass:
	printf(
		"You have reached some kind of motorway underpass.\n"
		"Cars roar overhead, yet the eerie silence around you is defeaning.\n"
		"In the darkness, you can see the outline of a rusty metal door.\n"
		"\n");

	if (door_locked && have_shotgun)
	{
		printf(
			"The rusty door is locked. But it looks like the shotgun\n"
			"you have will blow it open.\n"		
			"Will you use the shotgun to OPEN the DOOR or GO back to the ESTATE?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "ESTATE") && strstr(answer, "GO"))
		{
			goto return_to_estate;
		}
		else if (strstr(answer, "DOOR") && strstr(answer, "OPEN"))
		{
			goto open_door;
		}
		else
		{
			goto unknown_underpass;
		}
	}
	else if (door_locked)
	{
		goto return_for_shotgun;
	}
	else if (have_shotgun)
	{
		printf(
			"The door is blown open. Will you CLOSE the DOOR, ENTER through the DOOR, or GO\n"
			"back to the ESTATE?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "ESTATE") && strstr(answer, "GO"))
		{
			goto return_to_estate;
		}
		else if (strstr(answer, "DOOR") && strstr(answer, "ENTER"))
		{
			goto enter_chavlair;
		}
		else if (strstr(answer, "CLOSE") && strstr(answer, "DOOR"))
		{
			goto close_door;
		}
		else
		{
			goto unknown_underpass;
		}
	}
	else
	{
		printf(
			"The door is blown open. Will you ENTER through the door or GO back to the ESTATE?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "ESTATE") && strstr(answer, "GO"))
		{
			goto return_to_estate;
		}
		else if (strstr(answer, "DOOR") && strstr(answer, "ENTER"))
		{
			goto enter_chavlair;
		}
		else
		{
			goto unknown_underpass;
		}
	}

return_to_estate:
	printf(
		"\n"
		"You follow the road back into the council estate.\n"
		"\n");

	goto describe_estate;

open_door:
	printf(
		"\n"
		"The shotgun blows open the rusty door.\n"
		"\n");

	door_locked = false;
	goto describe_underpass;

close_door:
	printf(
		"\n"
		"As you close the door you suddenly wake up in your bed.\n"
		"\n");

	door_locked = true;
	goto failed_adventurer;

unknown_underpass:
	printf(
		"\n"
		"Sorry, I didn't understand that answer.\n"
		"\n");

	goto describe_underpass;

return_for_shotgun:
	printf(
		"The door is locked. You'll need something powerful to open it.\n"
		"You go back to the estate to look for something useful.\n"
		"\n");

	goto describe_estate;

enter_chavlair:
	printf(
		"\n"
		"You walk through the door and into the darkness.\n"
		"\n");

	goto describe_chavlair;

describe_chavlair:
	printf(
		"You find yourself in a chav drug den. Before you, in the darkness, you can make out the\n"
		"shape of a large, scary chav. He pulls out a flick-knife and prepares to strike.\n"
		"\n"
		"Will you FIGHT the CHAV, or FLEE back through the door?"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "FIGHT") && strstr(answer, "CHAV"))
	{
		goto last_chance;
	}
	else if (strstr(answer, "FLEE"))
	{
		goto flee;
	}
	else
	{
		goto unknown_chavlair;
	}

last_chance:
	printf(
		"\n"
		"You raise the shotgun and aim at his chest. Will you SHOOT the CHAV, or think\n"
		"better of it and FLEE back to the underpass?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "SHOOT") &&
        strstr(answer, "CHAV"))
	{
		goto kill_chav;
	}
	else if (strstr(answer, "FLEE"))
	{
		goto flee;
	}
	else
	{
		goto unknown_chavlair;
	}

flee:
	printf(
		"\n"
		"Your heart races as you walk back out of the chav lair.\n"
		"But, as you slam the door shut behind you, you suddenly wake up in your bed.\n"
		"\n");

	goto failed_adventurer;

unknown_chavlair:
	printf(
		"\n"
		"Sorry, I didn't understand that answer.\n"
		"\n");

	goto describe_chavlair;

kill_chav:
	printf(
		"\n"
		"Incredibly, you fight and kill the chav leader!\n"
		"You awake, with newfound confidence. You are a true vigilante adventurer.\n"
		"\n");

	goto the_end;

survivor:
	printf(
		"Your have cleaned up the streets. The chav menace is defeated.\n"
		"You are a true vigilante hero.\n"
		"\n");

	goto the_end;

failed_adventurer:
	printf(
		"Your vigilante adventure is at an end.\n"
		"You realise you do not have what it takes.\n"
		"You wimp.\n"
		"\n");

the_end:
	printf("THE END\n");

	return 0;
}
