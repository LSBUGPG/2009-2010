#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];	

the_crossroad:
	printf(
	    "\n"
		"You are walking home late one night. You are feeling tired.\n" 
		"You have stopped at a cross road. There are two routes that you can take home.\n"
		"ROUTE A is a long well lit road and will take you an hour to get home.\n"
		"ROUTE B takes you through the park that is not well lit.\n"
		"However, it would only take half the time.\n"
		"Will you take ROUTE A or ROUTE B?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "ROUTE") && strstr(answer, "A"))
	{
	    goto route_a;
	}
	else if (strstr(answer, "ROUTE") && strstr(answer, "B"))
	{
	    goto route_b;
	}
	else
	{
		goto unknown_routes1; 
	}

route_a:
    printf(
       "\n"
        "You are walking down ROUTE A. Suddenly the lampposts starts to flicker.\n" 
		"As you continue down the road, all the lampposts ahead turned off.\n" 
		"Strangely, the lamppost leading back to the crossroad are still lit.\n"
        "\n");
	{
		goto the_crossroad;
	}

route_b:
	    printf(
		"\n"
		"You are walking through the park. You hear a faint crying\n" 
		"coming from the children’s playground on your right.\n"
	    "You turn to your right and see a small girl sitting on the swing.\n"
        "Will you APPROACH her or IGNORE her?.\n"
        "\n");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
    if (strstr(answer, "APPROACH")) 
    {
	    goto approach_her;
	}
	else if (strstr(answer, "IGNORE"))
	{
	    goto ignore_her;
	}
	else
	{
		goto unknown_b;
	}

unknown_b:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto route_b;


ignore_her:
		printf(
			"\n"
			"You are feeling too tired to help. You decided to ignore her and go home.\n"
			"As you are walking home you still hear the girl crying.\n"
			"do you want to go BACK or CARRY ON home?\n"
		    "\n");
   fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer,"BACK"))
	{
		goto route_b;
	}
	else if (strstr(answer, "CARRY") && strstr(answer, "ON")) 
	{
		goto haunting_end;
	}
	else
	{
		goto unknown_answer3;
	}
 unknown_answer3:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto ignore_her;


haunting_end:
     printf(
	 "\n"
	 "You decided to head home. The crying stopped as you got into your house.\n"
	 "As you get into bed you hear the crying again.\n"
	 "You sit up and at the end of your bed you see the girl standing there.\n"
	 "You can’t see her face but you can see her glowing red eyes.\n"
	 "\n");
	 goto the_end;

 unknown_routes1:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto the_crossroad;


approach_her:
    printf(
	"\n"
	"As you approach the girl she stops crying and turns her head towards you.\n"
	"The lighting in the park was so dim that you can’t see her face.\n" 
	"You can slightly see the hat she is wearing. It has 2 patterns blue hearts and red ribbons.\n"
    "\n"
	"The girl begins to talk to you. She is asking if you can help her find her favourite toy\n"
	"that her Grandma gave to her. She lost it in the park. \n"
	"\n");

goto describe_task;


describe_task:
    printf(
		"\n"
		"You decided to help the girl. She tells you that you only have one chance\n" 
		"to give her the correct toy.\n" 
        "Now you need to search the playground for her favourite toy.\n" 
    	"\n");
		
		{
			goto the_playground;
		}

the_playground:
	printf(
		"\n"
		"You look around the play ground you see something near the merry-go-round.\n"
		"As you got closer to you see two toys a BLUE TEDDY and a PINK DOLL.\n"
        "Which one will you take to her?\n"
		"\n");
		
	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
    if (strstr(answer, "BLUE") && strstr(answer, "TEDDY"))
    {

	    goto the_goodend;
	}
	else if (strstr(answer, "PINK") && strstr(answer, "DOLL"))
	{
	    goto wrong_answer;
	}
	else
	{
		goto unknown_answer2;
    }

unknown_answer2:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto the_playground;

the_goodend:
     printf(
     "\n"
	 "You approach the small girl and gave her the toy.\n"
	 "She thanked you and walked away in the darkness.\n" 
	 "You couldn’t see her anymore. You walked home feeling a bit crazy.\n"
     "\n"
	 "The end\n"
	 "\n");
 goto the_end;

wrong_answer:
   printf(
		"\n"
		"You gave her the toy. She looks sad and disappeared.\n" 
		"You felt relief thinking thats it finally over.\n"
		"\n");

	goto haunting_end;

unknown_answer4:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto the_end;

the_end:
	printf(
		"\n"
		"THE END\n"
	    "Do you want to play again?\n"
		"YES or NO?\n"
		"\n");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
  
	if (strstr(answer,"YES"))
    {

	    goto the_crossroad;
	}
	else if (strstr(answer,"NO"))
	{
	    goto the_finalend;
	}
	else
	{
		goto unknown_answer4; 
    }


the_finalend: 
	printf("THE END\n"); 

	return 0;
}
