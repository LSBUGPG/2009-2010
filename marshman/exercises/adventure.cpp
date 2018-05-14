#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_strawberries = false;
	bool fetch_lady = false;
	bool alice_sad = false; 
//       12345678901234567890123456789012345678901234567890123456789012345678901234567890 = max character length.
	printf( 
		"Kidnap. A text based adventure By Spencer Marshman. \n"
		"\n"
		"Six years, six years! For too long you have been at the service of your \n"  
		"miserable employer Lord Farlington. Six years of continuous, devoted service \n" 
		"to that un-grateful bastard and what do you have to show for it? \n"
		"\n"
		"``I am sorry Harvey but we simply have to let you go, quite frankly if it \n" 
		"wasnt for my good lady wife I would of had you thrown out of here a long \n" 
		"time ago, just be thankful that I was willing to be so generous in the first \n"
		"place``. \n"
		"\n"
		"With only a week until the end of your contractual service you have no choice \n" 
		"but to find a way to secure your financial future and repay your master for \n"
		"his`generosity`. You decided to collaborate with an old acquaintance, \n" 
		"John Devlin who suggests that if you setup an easy access to the manor he \n"  
		"will kidnap Lord Farlingtons youngest daughter Alice and hold her for ransom \n" 
		"splitting the money fifty-fifty after the job is done. \n"
		"\n");

describe_hallway:
	printf(
		"Tonight is the night when you will execute your plan. \n"
		"You try to take your mind off of it during the day by running some light \n"
		"errands around the house. You are currently standing in the Main Hallway. \n"
		"Will you head to the DINING ROOM, to the KITCHEN or to your MASTERS QUARTERS?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "DINING") && strstr(answer, "ROOM"))
	{
	    goto enter_dining;
	}
	else if (strstr(answer, "KITCHEN"))
	{
	    goto enter_kitchen;
	}
	else if (strstr(answer, "MASTERS") && strstr(answer, "QUARTERS"))
	{
	    if (fetch_lady)
		{	printf(
		"\n"
		"The master will be mad if you do not return with Lady Farlington.\n"
		"You decide that it is in your best interest if you dont enter the room.\n"
		"\n");
			
			goto describe_hallway;
		}
		else {

			goto enter_master;
		}
	}
	else
	{
		goto unknown_hallway;
	}

enter_dining:
    printf(
        "\n"
		"You enter the Dining Room.\n"
        "\n");

    goto describe_dining;

enter_kitchen:
    printf(
        "\n"
        "You enter the kitchen.\n"
        "\n");

    goto describe_kitchen;

unknown_hallway:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_hallway;

describe_dining:
	if (alice_sad)
	{
		if (have_strawberries)
		{
			printf(
				"\n"
				"You return to the dining room. Alice is continuing to be a nuisance.\n"
				"You decide to give Alice a strawberry.\n"
				"\n");
			goto the_end;

		}
		else
		{
			printf(
				"\n"
				"You return to the dining room. Alice is continuing to be a nuisance.\n"
				"There is noting you can do for now.\n"
				"\n");
			goto leave_dining; 
		} 
	}
	
	printf(
		"As you step through the door you smell the aroma of what was a spectacular \n"
		"feast,you certainly will miss the cooks dinners when you have to leave.\n"    
		"The room is well lit by candlelight and sitting at the dining room table is\n"    
		"Lady Farlington and her six year old daughter Alice. \n"
		"\n"
		"Will you TALK to ALICE, or TALK to LADY Farlington or LEAVE the ROOM? \n"
		"\n>");
	
	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "TALK") && strstr(answer, "ALICE"))
	{
	    goto talk_alice;
	}
	else if (strstr(answer, "TALK") && strstr(answer, "LADY"))
	{
	    goto talk_lady;
	}
	else if (strstr(answer, "LEAVE") && strstr(answer, "ROOM"))
	{
	    goto leave_dining;
	}
	else
	{
		goto unknown_dining;
	}

talk_alice:
	printf(
		"\n"
		"``Hello Alice`` you say with a smile. She looks at you with a timid look \n" 
		"``hello`` she whimpers back. \n"
		"\n"
		"Will you TALK to LADY Farlington or LEAVE the ROOM \n"
		"\n>");
	
	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "TALK") && strstr(answer, "LADY"))
	{
	    goto talk_lady;
	}
	else if (strstr(answer, "LEAVE") && strstr(answer, "ROOM"))
	{
	    goto leave_dining;
	}
	else
	{
		goto unknown_dining;
	}

talk_lady:

