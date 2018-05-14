#include <cstdio>
#include <cstring>
#include <stdlib.h>// Library containing system("cls");
#include <windows.h>// Library containing Sleep(1000);

int main(int argc, char *argv[])
{
	reRun:
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool red_button_one = false; //red button in left hand room on/off
	bool red_button_two = false; //red button in right room on/off
	bool firstWake = true; // generates different text for the starting int the first room and returning to that room

system("cls");// clears screen

	printf(
		//12345678790123456789012345678901234567890123456789012345678901234567890123456789 screen size tester
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"\n"
		"                                  Wake up.......\n"
		);
	Sleep(3000);// pauses game action for three seconds

	system("cls");

	Sleep(500);

	printf(
		"\n"
		"You wake in a small, empty, white room.\n"
		"\n"
		"Somewhere unseen a speaker crackles into life.\n"
		"A flat, featureless voice speaks....\n"
		"\n"
		"\n"
		"                 'Welcome to subject testing, test number 2684.\n"
		"                  The centre would like to remind you that no\n"
		"                  responsibility will be taken for any injury\n"
		"                           recieved during testing'\n"
		"\n");

	Sleep(14000);

	printf(
		"\n"
		"              'Please wait, the test will commence in 5 seconds'\n"
		".");

	Sleep(1000);

	printf(
		".");

	Sleep(1000);

	printf(
		".");

	Sleep(1000);

	printf(
		".");

	Sleep(1000);

	printf(
		".");

	Sleep(1000);

	printf(
		".");

	system("cls");

describe_wakeUpRoom:
	if (firstWake)
	{
	printf(
		"\n"
		"To your left and right pannels in each wall begin to glow.\n"
		"The voice speaks again...\n"
		"\n"
		"                     'Please enter a door to begin'.\n"
		"\n"
		"It seems you have no choice, will you go LEFT or RIGHT?\n"
		"\n"
		">"
		);
	firstWake = false;
	}
	else
	{
	printf(
		"\n"
		"Will you go LEFT or RIGHT?\n"
		"\n"
		">"
		);
	}

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "LEFT"))
	{
	    goto go_left;
	}
	else if (strstr(answer, "RIGHT"))
	{
	    goto go_right;
	}
	else
	{
		goto unknown_wakeUpRoom;
	}

go_left:

	system("cls");

    printf(
        "\n"
        "The left hand door slides gently open as you approach it. You walk though...\n"
        "\n");

    goto describe_leftRoom;

go_right:

	system("cls");

    printf(
        "\n"
        "The right hand door slides gently open as you approach it. You walk though...\n"
        "\n");

    goto describe_rightRoom;

unknown_wakeUpRoom:

	system("cls");

	printf(
		"\n"
		"I did not understand that answer, please enter one of the words in CAPITALS\n"
		"\n");

	Sleep(1000);

	goto describe_wakeUpRoom;

