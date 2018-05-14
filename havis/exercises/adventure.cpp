#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_keys = false;
	bool grate_locked = true;

	printf(
		"\n"
		"Welcome to Earth Space Docking Station!\n"
		"\n"
		"I will be describing your situation and you must type what you need to do!\n"
		"Answers must be in capitalized letters in able to play. Why you ask?\n"
		"\n"
		"Am just a computer! I have not been upgraded to understand small letters!\n" 
		"Dont moan at me am just the assistant that get updated, moan to my makers!\n"
		"\n"
		"Enjoy your work as I give your missions and read them to you!\n"
		"\n"
		"===========================================================================\n"
		"\n");
describe_computer:
	printf(
		"Computer: Welcome! Mission:\n"
		"\n"
		"Your mission is to fix the space dock window it has started\n" 
		"to crack under the sun solars activity! \n"
		"\n"
		"===========================================================================\n"
		"\n"
		"You look around quickly, you see the ESCAPE pod, which has tools inside! \n"
		"\n"
		"Will you ENTER the ESCAPE pod or FOLLOW the LINE\n"
		
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "ESCAPE") && strstr(answer, "ENTER"))
	{
	    goto enter_escape;
	}
	else if (strstr(answer, "LINE") && strstr(answer, "FOLLOW"))
	{
	    goto follow_line;
	}
	else
	{
		goto unknown_computer;
	}

enter_escape:
    printf(
        "\n"
        "You are now inside the ESCAPE pod, while looking around you see a bunch of keys!\n"
        "\n");

    goto describe_escape;

follow_line:
    printf(
        "\n"
        "You FOLLOW the LINE from the main Spacedock hull.\n"
        "\n");

    goto describe_streambed;

unknown_computer:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_computer;

describe_escape:
	printf(
		"Now will you take the bunch of keys?\n"
		"\n");

	if (have_keys)
	{
		printf(
			"Will you RETURN the KEYS to the\n"
			"hook, or GO back OUTSIDE?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "OUTSIDE") && strstr(answer, "GO"))
		{
			goto leave_escape;
		}
		else if (strstr(answer, "KEYS") && strstr(answer, "RETURN"))
		{
			goto return_keys;
		}
		else
		{
			goto unknown_escape;
		}
	}
	else
	{
		printf(
			" The keys laying there undisturbed.\n"
			"\n"
			"Will you TAKE the KEYS or GO back to the Spacedock MAINHULL?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "MAINHULL") && strstr(answer, "GO"))
		{
			goto leave_escape;
		}
		else if (strstr(answer, "KEYS") && strstr(answer, "TAKE"))
		{
			goto take_keys;
		}
		else
		{
			goto unknown_escape;
		}
	}

leave_escape:
	printf(
		"\n"
		"You leave the escape pod, back into Spacedock mainhull..\n"
		"\n");

	goto describe_computer;

return_keys:
	printf(
		"\n"
		"You return the bunch of keys to the security desk.\n"
		"\n");

	have_keys = false;
	goto describe_escape;

unknown_escape:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_escape;

take_keys:
	printf(
		"\n"
		"You take the bunch of keys and leave the ESCAPE pod, with the tools.\n"
		"\n");

	have_keys = true;
	goto describe_computer;

describe_streambed:
	printf(
		"You take your tools out ready to repair the cracked window.\n" 
		"You look up and notice that there is a large metal grate\n" 
		"covering the spacedock window.\n"
		"\n"
		"\n");

	if (grate_locked && have_keys)
	{
		printf(
			"The grate is locked. It looks like the key you have will fit the lock. Will you\n"
			"use the key to OPEN the GRATE or GO back to Spacedock MAINHULL?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "MAINHULL") && strstr(answer, "GO"))
		{
			goto return_to_computer;
		}
		else if (strstr(answer, "GRATE") && strstr(answer, "OPEN"))
		{
			goto unlock_grate;
		}
		else
		{
			goto unknown_streambed;
		}
	}
	else if (grate_locked)
	{
		goto return_for_keys;
	}
	else if (have_keys)
	{
		printf(
			"The grate is now unlocked.\n"
			"You get your tools out start fixing the cracked window\n"
			"You pick your tools up and finished fixing the window,\n"
			"\n"
			"Will you LOCK the GRATE, or GO back to the Spacedock MAINHULL?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "MAINHULL") && strstr(answer, "GO"))
		{
			goto return_to_computer;
		}
		
		else if (strstr(answer, "LOCK") && strstr(answer, "GRATE"))
		{
			goto lock_grate;
		}
		else
		{
			goto unknown_streambed;
		}
	}
	else
	{
		printf(
			"The grate is unlocked.\n"
			"Now you can fix the window and get on with the job\n"
			"\n"
			"You finished the job and all is done.\n"
			"\n"
			"Will you GO back to the Spacedock MAINHULL?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "MAINHULL") && strstr(answer, "GO"))
		{
			goto return_to_computer;
		}
		else
		{
			goto unknown_streambed;
		}
	}

return_to_computer:
	printf(
		"\n"
		"You follow the line back to the main Spacedock main hull.\n"
		"\n");

	goto describe_computer;

unlock_grate:
	printf(
		"\n"
		"The key turns reluctantly in the lock.\n"
		"\n");

	grate_locked = false;
	goto describe_streambed;

lock_grate:
	printf(
		"\n"
		"As you lock the grate, you check the window that it has not cracked again!\n"
		"\n");

	grate_locked = true;
	goto failed_adventurer;

unknown_streambed:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_streambed;

return_for_keys:
	printf(
		"The grate is locked. You'll need a key to open it. You go back\n" 
		"to the Spacedock main hull area to look for a bunch of keys.\n"
		"\n");

	goto describe_computer;

failed_adventurer:
	printf(
		"Computer : Mission Completed\n"
		"\n"	
		"Your mission now done, and happy with the job at the end.\n" 
		"You realise you do not have any more jobs to do and you then hit the pub!\n"
		"\n");

the_end:
	printf("THE END\n");

	return 0;
}