if (fetch_lady)
		{	printf(
		"\n"
		"You remind Lady Farlington that she needs to get ready for the theatre.\n"
		"``Oh thankyou Harvey, I almost completely forgot``.\n"
		"As she stands to leave Alice starts to tug on her arm.\n"
		"``Mummy don't go`` Alice starts to cry as she rages into a tantrum.\n"
		"``Harvey please help me I cant afford to be late``. \n"
		"This is great, if Lady Farlington misses the theatre tonight all \n"
		"of your plans will be shot down. You need to think of something....fast \n"
		"\n");
			
			alice_sad = true; 

			goto leave_dining;
		}
		else {
	printf(
		"\n"
		"``Is there anything you require Madam?`` you ask. ``No thank you Harvey`` \n"
		"Lady Farlington looks at you with the same gentle smile she always has. \n" 
		"How you wish that you could whisk her away to somewhere in the country \n"
		"and start a new life together, alas that will never be. \n"
		"\n"
		"Will you TALK to ALICE or LEAVE the ROOM? \n" 
		"\n>");
		}

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "TALK") && strstr(answer, "ALICE"))
	{
	    goto talk_alice;
	}
	else if (strstr(answer, "LEAVE") && strstr(answer, "ROOM"))
	{
	    goto leave_dining;
	}
	else
	{
		goto unknown_dining;
	}

leave_dining:
	printf(
		"\n"
		"You leave the Dining Room.\n"
		"\n");

	goto describe_hallway;

unknown_dining:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_dining;

describe_kitchen:
	printf(
		"You are standing in the manor's kitchen. There currently seems to be no-one \n"
		"about. Sitting on the kitchen table is a big bowl of fresh strawberries. \n"
		"\n"
		"Will you PICK some STRAWBERRIES from the bowl or LEAVE the KITCHEN? \n"
		"\n>");
	
	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "PICK") && strstr(answer, "STRAWBERRIES"))
		{
			goto pick_strawberries;
		}
		else if (strstr(answer, "LEAVE") && strstr(answer, "KITCHEN"))
		{
			goto leave_kitchen;
		}
		else
		{
			goto unknown_kitchen;
		}

pick_strawberries:
	
	if (have_strawberries)
	{
	printf(
		"\n"
		"You already have some strawberries, if you take any more then someone \n"
		"will notice. \n"
		"\n");

		goto leave_kitchen;
		}	
		else
		{ 
	
		printf(
		"\n"
		"You cautiously look over your shoulder as you help yourself to some strawberries. \n"
		"\n");

		have_strawberries = true; 
			
		goto leave_kitchen;

	}

leave_kitchen: 
	printf(
		"\n"
		"You leave the kitchen and walk back into the hallway.\n"
		"\n");

	goto describe_hallway;

unknown_kitchen:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto describe_kitchen;

enter_master:
	printf(
		"\n"
		"You walk towards the door and knock. ``Enter`` you hear from the other side \n"  
		"as you open the door. \n"
		"\n");
	goto describe_master;

describe_master:
	printf(
		"\n"
		"You enter the masters quarters. Lord Farlington is finishing adjusting his  \n"
		"frock coat. He looks at you with a stern, displeasing look. \n" 
		"``Harvey, go and fetch my wife, we are suppose to be going to the theatre  \n"
		"tonight and the coach ride will take at least an hour to get there``. \n"  
		"Just as planned you knew that they would be away for most of the night \n"
		"allowing you to make your preparations for John to enter the manor with \n"  
		"relative ease. This will be the last possible opportunity you will have \n"
		"to attempt this caper as being still employed for the remainder of the week \n"
		"will relieve the suspicion from yourself as you will appear to fear \n" 
		"for the childs safety. \n"
		"\n");
	goto leave_master;

leave_master:
	printf(
		"\n"
		"You leave and close the door behind you"
		"\n"
		"\n");

	fetch_lady = true; 
	goto describe_hallway; 

the_end:
	printf("She takes the strawberry from your hand and stops crying. You promise her more \n"
		"if she decides to behave and go to bed.``Oh thankyou Harvey`` says  \n"
		"Lady Farlington with a smile, she leaves the dining room to get ready  \n"
		"for her evening out. Later that night you make all of the arrangements for \n"
		"John to enter the house and steal the girl. \n"
		"\n"
		"You dream that night of vast riches and a home to call your own. \n"
		"However your dreams are shattered as you awake to find Alice \n" 
		"dead on your bedroom floor. \n"
		"TO BE CONTINUED.... \n"
		"\n");

	return 0;
}