describe_leftRoom:
	printf(
		"The left room is empty save for two pedistals by the far wall.\n"
		"On each pedistal is a button one red, one blue...\n"
		"\n");

	if (red_button_one)
	{
		printf(
			"The red button pulses gently, you have already activated this button...\n"
			"\n"
			"Will you press RED again, press BLUE, or RETURN to the previous room?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "RED"))
		{
			goto press_red_left;
		}
		else if (strstr(answer, "BLUE"))
		{
			goto press_blue_left;
		}
		else if (strstr(answer, "RETURN"))
		{
			goto return_left;
		}
		else
		{
			goto unknown_left;
		}
	}
	else
	{
		printf(
			"Will you press RED, press BLUE or RETURN to the previous room?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "RED"))
		{
			goto press_red_left;
		}
		else if (strstr(answer, "BLUE"))
		{
			goto press_blue_left;
		}
		else if (strstr(answer, "RETURN"))
		{
			goto return_left;
		}
		else
		{
			goto unknown_left;
		}
	}

press_red_left:
	if (red_button_one)
	{
		system("cls");

		printf(
			"\n"
			"You press the red button but nothing happens...\n"
			"\n");
	}
	else
	{
		system("cls");

		printf(
			"\n"
			"A deep humming sound begins and the floor vibrates very gently\n"
			"on the pedistal the button starts to pulse red\n"
			"\n");
		red_button_one = true;
				if (red_button_one && red_button_two)
		{
			goto finish_left;
		}
	}

	goto describe_leftRoom;

press_blue_left:
	if (red_button_one)
	{
		system("cls");

		printf(
			"\n"
			"You press the blue button and the humming sound dies away...\n"
			"The red button fades and goes dark... you have made a mistake\n"
			"\n");
		red_button_one = false;
		red_button_two = false;
	}
	else if (red_button_two)
	{
		system("cls");

		printf(
			"\n"
			"You press the blue button, the humming noise dies away...\n"
			"you have made a mistake\n"
			"\n");
		red_button_one = false;
		red_button_two = false;
	}
	else
	{
		system("cls");

		printf(
			"\n"
			"You press the blue button but nothing happens...\n"
			"\n");
	}
	goto describe_leftRoom;

unknown_left:

	system("cls");

	printf(
		"\n"
		"I did not understand that answer, please enter one of the words in CAPITALS\n"
		"\n");

	Sleep(1000);

	goto describe_leftRoom;

return_left:

	system("cls");

	printf(
		"\n"
		"You leave the left room and return to the one you woke up in.\n"
		"\n");

	if (red_button_one)
	{
		printf(
			"You can still hear the humming and feel the vibration,\n"
			"it seems to be everywhere...\n"
			"\n");
	}

	goto describe_wakeUpRoom;

describe_rightRoom:
	printf(
		"A smooth, raised bench runs down the opposite wall in the right room\n"
		"above the bench is a large screen and on the bench itself sit two buttons\n"
		"coloured red and green..."
		"\n");

if (red_button_two)
	{
		printf(
			"\n"
			"The red button pulses gently, you have already activated this button...\n"
			"\n"
			"Will you press RED again, press GREEN, or RETURN to the previous room?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "RED"))
		{
			goto press_red_right;
		}
		else if (strstr(answer, "GREEN"))
		{
			goto press_green_right;
		}
		else if (strstr(answer, "RETURN"))
		{
			goto return_right;
		}
		else
		{
			goto unknown_right;
		}
	}
	else
	{
		printf(
			"\n"
			"Will you press RED, press GREEN or RETURN to the previous room?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "RED"))
		{
			goto press_red_right;
		}
		else if (strstr(answer, "GREEN"))
		{
			goto press_green_right;
		}
		else if (strstr(answer, "RETURN"))
		{
			goto return_right;
		}
		else
		{
			goto unknown_right;
		}
	}

press_red_right:
	if (red_button_two)
	{
		system("cls");

		printf(
			"\n"
			"You press the red button but nothing happens...\n"
			"\n");
	}
	else
	{
		system("cls");

		printf(
			"\n"
			"A humming sound begins deep beneath your feet,\n"
			"on the pedistal the button starts to pulse red\n"
			"\n");
		red_button_two = true;
		if (red_button_one && red_button_two)
		{
			goto finish_right;
		}
	}

	goto describe_rightRoom;

press_green_right:
	if (red_button_two)
	{
		system("cls");

		printf(
			"\n"
			"You press the green button, the humming noise dies away...\n"
			"The red button fades and goes dark... you have made a mistake\n"
			"\n");
		red_button_one = false;
		red_button_two = false;
	}
	else if (red_button_one)
	{
		system("cls");

		printf(
			"\n"
			"You press the green button, the humming noise dies away...\n"
			"you have made a mistake\n"
			"\n");
		red_button_one = false;
		red_button_two = false;
	}
	else
	{
		system("cls");

		printf(
			"\n"
			"You press the green button but nothing happens...\n"
			"\n");
	}
	goto describe_rightRoom;

unknown_right:

	system("cls");

	printf(
		"\n"
		"I did not understand that answer, please enter one of the words in CAPITALS\n"
		"\n");

	Sleep(1000);

	goto describe_rightRoom;

return_right:
	
	system("cls");

	printf(
		"\n"
		"You leave the right room and return to the room you woke up in.\n"
		"\n");

	if (red_button_two)
	{
		printf(
			"You can still hear the humming and feel the vibration,\n"
			"it seems to be everywhere...\n"
			"\n");
	}

	goto describe_wakeUpRoom;

finish_left:

	system("cls");

	printf(
		"\n"
		"You hear a crackling sound comming from outside the room.\n"
		"Upon investigation you discover it is coming from the right hand room.\n"
		"You enter this room. The screen on the opposing wall is flickering\n"
		"with static...\n"
		"\n");
	goto end;

finish_right:

	system("cls");

	printf(
		"\n"
		"The screen on the wall flickers into life\n"
		"\n");
	
end:
	printf(	
		"A mans face appears, his left cheek is stained with blood and he appears\n"
		"very scared...\n"
		"\n"
		"           'Oh god another. Run, for gods sake get out before the....'\n"
		"\n"
		"The screen cuts out as the voice chimes in again...\n"
		"\n"
		"                  'Pattern recognition test 7_B complete'\n"
		"                           'Analysis pending'\n"
		"                              'Ending Test'\n"
		"\n"
		"An electrical shock of shoots through your body and the world fades away\n"
		"as you slip into unconsiousness...\n"
		"\n");
quit_option:
	printf(
		"Would you like to play again Y/N?"
		"\n"
		">");
	
	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "YES")||(answer, "Y"))
		{
			goto reRun;
		}
		else if (strstr(answer, "NO")||(answer, "N"))
		{
			return 0;
		}
		else
		{
		system("cls");

		printf(
			"\n"
			"I did not understand that answer, please enter YES or NO\n"
			"\n");

		Sleep(1000);

		goto quit_option;
		}
}
