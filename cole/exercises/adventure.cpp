#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool had_wee = false;
	bool friend_uninpressed = true;

	printf(
		"\n"
		"Welcome to your heavy night out. To play, I will describe your situation,\n"
		"and you must type what to do.\n" 
		"\n"
		"Ensure that you include the capitalized words in your answer as\n"
		"these are the only words I understand.\n"
		"\n"
		"Good luck boozer!\n"
		"\n");

describe_pub:
	printf(
		"You are in the local Pub. you have had a few too many. Maybe\n"
		"its best you left.\n"
		"the Pub is realy busy and loud. you can see the exit of the Pub. next to which\n"
		"is the door to the rest room.\n"
		"\n"
		"Will you EXIT the PUB or go to the REST ROOM?\n"
		"\n");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "REST") && strstr(answer, "ROOM"))
	{
	    goto rest_room;
	}
	else if (strstr(answer, "PUB") && strstr(answer, "EXIT"))
	{
	    goto exit_pub;
	}
	else
	{
		goto unknown_pub;
	}

rest_room:
    printf(
        "\n"
        "You enter the rest room.\n"
        "\n");

    goto describe_toilet;

exit_pub:
    printf(
        "\n"
        "You leave the pub and start to walk up the street.\n"
        "\n");

    goto describe_street;

unknown_pub:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_pub;

describe_toilet:
	printf(
		"you are in the rest room.\n"
		"Whats that smell!\n"
		"\n");

	if (had_wee)
	{
		printf(
			"There is a toilet cubicle free!. \n"
			"\n>"
			"Will you BE SICK, or LEAVE the TOILET?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "TOILET") && strstr(answer, "LEAVE"))
		{
			goto leave_toilet;
		}
		else if (strstr(answer, "SICK") && strstr(answer, "BE"))
		{
			goto be_sick;
		}
		else
		{
			goto unknown_toilet;
		}
	}
	else
	{
		printf(
			"There is a toilet cubicle free!.\n"
			"\n"
			"Will you HAVE a WEE or LEAVE the TOILET?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "TOILET") && strstr(answer, "LEAVE"))
		{
			goto leave_toilet;
		}
		else if (strstr(answer, "WEE") && strstr(answer, "HAVE"))
		{
			goto have_wee;
		}
		else
		{
			goto unknown_toilet;
		}
	}

leave_toilet:
	printf(
		"\n"
		"You leave the rest room.\n"
		"\n");

	goto describe_pub;

be_sick:
	printf(
		"\n"
		"You are sick down the toilet. you look a mess.\n"
		"\n");

	goto describe_toilet;

unknown_toilet:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_toilet;

have_wee:
	printf(
		"\n"
		"You go for a wee. Wow you realy needed that.\n"
		"\n");

	had_wee = true;
	goto describe_pub;

describe_street:
	printf(
		"You are at the end of the street.\n" 
		"There is a set of traffic lights you must cross.\n"
		"\n");

	if (friend_uninpressed && had_wee)
	{
		printf(
			"you notice that an old friend of yours that you have fancied for ages is\n" 
			"waiting to cross at the traffic lights.\n"
			"Will you try CHAT them UP or GO BACK the way you came?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "BACK") && strstr(answer, "GO"))
		{
			goto return_to_pub;
		}
		else if (strstr(answer, "UP") && strstr(answer, "CHAT"))
		{
			goto chat_up;
		}
		else
		{
			goto unknown_street;
		}
	}
	else if (friend_uninpressed)
	{
		goto return_for_wee;
	}
	else if (had_wee)
	{
		printf(
			"you friend wants to go back to yours. Will you BE SICK, CROSS\n"
			"the ROAD, or GO BACK the way you came?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "BACK") && strstr(answer, "GO"))
		{
			goto return_to_pub;
		}
		else if (strstr(answer, "ROAD") && strstr(answer, "CROSS"))
		{
			goto follow_path;
		}
		else if (strstr(answer, "SICK") && strstr(answer, "BE"))
		{
			goto be_sick2;
		}
		else
		{
			goto unknown_street;
		}
	}
	else
	{
		printf(
			"you friend is impressed. Will you CROSS the ROAD or GO BACK the\n"
			"way you came?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "BACK") && strstr(answer, "GO"))
		{
			goto return_to_pub;
		}
		else if (strstr(answer, "ROAD") && strstr(answer, "CROSS"))
		{
			goto follow_path;
		}
		else
		{
			goto unknown_street;
		}
	}

return_to_pub:
	printf(
		"\n"
		"You follow the street back into the pub.\n"
		"\n");

	goto describe_pub;

chat_up:
	printf(
		"\n"
		"you pull out all the stops. and hey it seems to have worked!.\n"
		"\n");

	friend_uninpressed = false;
	goto describe_street;

be_sick2:
	printf(
		"\n"
		"you are suddenly sick all over you friend. EWWW!\n"
		"you messed up big time!\n"
		"you then pass out.\n"
		"\n");

	friend_uninpressed = true;
	goto epic_fail;

unknown_street:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_street;

return_for_wee:
	printf(
		"you need to impress your friend but you suddenly realy need the toilet.\n"
		"you go back to the pub to look for a rest room.\n"
		"\n");

	goto describe_pub;

follow_path:
	printf(
		"\n"
		"You cross the road and follow the path to the estate.\n"
		"\n");

	goto describe_estate;

describe_estate:
	printf(
		"You are in chav-ville. you look up ahead, you can see and hear\n"
		"a couple of dodgy looking thugs. the thugs start shouting at you and\n"
		"your friend. your friend is getting upset. you best do something.\n"
		"\n"
		"Will you FIGHT the THUGS, or FLEE and as fast as you can?"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "FIGHT") && strstr(answer, "THUGS"))
	{
		goto last_chance;
	}
	else if (strstr(answer, "FLEE"))
	{
		goto flee;
	}
	else
	{
		goto unknown_path;
	}

last_chance:
	printf(
		"\n"
		"you shout abuse back at them but this just gets them more angry.\n"
		"Will you FIGHT the ANGRY THUGS, or try\n"
		"TALK your way out of the fight?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "FIGHT") &&
        strstr(answer, "ANGRY") &&
        strstr(answer, "THUGS"))
	{
		goto mess_up;
	}
	else if (strstr(answer, "TALK"))
	{
		goto lucky;
	}
	else
	{
		goto unknown_path;
	}

flee:
	printf(
		"\n"
		"You attempt to turn and run away. But, the booze gets the better of you.\n"
		"you stumble and fall into a bush. you then pass out.\n"
		"\n");

	goto epic_fail;

unknown_path:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_estate;

mess_up:
	printf(
		"\n"
		"thats it you've had enough. you charge with arms swinging at the thugs.\n"
		"But, the booze gets the better of you.\n"
		"you stumble and fall into a bush. you then pass out.\n"
		"\n");

	goto epic_fail;

lucky:
	printf(
		"you're about to talk your way out when the thugs randomly start\n"
		"laughing and just walk off in hysterics.\n"
		"confused, you go staight home.\n"
		"\n");

	goto nice;

epic_fail:
	printf(
		"you wake up in a hospital because of alcohol poisoning.\n"
		"what a terrible night.\n"
		"\n");

	goto the_end;

nice:
	printf(
		"you wake up in bed next to your friend.\n"
		"what a brilliant night out!\n"
		"\n");

the_end:
	printf("THE END\n");

	return 0;
}