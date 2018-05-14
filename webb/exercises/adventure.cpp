#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_phone = false;
	bool grate_locked = true;
       //12345678901234567890123456789012345678901234567890123456789012345678901234567890
	printf(
		"\n"
		"Welcome to the city. Nearest thing to hell on earth.\n" 
		"To play, I will describe your situation, and you must type what to do.\n"
		"Ensure that you include the capitalized words in your answers.\n"
		"\n"
		"Try not to get yourself killed kid.\n"
		"\n"
		"You awake in a grim looking alley with a pistol to your side\n"
		"and a matchbox with 'Stacey's Dive', written across the side.\n"
		"\n"
		"You sit up to notice your shirt covered in blood, you then notice the dead\n"
		"mangled body infront of you. Blood leads up to the body leading you to believe\n"
		"it was dragged, maybe a setup?\n"
		"\n");

describe_alley:
	printf(
		
		"In a grim looking alley you can see a trail of blood.\n"
		"The sound of people talking and laughing can be heard nearby. Maybe a bar?\n"
		"\n"
		"Will you ENTER the BAR nearby or\n"
		"FOLLOW the stream of BLOOD?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "BAR") && strstr(answer, "ENTER"))
	{
	    goto enter_bar;
	}
	else if (strstr(answer, "FOLLOW") && strstr(answer, "BLOOD"))
	{
	    goto follow_blood;
	}
	else
	{
		goto unknown_alley;
	}

enter_bar:
    printf(
        "\n"
        "You enter the bar, which is crawling with the low lifes and drags of Schak City.\n"
        "\n");

    goto describe_bar;

follow_fuck:
    printf(
        "\n"
        "You follow the blood slowly back to your house where upon entry you are\n"
		"ambushed by a creature of some sort.\n"
        "\n");

    goto failed_adventurer;

unknown_alley:
	printf(
		"\n"
		"Be precise kid or your gunna get yourself killed.\n"
		"\n");

	goto describe_alley;

describe_bar:
	printf(
		"Looking around you see two suspicious looking characters in the the corner.\n"
		"They are talking to one another.\n"
		"\n");

	if (have_phone)
	{
		printf(
			"The two suspicious looking characters haven't yet noticed\n"
			"that the phone is missing.\n"
			"\n"
			"You could RETURN the PHONE or will you GO BACK and continue\n"
			"your journey?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "BACK") && strstr(answer, "GO"))
		{
			goto leave_bar;
		}
		else if (strstr(answer, "PHONE") && strstr(answer, "RETURN"))
		{
			goto return_phone;
		}
		else
		{
			goto unknown_bar;
		}
	}
	else
	{
		printf(
			"There is a mobile phone on the table.\n"
			"\n"
			"They wouldn't notice...\n"
			"\n"
			"Will you STEAL the PHONE or GO BACK?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "BACK") && strstr(answer, "GO"))
		{
			goto leave_bar;
		}
		else if (strstr(answer, "STEAL") && strstr(answer, "PHONE"))
		{
			goto take_phone;
		}
		else
		{
			goto unknown_bar;
		}
	}

leave_bar:
	printf(
		"\n"
		"You leave the bar.\n"
		"\n");

	goto describe_alley;

return_phone:
	printf(
		"\n"
		"You return the mobile phone to its rightfull owner.\n"
		"\n");

	have_phone = false;
	goto describe_bar;

unknown_bar:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_bar;

take_phone:
	printf(
		"\n"
		"You take the mobile phone and leave the bar.\n"
		"\n");

	have_phone = true;
	goto describe_alley;

follow_blood:
	printf(
		"\n"
		"You head back to your place, when your phone starts to make static noises.\n"
		"\n"
		"You pull the phone and see a face in the reflection\n"
		"of the black screen, a creature preparing to pounce at you.\n"
		"\n");

	if (have_phone)
	{
		printf(
			"You turn to see that the noise the phone is emitting has temporarily\n"
			"stunned the creature.\n"
			"\n"
			"Will you PULL your GUN out and plug the thing, or TURN BACK the way you came?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "TURN") && strstr(answer, "BACK"))
		{
			goto return_to_alley;
		}
		else if (strstr(answer, "PULL") && strstr(answer, "GUN"))
		{
			goto shoot_gun;
		}
		else
		{
			goto unknown_blood;
		}
	}
	else 
	{
		goto follow_fuck;
	}
	
shoot_gun:
		printf(
			"\n"
			"The creature now must certainly be dead.\n"
			"\n"
			"Will you SEARCH the APARTMENT or USE the PHONE to call some\n"
			"kind of emergency response unit?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		
		if (strstr(answer, "SEARCH") && strstr(answer, "APARTMENT"))
		{
			goto search_apartment;
		}
		else if (strstr(answer, "USE") && strstr(answer, "PHONE"))
		{
			goto use_phone;
		}
		else
		{
			goto unknown_gun;
		}

return_to_alley:
	printf(
		"\n"
		"You go back to the alley.\n"
		"\n");

	goto describe_alley;

use_phone:
	printf(
		"\n"
		"As you dial the number you fall unconscious.\n"
		"you awake in a cold cocooned state with an egg sitting infront of you.\n"
		"\n");

	goto failed_adventurer;

unknown_blood:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto follow_blood;

unknown_gun:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto shoot_gun;

search_apartment:
	printf(
		"\n"
		"You find a blue light in your apartment, as you get closer you get sucked\n"
		"into an abyss of darkness. Screams can be heard.\n"
		"\n");

	goto describe_hell;

describe_hell:
	printf(
		"\n"
		"You awake in hell with a huge hellhound infront of\n"
		"you and who currently has his back turned to you.\n"
		"\n"
		"He hasn't noticed you yet but you know its only a matter of time\n"
		"until he does\n"
		"\n"
		"Will you FIGHT the HELLHOUND, or FLEE back through the portal?"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "FIGHT") && strstr(answer, "HELLHOUND"))
	{
		goto last_chance;
	}
	else if (strstr(answer, "FLEE"))
	{
		goto flee;
	}
	else
	{
		goto unknown_hell;
	}

last_chance:
	printf(
		"\n"
		"Barehanded! Well you have a mobile phone and a gun with no bullets.\n"
		"\n"
		"Are you sure?\n"
		"\n"
		"Will you FIGHT the HELLHOUND BAREHANDED, or think\n"
		"better of it and FLEE back to the reality you came from?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "FIGHT") &&
        strstr(answer, "HELLHOUND") &&
        strstr(answer, "BAREHANDED"))
	{
		goto kill_hellhound;
	}
	else if (strstr(answer, "FLEE"))
	{
		goto flee;
	}
	else
	{
		goto unknown_hell;
	}

flee:
	printf(
		"\n"
		"You walk back through the blue portal from which you came, quite so not to scare the hellhound.\n"
		"As you awake back in your apartment, you find the creature you thought you killed, looking you in the eye.\n"
		"\n");

	goto survivor;

unknown_hell:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_hell;

kill_hellhound:
	printf(
		"\n"
		"Incredibly, you fight and kill the the hellhound with your harsh\n"
		"language and incredible new Nokia mobile phone!\n"
		"\n"
		"You wake, with newfound confidence. You are a true killer!.\n"
		"\n");

	goto the_end;

survivor:
	printf(
		"Your adventure is at an end. You have faced a hellhound and yet live to tell the\n"
		"tale. You are a true survivor.\n"
		"\n");

	goto the_end;

failed_adventurer:
	printf(
		"You won't wake up this time.\n"
		"\n");

the_end:
	printf("THE END\n");

	return 0;
}
