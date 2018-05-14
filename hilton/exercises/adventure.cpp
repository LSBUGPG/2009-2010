#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_key = false;
	bool grate_locked = true;

// START
		// INTRO
	printf(
		"\n"
		"Welcome to the adventure. To play, I will describe your situation, and you must\n"
		"type what to do. Ensure that you include the capitalized words in your answer as\n"
		"these are the only words I understand.\n"
		"\n"
		"Good luck adventurer!\n"
		"\n");

	// STORY
beg_wood:
printf(
	   "You are a bear roaming the woods, you havent eaten for days as pickins are\n"
	   " slim. You come across a small glowing, rainbow coloured mushroom,\n"
	   "Do you EAT the mushroom and risk becoming the new face of Charmin or\n"
	  "Are you SMARTER than the average bear and know this probably isnt wise?\n" 
	  "\n>");


	//QUESTION 1

fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "EAT") )
		{
			printf(
				"something wasn’t quite right about that mushroom. You suddenly feel the need \n"
				"to use public transport, complain about the credit crunch, but still do\n" 
				"a little unnecessary telly-shopping...\n"
				"\n"
				"DUN!\n"
				"\n"
				"DUN!!\n"
				"\n"
				"DUN!!!\n"
				"\n"
				"This morphing mushroom has mashed your brain, you feel an\n"
				"over-whelming urge to be one with the humans.\n");


			goto shop_out;
		}
		else if (strstr(answer, "SMARTER"))
		{
			printf(
				"Didnt you hear what i said!? You’re starving...\n"
				"               Well you were... YOURE DEAD NOW\n");

			goto bad_end;
		}
		else
		{
			printf(
				"Im sorry i couldnt hear you could you repeat that");

			goto beg_wood;
		}

bad_end:
		printf(
			"you have failed in you mission to intergrrate\n"
			"with the humans please try again.\n");


shop_out:
		printf(
			"You know theres a town nearby, thats where the humans buy\n"
			"their clothes, its time to blend!\n"
			"\n"
			"\n"
			"You wonder into the outskirts of town and find the nearest clothing store.\n"
			"A sign reads Armani suits on sale now! That will do nicely, but the store is\n"
			"closed and you need to find a way in.\n"
			"\n"
			"\n"
			"Do you scale the wall and ENTER through the VENTILATION shafts or use the\n"
			"big paw PAW to break the DOOR, have I given you a clue?\n"
			"\n"
			"\n>");

			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "PAW") || strstr(answer, "DOOR"))
		{
			printf(
				"\n"
				"Great! Using the bear necessities got you in!\n"
				"\n");
			
			goto shop_inside;
		}
		else if (strstr(answer, "ENTER") || strstr(answer, "VENTILATION"))
		{
			printf(
				"\n"
				"Seriously youre a bear, theres no way you’re fitting through a vent.\n" 
				"You climb down again and look round for alternatives.\n"
				"\n");

			goto shop_out;
		}
		else
		{
			printf(
				"Im sorry i couldnt hear you could you repeat that?\n");

			goto shop_out;
		}

