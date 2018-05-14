#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];

	printf(
		"\n"
		"To play Sams day. You must type what to do depending on the situation that's \n"
		"described Please make sure that your answer is made up of the capitalized words\n"
		"or your progression through the game could be effected.\n"
		"\n"
		"Morning!\n"
		"\n");

sams_room:
	printf(
		"You look around your room. you make your way to your bedroom door and grab the\n"
		"school bag off the floor.you put your ear to the door and listen out for \n"
		"any sounds. nobody's home and all is quiet in the house. you look\n"
		"at the clock and see that your late for school.\n"
		"\n"
		"Will you ENTER the living ROOM or GO to SCHOOL?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "ROOM") && strstr(answer, "ENTER"))
	{
	    goto enter_room;
	}
	else if (strstr(answer, "SCHOOL") && strstr(answer, "GO"))
	{
	    goto go_school;
	}
	else
	{
		goto hide_in_closet;
	}

enter_room:
    printf(
        "\n"
        "You go into the living room and play xbox for the rest of the day.\n"
        "\n");

    goto the_end;

go_school:
    printf(
        "\n"
        "You go to school and learn for most of the day but you score\n"
		" the winning goal in P.E and make new friends\n"
        "\n");

    goto the_end;

hide_in_closet:
	printf(
		"\n"
		"you hide in the closet for a little while because you thought you heard a sound.\n"
		"\n");

	goto sams_room;

the_end:
	printf("THE END\n");

	return 0;
}