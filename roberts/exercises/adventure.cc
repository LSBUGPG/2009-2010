#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_key = false;
	bool grate_locked = true;
//		12345678901234567890123456789012345678901234567890123456789012345678901234567890
	opening_speech:
	printf(		
		"Welcome, being. My name is Windhoof, the leader of Colkai tribe. \n"
		"I am the only person who understands the Human language in our tribe. \n"
		"But there's a catch, I can only understand the words you say loudly.\n"
		"just like this: JUMP OVER, RUN AWAY, SHOOT. Do you see how I mean?\n"
		"\n"
		"Do you understand what I mean? YES or NO?\n"
		"\n>"
		);

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "YES"))
	{
	    goto describe_location;
	}
	else if (strstr(answer, "NO"))
	{
	    goto speech_details;
	}
	else
	{
		goto opening_speech;
	}

speech_details:
    printf(
        "\n"
        "I can only understand the words that are pronounced in UPPER CASE lettering.\n"
        "Whereas the rest of the tribe are not trained to understand your \n"
		"UPPER CASE speech.\n"
        "Do you understand what I mean?\n"
		"\n"
		"YES or NO?\n"
		"\n"
		);

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "YES"))
	{
	    goto describe_location;
	}
	else if (strstr(answer, "NO"))
	{
	    goto speech_details;
	}
	else
	{
		goto opening_speech;
	}
	describe_location:
	printf(
		"\n"
		"You are in a beautiful ambient rainforest surrounded by creatures of all sizes.\n"
		"You see a small village down the hill in front of you, and to your left is \n"
		"Windhoof, and six of his followers, eager to hear of how you got there.\n"
		"\n"
		"Will you ASK WHERE YOU ARE or RUN FOR YOUR LIFE?\n"
		"\n>"
		);

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "WHERE") && strstr(answer, "ARE"))
		{
			goto lake_kalawio;
		}
		if (strstr(answer, "RUN") && strstr(answer, "LIFE"))
		{
			goto run_away;
		}
		else
		{
			goto describe_location;
		}
	

lake_kalawio:
    printf(
        "\n"
        "You are in the most dangerous river in all of our land, Lake Kalawio.\n"
        "We're incredibly curious as to how you got past our village without \n"
		"disturbing any of us on your way through.\n"
		"\n"
		"Now tell me, how did you get past our village? Do you say either, \n"
		"I KILLED YOUR GUARD, I DON'T KNOW MYSELF or I SNUCK PAST.\n"
		"\n"
		);
			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "KILLED") && strstr(answer, "GUARD"))
		{
			goto hang_time;
		}
		if (strstr(answer, "DON'T") && strstr(answer, "KNOW"))
		{
			goto confused_lost;
		}
		if (strstr(answer, "SNUCK") && strstr(answer, "PAST"))
		{
			goto snuck_past;
		}
		else 
		{ goto lake_kalawio;
		} 
	
run_away:
	printf(
		"\n"
		"Stop! Where are you going? We didn't even get a chance to talk. \n"
		"If you do that again you should fear for your life, I don't trust you. \n"
		"\n"
		"You overhear Windhoof say to a tribe member that if you are to run away again, \n"
		"he will kill you.\n" 
		"\n"
		"Do you choose to return to LAKE KALAWIO or RUN AWAY?\n"
		"\n"
		);

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "LAKE") && strstr(answer, "KALAWIO"))
		{
			goto lake_kalawio;
		}
		else if (strstr(answer, "RUN") && strstr(answer, "AWAY"))
		{
			goto run_away2;
		}
		else
		{
			goto run_away;
		}
run_away2:
		printf(
			"\n"
			"Medeni... shoot him down. What a shame to end this friendship so early.\n"
			"\n");
 goto the_end;

 		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "KILLED") && strstr(answer, "GUARD"))
		{
			goto hang_time;
		}
		if (strstr(answer, "DON'T") && strstr(answer, "KNOW"))
		{
			goto confused_lost;
		}
		if (strstr(answer, "SNUCK") && strstr(answer, "PAST"))
		{
			goto snuck_past;
		}
		else 
		{ goto lake_kalawio;
		} 

		snuck_past:
	printf(
		"\n"
		"I snuck past a guard at the entrance and used the trees for cover. \n"
		"It's not my fault that he was asleep, \n"
		"it made it easy for me to get here. \n"
		"\n"
		);

confused_lost:
	printf(
		"\n"
		"I don't know how I got here myself, i'm just as confused as you. Where is all \n"
		"my stuff that I was carrying before I passed out? \n"
		"\n"
		);
	goto your_stuff;
 //		12345678901234567890123456789012345678901234567890123456789012345678901234567890
your_stuff:
	printf(
		"\n"
		"Your stuff? You had no stuff on you when you arrived other than\n"
		"the clothes you wear on your body. What stuff do you mean?\n"
		"\n"
		"Do you mean your GUN, your DRUGS, or your CRAYONS? \n"
		"\n");

fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "GUN"))
		{
			goto why_gun;
		}
		if (strstr(answer, "DRUGS"))
		{
			goto wake_up;
		}
		if (strstr(answer, "CRAYONS"))
		{
			goto why_crayons;
		}
		else 
		{ goto your_stuff;
		} 

why_gun:
		printf(
			"\n"
			"You was carrying a gun? Why? Did you mean to cause harm to our peaceful tribe?\n"
			"No one causes harm to us, anyone who aims to is shot down. So you must now \n"
			"face your consequences.\n"
			"\n"
			);
			goto run_away2;
wake_up:
			printf(
				"\n"
				"You feel someone press their hand against your wrist to check your\n"
				"pulse before seeing your body from above.\n"
				"Drugs? He was under the influence of drugs?\n"
				"Let this be a lesson to all of you, he wouldn't have fallen off\n"
				"the ledge if he wasn't off his nut. Time of death, 23:14pm.\n"
				);
			goto the_end;

   //	12345678901234567890123456789012345678901234567890123456789012345678901234567890

hang_time:
	printf(
		"You killed our guard?! You killed Haidoka? Haidoka was my son!\n"
		"That is it! May the gods smite you down and inflict pain and misery \n"
		"upon you for however long you shall live! \n"
		"\n"
		"You are banished to the dark portal for the rest of eternity to never \n"
		"see another person, another animal another anything, other than your own \n"
		"demise for aslong as you live. \n"
		"\n"
		);
goto the_end;

why_crayons:
	printf(
		"You can't find your crayons? Poor Jimmy, Mummy will go find those for you.\n"
		"You sounded like you was having a fun game then, who was Windhoof? \n"
		"\n"
		"Congratulations, you beat the game and survived the Colkai tribe.\n"
		);
goto the_end;

	the_end:
	printf("THE END\n");

	return 0;
}
