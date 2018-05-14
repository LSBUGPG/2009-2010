// adventure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_orb = false;
	bool gate_locked = true;

	printf(
		"\n"
		"Welcome the World-Above-Clouds! Read on to choose your destiny! As Mad-Sun,\n" 
		"one of the suns of The Great All-Star, you'll need to SHOUT one of the options\n" 
		"available by typing in capitals, otherwise the All-Star wont hear you and will\n" 
		"be unable to change your destiny! Good luck! .\n"
		"\n"
		"\n");

describe_cloudtops:
	printf(
		"You wake up in the beuatiful cloudtops. You can hear a nearby windstream.\n"
		"These windstream take lost stars to other areas amongst the All Star's kingdom.\n"
		"A cloud pocket appears in front of you and looks salvagable.\n"
		"\n"
		"Will you INVESTIGATE the CLOUDPOCKET or RIDE the WINDSTREAM?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "CLOUDPOCKET") && strstr(answer, "INVESTIGATE"))
	{
	    goto investigate_cloudpocket;
	}
	else if (strstr(answer, "WINDSTREAM") && strstr(answer, "RIDE"))
	{
	    goto ride_windstream;
	}
	else
	{
		goto unknown_cloudtops;
	}

investigate_cloudpocket:
    printf(
        "\n"
        "You stare deep into the cloudpocket and feel a strange warmth.\n"
        "\n");

    goto describe_cloudpocket;

ride_windstream:
    printf(
        "\n"
        "You ride the course of the windstream through the cloudtops until you reach a point\n"
        "a seemingly vacant cloud.\n"
        "\n");

    goto describe_windstreambed;

unknown_cloudtops:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_cloudtops;

describe_cloudpocket:
	printf(
		"You feel safe inside the cloud pocket.\n"
		"\n");

	if (have_orb)
	{
		printf(
			"There is a small sun orb appears as if from nowhere. Will you RETURN the ORB to the\n"
			"cloud, or GO back DOWN?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "DOWN") && strstr(answer, "GO"))
		{
			goto leave_cloudpocket;
		}
		else if (strstr(answer, "ORB") && strstr(answer, "RETURN"))
		{
			goto return_orb;
		}
		else
		{
			goto unknown_cloudpocket;
		}
	}
	else
	{
		printf(
			"A shining orb of sunlight hangs in air.\n"
			"\n"
			"Will you TAKE the ORB or GO back DOWN?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "DOWN") && strstr(answer, "GO"))
		{
			goto leave_cloudpocket;
		}
		else if (strstr(answer, "ORB") && strstr(answer, "TAKE"))
		{
			goto take_orb;
		}
		else
		{
			goto unknown_cloudpocket;
		}
	}

leave_cloudpocket:
	printf(
		"\n"
		"You leave the cloudpocket.\n"
		"\n");

	goto describe_cloudtops;

return_orb:
	printf(
		"\n"
		"You return the small orb to the cloud.\n"
		"\n");

	have_orb = false;
	goto describe_cloudpocket;

unknown_cloudpocket:
	printf(
		"\n"
		"The All Star cannot hear you.\n"
		"\n");

	goto describe_cloudpocket;

take_orb:
	printf(
		"\n"
		"You take the small orb and leave the cloudpocket.\n"
		"\n");

	have_orb = true;
	goto describe_cloudtops;

describe_windstreambed:
	printf(
		"You are at the end of the windstream. Further on you can see a gate.\n"
		"You venture closer and assume the gate is shut. However, you can feel the\n"
		"All Star behind it.\n"
		"\n");

	if (gate_locked && have_orb)
	{
		printf(
			"The sun orb glows violently. Will you place the orb inside \n"
			"the pedestal to OPEN the GATE or GO back UPSTREAM?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "UPSTREAM") && strstr(answer, "GO"))
		{
			goto return_to_cloudtops;
		}
		else if (strstr(answer, "GATE") && strstr(answer, "OPEN"))
		{
			goto unlock_gate;
		}
		else
		{
			goto unknown_windstreambed;
		}
	}
	else if (gate_locked)
	{
		goto return_for_orb;
	}
	else if (have_orb)
	{
		printf(
			"The gate shines and unlocks. Will you LOCK the gate, INVESTIGATE through the GATE, or GO\n"
			"back UPSTREAM?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "UPSTREAM") && strstr(answer, "GO"))
		{
			goto return_to_cloudtops;
		}
		else if (strstr(answer, "GATE") && strstr(answer, "INVESTIGATE"))
		{
			goto investigate_cave;
		}
		else if (strstr(answer, "LOCK") && strstr(answer, "GATE"))
		{
			goto lock_gate;
		}
		else
		{
			goto unknown_windstreambed;
		}
	}
	else
	{
		printf(
			"The gate is unlocked. Will you INVESTIGATE through the GATE or GO back UPSTREAM?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "UPSTREAM") && strstr(answer, "GO"))
		{
			goto return_to_cloudtops;
		}
		else if (strstr(answer, "GATE") && strstr(answer, "GATE"))
		{
			goto investigate_cave;
		}
		else
		{
			goto unknown_windstreambed;
		}
	}

return_to_cloudtops:
	printf(
		"\n"
		"You ride the windstream back into the cloudtops.\n"
		"\n");

	goto describe_cloudtops;

unlock_gate:
	printf(
		"\n"
		"The orb glows violently in the pedestal.\n"
		"\n");

	gate_locked = false;
	goto describe_windstreambed;

lock_gate:
	printf(
		"\n"
		"As you lock the gate you turn to dust.\n"
		"\n");

	gate_locked = true;
	goto failed_adventurer;

unknown_windstreambed:
	printf(
		"\n"
		"The All Star cannot hear you.\n"
		"\n");

	goto describe_windstreambed;

return_for_orb:
	printf(
		"The gate is locked. You'll need a sun orb to open it. You go back UPSTREAM to look\n"
		"for one.\n"
		"\n");

	goto describe_cloudtops;

investigate_cave:
	printf(
		"\n"
		"You descend through the gate and are transported even higher above the kingdom.\n"
		"\n");

	goto describe_cave;

describe_cave:
	printf(
		"You are face to face with the All Star.  He wants to test you alliegance to\n"
		"his galaxy.\n"
		"\n"
		"Will you ANSWER the ALL STAR, or RUN back through the gate?"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "ANSWER") && strstr(answer, "ALL STAR"))
	{
		goto last_chance;
	}
	else if (strstr(answer, "RUN"))
	{
		goto RUN;
	}
	else
	{
		goto unknown_cave;
	}

last_chance:
	printf(
		"\n"
		"Barehanded! Are you sure? Will you answer the All Star BAREHANDED, or think\n"
		"better of it and RUN back to the surface?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "answer") &&
        strstr(answer, "All Star") &&
        strstr(answer, "BAREHANDED"))
	{
		goto kill_AllStar;
	}
	else if (strstr(answer, "RUN"))
	{
		goto RUN;
	}
	else
	{
		goto unknown_cave;
	}

RUN:
	printf(
		"\n"
		"You run in fear from the All Star but it is too late,\n"
		"and you turn to dust.\n"
		"\n");

	goto survivor;

unknown_cave:
	printf(
		"\n"
		"The All Star cannot hear you.\n"
		"\n");

	goto describe_cave;

kill_AllStar:
	printf(
		"\n"
		"Incredibly, you answer correctly and the All Star congratulats you! You \n"
		"are granted to your wish to become an even bigger sun.\n"
		"\n");

	goto the_end;

survivor:
	printf(
		"You decide against the All Star and survived.  Other Suns will now look up to you.\n"
		"You are the real star..\n"
		"\n");

	goto the_end;

failed_adventurer:
	printf(
		"Your adventure is at an end. You turn to dust.\n"
		"\n");

the_end:
	printf("THE END\n");

	return 0;
}