shop_inside:
printf(
	   "You see the Armani suits in the distance but the alarm is triggered and\n"
	   " security is heading straight for you. If you stay here you will be caught.\n"
		"Do you head for LINGERIE or HEADWEAR?\n"
		"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "LINGERIE") )
		{
			printf(
				"\n"
				"Racing through lingerie, you collide with a 38G bra, the super supportive\n"
				"elastic catapults you straight towards the Armanis, aiding your escape.\n"
				"\n");
			
			goto suit_got;
		}
		else if (strstr(answer, "HEADWEAR") )
		{
			printf(
				"\n"
				"The headwear section offers a wide array of disguises, ironically choosing\n"
				"the bee keepers hat you manage to slip by security unnoticed\n"
				"and continue on your way to the Armanis..\n" 
				"\n");

			goto suit_got;
		}
		else
		{
			printf(
				"Im sorry I couldnt hear you could you repeat that?\n");

			goto shop_inside;
		}

suit_got:
		printf(
			"Grabbing a suit you swiftly make your exit.\n"
			"\n"
			"Stopping to catch your breath in an alleyway you notice a paper\n"
			" on the floor open at the jobs section. There is an opening for a data \n"
			" analyst at Oats-so-Simple corp. Using a reverse charge call\n"
			"you arrange an interview."
			"\n"
			"\n"
			"On your way to the interview you realise this is your real test if you can\n"
			" blend in here you should be how free. You are called into the interview \n"
			"but to your dismay the interviewer has no eyes,\n"
			"regardless of this the interview continues.\n"
			"\n"
			"He scans over the leaf you handed in as a CV (obviously unable to accept the\n"
			"fact that he is blind) however he seems impressed with your credentials so has\n"
			"one final question for you, what do you think of his tie?\n"
			"\n"
			"Do you respond with RAWR or GRR?\n"
			"\n>");


			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "RAWR") )
		{
			printf(
				"\n"
				"I can tell your brown-nosing, youre just not the right man for the job,\n"
				"cant have people like that working in the company.\n"
				"\n");
			
			goto try_job;
		}
		else if (strstr(answer, "GRR") )
		{
			printf(
				"\n"
				"I like an honest man, youve got the job.\n" 
				"\n");

			goto water_cooler;
		}
		else
		{
			printf(
				"Im sorry I couldnt hear you could you repeat that?\n");

			goto suit_got;
		}

try_job:
		printf(
			"\n"
			"Your job is hanging by a thread, do you try and spark some sympathy in the\n"
			"man by putting your HAND on his ARM or do you try to REASON with HIM?\n"
			"\n>");

			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "HAND") || strstr(answer, "ARM"))
		{
			printf(
				"\n"
				"You reach out to the man and place your paw on his arm, being blind and \n"
				"oblivious to the fact you are a bear he mistake your paw for a fur coat\n"
				"which he accepts as a bribe, you get the job.\n");
			
			goto water_cooler;
		}
		else if (strstr(answer, "REASON") || strstr(answer, "HIM"))
		{
			printf(
				"\n"
				"You try and reason with the man but he cannot understand your roars and \n"
				"grunts, believing you are drunk he asks you to leave. \n" 
				"\n");
goto bad_end;
		}
		else
		{
			printf(
				"Im sorry I couldnt hear you could you repeat that?\n");

			goto try_job;
		}



water_cooler:
		printf(
			"You are shown to your cubical and are about to start work when you notice  \n"
			"the water cooler, deciding to quench your thirst you head on over. Susie \n"
			"from marketing approaches (who has eyes), if she believes your human \n"
			"anyone will. She notices your unusually abundant body hair and\n"
			"questions you about it.\n"
			"\n"
			"Do you REACH OUT as you did with the interviewer and put you paw on her \n"
			"arm or do you GESTURE out the WINDOW hoping that\n"
			"it distracts her from the question?\n"
			"\n>");

		
		
			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "REACH") || strstr(answer, "OUT"))
		{
			printf(
				"\n"
				"You reach out and touch the womans arm, she looks down, sees your claws\n"
				"and realises that you are a bear, you have be found\n"
				"out you must return  to the woods.\n");
			
			
		}
		else if (strstr(answer, "GESTURE") || strstr(answer, "WINDOW"))
		{
			printf(
				"\n"
				"Out the window is a Persian carpet shop, Susie believe you are\n"
				"gesturing that you are of Iranian heritage and take that as an\n"
				" explanation to your excessive body hair. \n" 
				"\n");

			goto the_end;
		}
		else
		{
			printf(
				"Im sorry I couldnt hear you could you repeat that?\n");

			goto water_cooler;
		}

the_end:
		printf(
			"Congratulation you have successfully blended with the humans!!\n"
			"\n"
			"The End...\n"
			"\n"
			"....\n"
			"\n"
			".... How the hell did you get that interview in the first place!?\n");



}