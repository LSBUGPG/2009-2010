#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_hand = false;
	bool scan_locked = true;

	printf(
		"\n"
		"Welcome to the adventure. To play, I will describe your situation, and you must\n"
		"type what to do. Ensure that you include the capitalized words in your answer as\n"
		"these are the only words I understand.\n"
		"\n"
		"Good luck spaceman!\n"
		"\n");

describe_spaceship:
	printf(
		"you are on a spaceship, drifting between galaxies on the voyage home from a mission exploring\n"
		"the far reaches of space. \n"
		"when suddenly a meteor storm rips through the bulkhead. your cryo vat goes into emergency proceedure\n"
		"and as it spits you out you slowly regain conscience to find that the other vats are destroyed\n"
		"and you are the only surviving person on the ship.what would you do?\n"
		"Will you EXPLORE the CRYO or FIND the COMPUTER?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "CRYO") && strstr(answer, "EXPLORE"))
	{
	    goto explore_cryo;
	}
	else if (strstr(answer, "COMPUTER") && strstr(answer, "FIND"))
	{
	    goto find_computer;
	}
	else
	{
		goto unknown_ship;
	}

explore_cryo:
    printf(
        "\n"
        "You manage to find your feet and begin to look around the cryo chamber .\n"
        "\n");

    goto describe_cryo;

find_computer:
    printf(
        "\n"
        "You follow the gangway until you come across a computer terminal\n"
        "you try to use the terminal- access denied.\n"
        "\n");

    goto describe_computer;

unknown_ship:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_spaceship;

describe_cryo:
	printf(
		"as you search through the debris of cryo vats,you move a large tube to find. .\n"
		"\n");

	if (have_hand)
	{
		printf(
			"the capt's mutilated body is lying on the floor. Will you RETURN the HAND\n"
			" or GO back to TERMINAL?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "TERMINAL") && strstr(answer, "GO"))
		{
			goto leave_cryo;
		}
		else if (strstr(answer, "HAND") && strstr(answer, "RETURN"))
		{
			goto return_hand;
		}
		else
		{
			goto unknown_ship;
		}
	}
	else
	{
		printf(
			"the capt's mutilated corpse on the floor, his hand severed from his body\n"
			"\n"
			"Will you TAKE the HAND or GO back to TERMINAL?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "TERMINAL") && strstr(answer, "GO"))
		{
			goto leave_cryo;
		}
		else if (strstr(answer, "HAND") && strstr(answer, "TAKE"))
		{
			goto take_hand;
		}
		else
		{
			goto unknown_ship;
		}
	}

leave_cryo:
	printf(
		"\n"
		"You leave the cryo chamber.\n"
		"\n");

	goto describe_spaceship;

return_hand:
	printf(
		"\n"
		"You return the hand to the captain and let him rest in peace.\n"
		"\n");

	have_hand = false;
	goto describe_cryo;

take_hand:
	printf(
		"\n"
		"You take the hand and leave the chamber.\n"
		"\n");

	have_hand = true;
	goto describe_computer;

describe_computer:
	printf(
		"you try bypassing the computer to find out what happened to the ship- access denied \n"
		"you ask the computer to open the bridge door- need finger print identification and\n"
		"authorisation.\n"
		"\n");

	if (scan_locked && have_hand)
	{
		printf(
			"The scan is locked. you need the capt's authorisation and identification. Will you\n"
			"use the hand to OPEN the SCAN or GO back to the CHAMBER?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "CHAMBER") && strstr(answer, "GO"))
		{
			goto return_to_chamber;
		}
		else if (strstr(answer, "SCAN") && strstr(answer, "OPEN"))
		{
			goto unlock_scan;
		}
		else
		{
			goto unknown_terminal;
		}
	}
	else if (scan_locked)
	{
		goto return_for_hand;
	}
	else if (have_hand)
	{
		printf(
			"The scan is unlocked. the bridge door swings open and a eerie sound comes from inside\n"
			" Will you LOCK the SCAN, ENTER through the BRIDGE, or GO back to CHAMBER?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "CHAMBER") && strstr(answer, "GO"))
		{
			goto return_to_chamber;
		}
		else if (strstr(answer, "BRIDGE") && strstr(answer, "ENTER"))
		{
			goto enter_bridge;
		}
		else if (strstr(answer, "LOCK") && strstr(answer, "SCAN"))
		{
			goto lock_scan;
		}
		else
		{
			goto unknown_terminal;
		}
	}
	else
	{
		printf(
			"The door is unlocked. Will you ENTER through the DOOR or GO back to CHAMBER?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "CHAMBER") && strstr(answer, "GO"))
		{
			goto return_to_chamber;
		}
		else if (strstr(answer, "DOOR") && strstr(answer, "ENTER"))
		{
			goto enter_bridge;
		}
		else
		{
			goto unknown_terminal;
		}
	}

return_to_chamber:
	printf(
		"\n"
		"You follow the gangway back into the cryo chamber.\n"
		"\n");

	goto describe_cryo;

unlock_scan:
	printf(
		"as you place the capt's severed hand on the terminal the bridge door\n"
		"unlocks and the comp says- access granted, welcome captain.\n"
		"\n");

	scan_locked = false;
	goto describe_computer;

lock_scan:
	printf(
		"\n"
		"As you lock the terminal you suddenly wake inside the cryo tube.\n"
		"\n");

	scan_locked = true;
	goto failed_spaceman;

unknown_terminal:
	printf(
		"\n"
		"does not compute- access denied.\n"
		"\n");

	goto describe_computer;

return_for_hand:
	printf(
		"The scan is locked. You'll need authorisation to open it . You go back to look\n"
		"for some.\n"
		"\n");

	goto describe_computer;

enter_bridge:
	printf(
		"\n"
		"You descend through the door into the darkness.\n"
		"\n");

	goto describe_bridge;

describe_bridge:
	printf(
		"you enter the dark room and try using the navigation computer to read the 'black box' but as you sit down\n"
		"a bright light flies into the room and approaches you. you feel terrified and look for a weeapon to use\n"
		"but as you turn, voices fill your head- its as if its trying to communicate with you.\n"
		"Will you try to COMMUNICATE with the LIGHT, or try and FIGHT it back to where it came from?"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "COMMUNICATE") && strstr(answer, "LIGHT"))
	{
		goto last_chance;
	}
	else if (strstr(answer, "FIGHT"))
	{
		goto fight;
	}
	else
	{
		goto unknown_bridge;
	}

last_chance:
	printf(
		"you drop the improvised weapon and begin walking into the anomaly, the voices becoming more coherent\n"
		"until it speaks- Ive been waiting a long time to meet you.\n"
		"do you ASK it WHY? \n"
		" or think better of it and FIGHT the light?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "ASK") &&
       strstr(answer, "WHY"))
        
	{
		goto talk_light;
	}
	else if (strstr(answer, "FIGHT"))
	{
		goto fight;
	}
	else
	{
		goto unknown_bridge;
	}

fight:
	printf(
		"\n"
		"Your heart races as you pick up a nearby blunt instrument and hurl yourself at the anomaly\n"
		"the light begins to fill the room and then dissapears.\n"
		"\n");

	goto survivor;

unknown_bridge:
	printf(
		"\n"
		"what...what, I dont understand.....whats going on?\n"
		"\n");

	goto describe_bridge;

talk_light:
	printf(
		"Incredibly, the light takes the form of a humanoid and approaches you with her arms open\n"
		" 'what happened to your ship was no accident, you have been chosen as an ambassador for your species\n"
		"it means you can never go home but you will live forever as a form of energy\n"
	"well done human. You are a true adventurer.\n"	
	"\n");

	goto the_end;

survivor:
	printf(
		"Your adventure is at an end. you have faced fear as no human could and live to tell the \n"
		"tale. You are a true survivor.\n"
		"\n");

	goto the_end;

failed_spaceman:
	printf(
		"Your adventure is at an end. You realise you do not have what it takes.\n"
		"and as a result you are to float in the endless void of space for eternity.\n"
		"\n");

the_end:
	printf("THE END?\n");

	return 0;
}
