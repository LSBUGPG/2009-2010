#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_keys = false;
	bool door_locked = true;

	printf(
		"\n"
		"Welcome to the adventure. To play, I will describe your situation, and you must\n"
		"type what to do. Ensure that you include the capitalized words in your answer as\n"
		"these are the only words I understand.\n"
		"\n"
		"Good luck adventurer!\n"
		"\n");

describe_room:
	printf(
		"You are at school after its official closing time for detention. Your teacher is\n"
		"running late but you notice a bunch of keys. You also start to think about leaving\n"
		"as no one is there.\n"
		"Will you STAY in the ROOM or LEAVE the ROOM?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "STAY") && strstr(answer, "ROOM"))
	{
	    goto stay;
	}
	else if (strstr(answer, "LEAVE") && strstr(answer, "ROOM"))
	{
	    goto leave_room;
	}
	else
	{
		goto stay_room;
	}

stay_room:
    printf(
        "\n"
        "You stay in the room.\n"
        "\n");

    goto describe_stay_room;

leave_room:
    printf(
        "\n"
        "You follow the corridoor but notice the main entrance is locked\n"
        "where it suddenly ends.\n"
        "\n");

    goto describe_leave_room;

leave_room:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto stay_room;

describe_stay_room:
	printf(
		"You stay in the room. There is a bunch of keys on the teachers desk\n"
		"\n");

	if (have_keys)
	{
		printf(
			"You stop to think and feel a little guilty. Will you RETURN the KEYS to the desk\n"
			"or GO back to the CORRIDOOR?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "CORRIDOOR") && strstr(answer, "GO"))
		{
			goto leave_room;
		}
		else if (strstr(answer, "KEYS") && strstr(answer, "RETURN"))
		{
			goto return_keys;
		}
		else
		{
			goto unknown_room;
		}
	}
	else
	{
		printf(
			"There is a bunch of keys on the teachers desk\n"
			"\n"
			"Will you TAKE the KEY or GO back to the CORRIDOOR?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "CORRIDOOR") && strstr(answer, "GO"))
		{
			goto leave_room;
		}
		else if (strstr(answer, "KEYS") && strstr(answer, "TAKE"))
		{
			goto take_key;
		}
		else
		{
			goto unknown_room;
		}
	}

leave_room:
	printf(
		"\n"
		"You leave the room.\n"
		"\n");

	goto leave_room;

return_keys:
	printf(
		"\n"
		"You return the keys to the desk.\n"
		"\n");

	have_keys = false;
	goto describe_leave_room;

unknown_room:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_stay_room;

take_keys:
	printf(
		"\n"
		"You take the bunch of keys and leave the room.\n"
		"\n");

	have_keys = true;
	goto describe_go_corridoor;

describe_:
	printf(
		"You are at the end of the corridoor. There is a back entrance you can take\n"
		"which is locked\n"
		"\n");

	if (door_locked && have_keys)
	{
		printf(
			"The door is locked. It looks like the key you have will fit the lock. Will you\n"
			"use the key to OPEN the DOOR or GO back up the CORRIDOOR\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "CORRIDOOR") && strstr(answer, "GO"))
		{
			goto return_go_corridoor;
		}
		else if (strstr(answer, "DOOR") && strstr(answer, "OPEN"))
		{
			goto unlock_door;
		}
		else
		{
			goto unknown_go_corridoor;
		}
	}
	else if (door_locked)
	{
		goto return_for_keys;
	}
	else if (have_keys)
	{
		printf(
			"The door is unlocked. Will you LOCK the DOOR, ENTER through the DOOR, or GO\n"
			"back up the CORRIDOOR?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "CORRIDOOR") && strstr(answer, "GO"))
		{
			goto return_go_corridoor;
		}
		else if (strstr(answer, "DOOR") && strstr(answer, "ENTER"))
		{
			goto enter_door;
		}
		else if (strstr(answer, "LOCK") && strstr(answer, "DOOR"))
		{
			goto lock_door;
		}
		else
		{
			goto unknown_go_corridoor;
		}
	}
	else
	{
		printf(
			"The door is unlocked. Will you ENTER through the DOOR or GO back up the CORRIDOOR?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "CORRIDOOR") && strstr(answer, "GO"))
		{
			goto return_go_corridoor;
		}
		else if (strstr(answer, "DOOR") && strstr(answer, "ENTER"))
		{
			goto enter_door;
		}
		else
		{
			goto unknown_go_corridoor;
		}
	}

return_to_go_corridoor:
	printf(
		"\n"
		"You follow the corridoor back into the classroom.\n"
		"\n");

	goto describe_room;

unlock_door:
	printf(
		"\n"
		"The key turns and the entrance of the school opens.\n"
		"\n");

	door_locked = false;
	goto describe_go_corridoor;

lock_door:
	printf(
		"\n"
		"You lock the entrance.\n"
		"\n");

	door_locked = true;
	goto failed_adventurer;

unknown_go_corridoor:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_stay_room;

return_for_key:
	printf(
		"The door is locked. You'll need a key to open it. You go back up the corridoor and\n"
		"look for one.\n"
		"\n");

	goto describe_stay_room;

enter_door:
	printf(
		"\n"
		"You skip detention and await your destiny in the next lesson...\n"
		"\n");

	goto the_end;

failed_adventurer:
	printf(
		"Your adventure is at an end. Your teacher catches you trying to leave. You didn't\n"
		"leave quick enough\n"
		"\n");

the_end:
	printf("You skip detention and await your destiny in the next lesson...\n"
		"\n"););

	return 0;
}
