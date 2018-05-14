#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_key = false;
	bool cardoor_locked = true;

	printf(
		"\n"
		"Welcome! To play, I will describe your situation, and you must\n"
		"type what to do. Ensure that you include the capitalized words in your answer as\n"
		"these are the only words I understand.\n"
		"\n"
		"Good luck!\n"
		"\n");

describe_elevator:
	printf(
		"You are in a fancy elevator. There is a console but it only has two buttons:\n"
		"ROOF and BASEMENT. Which floor do you prefer to go to?\n"
		"\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "ROOF"))
	{
	    goto enter_roof;
	}
	else if (strstr(answer, "BASEMENT"))
	{
	    goto enter_basement;
	}
	else
	{
		goto unknown_elevator;
	}

enter_roof:
    printf(
        "\n"
        "You step out of the elevator and on to the roof.\n"
        "\n");

    goto describe_roof;

enter_basement:
    printf(
        "\n"
        "You step out of the elevator and go deeper into the basement.\n"
		"There is a car parked near you.\n"
        "\n");

    goto describe_car;

unknown_elevator:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_elevator;

describe_roof:
	printf(
		"You are on a a very high and windy rooftop.\n"
		"\n");

	if (have_key)
	{
		printf(
			"There is a small metal key lying on the floor. Will you PLACE the key
			"back to the floor, or go back to the ELEVATOR?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "ELEVATOR"))
		{
			goto leave_roof;
		}
		else if (strstr(answer, "PLACE"))
		{
			goto return_key;
		}
		else
		{
			goto unknown_roof;
		}
	}
	else
	{
		printf(
			"There is a small metal key lying on the floor.\n"
			"Will you take the KEY or go back to the ELEVATOR?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "ELEVATOR"))
		{
			goto leave_roof;
		}
		else if (strstr(answer, "KEY"))
		{
			goto take_key;
		}
		else
		{
			goto unknown_roof;
		}
	}

leave_roof:
	printf(
		"\n"
		"You leave the roof and go back to the elevator.\n"
		"\n");

	goto describe_elevator;

return_key:
	printf(
		"\n"
		"You return the small key to the floor.\n"
		"\n");

	have_key = false;
	goto describe_roof;

unknown_roof:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_roof;

take_key:
	printf(
		"\n"
		"You take the small key and go back to the elevator.\n"
		"\n");

	have_key = true;
	goto describe_elevator;

describe_car:
	printf(
		"The car is satin black and has a skeleton saying 'enter' painted on its door.\n"
		"\n");

	if (cardoor_locked && have_key)
	{
		printf(
			"The car door is locked. It looks like the key you have will fit the lock.\n"
			"Will you use the key to OPEN the door or go BACK?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "BACK"))
		{
			goto return_to_elevator;
		}
		else if (strstr(answer, "OPEN"))
		{
			goto unlock_cardoor;
		}
		else
		{
			goto unknown_car;
		}
	}
	else if (cardoor_locked)
	{
		goto return_for_key;
	}
	else if (have_key)
	{
		printf(
			"The door is unlocked. Will you LOCK the door, ENTER the car, or go\n"
			"BACK?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "BACK"))
		{
			goto return_to_elevator;
		}
		else if (strstr(answer, "ENTER"))
		{
			goto enter_hell;
		}
		else if (strstr(answer, "LOCK"))
		{
			goto lock_cardoor;
		}
		else
		{
			goto unknown_car;
		}
	}
	else
	{
		printf(
			"The door is now unlocked. Will you ENTER the car or go BACK?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "BACK"))
		{
			goto return_to_elevator;
		}
		else if (strstr(answer, "ENTER"))
		{
			goto enter_hell;
		}
		else
		{
			goto unknown_car;
		}
	}

return_to_elevator:
	printf(
		"\n"
		"You follow the route back into the elevator.\n"
		"\n");

	goto describe_elevator;

unlock_cardoor:
	printf(
		"\n"
		"The key fits perfectly in the rusty old car lock.\n"
		"\n");

	cardoor_locked = false;
	goto describe_car;

lock_cardoor:
	printf(
		"\n"
		"As you lock the door you suddenly wake.\n"
		"\n");

	cardoor_locked = true;
	goto failed_adventurer;

unknown_car:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_car;

return_for_key:
	printf(
		"The door is locked. You'll need a key to open it.\n"
		"You'll need to go to find one.\n"
		"\n");

	goto describe_elevator;

enter_hell:
	printf(
		"\n"
		"You descend through the car door and into the darkness.\n"
		"\n");

	goto the_end;

failed_adventurer:
	printf(
		"Your adventure is at an end. You realise you do not have what it takes.\n"
		"\n");

the_end:
	printf("THE END\n");

	return 0;
}
