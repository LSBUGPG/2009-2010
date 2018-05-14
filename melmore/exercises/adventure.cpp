#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool suit_up = false;
	bool watch_tv = false;
	bool umbrella_get = false;
	bool repeat_day = false;

	printf(
		"\n"
		"Welcome to the Life of George. To play, I will describe your situation, and you\n"
		"must type what to do. Ensure that you include the capitalized words in your\n"
		"answer as these are the only words I understand.\n"
		"\n"
		"Good luck George!\n");
	
	goto alarm_wake;

alarm_wake:	
	if (repeat_day)
	{
	printf(
		"You are woken by the dulcet tones of 'Venus' by Bananarama coming from your\n" 
		"radio alarm clock. It's 7:30am.\n"
		"You pull yourself from your bed.\n"
		"\n"
		"\n"
		"This seems awfully familiar?\n"
		"\n"
		"Must have been a weird dream?\n"
		"\n");
	
	goto room_start;
	}
	else
	{
		printf(
		"You are woken by the dulcet tones of 'Venus' by Bananarama coming from your\n" 
		"radio alarm clock. It's 7:30am. You pull yourself from your bed.\n"
		"\n");
	
	goto room_start;
	}

room_start:	
	if (suit_up && !watch_tv && umbrella_get)
	{
		printf(
			"\n"
			"You are ready for the day. You leave your appartment.\n"
			"\n");

			goto describe_street;
	}
	else if (!suit_up && watch_tv && !umbrella_get)
	{
		printf(
			"\n"
			"You turn on the TV. There is a severe weather warning of a thunder\n"
			"storm! It's going to be raining like cats and dogs later on.\n"
			"You turn the telly off.\n"
			"\n"
			"Do you leave your flat through the DOOR, get DRESSED or do you get an\n"
			"umbrella from the CUPBOARD?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "DOOR"))
		{
			goto describe_street;
		}
		else if (strstr(answer, "CUPBOARD"))
		{
			watch_tv = false;
			umbrella_get = true;
			goto room_start;
		}
		else if (strstr(answer, "DRESSED"))
		{
			watch_tv = false;
			suit_up = true;
			goto room_start;
		}
		else
		{
			goto unknown_room;
		}
	}	
	else if (suit_up && watch_tv && !umbrella_get)
	{
		printf(
			"\n"
			"You turn on the TV. There is a severe weather warning of a thunder\n"
			"storm! It's going to be raining like cats and dogs later on.\n"
			"You turn the telly off.\n"
			"\n"
			"Do you leave your flat through the DOOR or do you get an\n"
			"umbrella from the CUPBOARD?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "DOOR"))
		{
			goto describe_street;
		}
		else if (strstr(answer, "CUPBOARD"))
		{
			watch_tv = false;
			umbrella_get = true;
			goto room_start;
		}
		else
		{
			goto unknown_room;
		}
	}	
	else if (suit_up && !watch_tv && !umbrella_get)
	{
		printf(
			"\n"
			"You are now dressed, what do you want to do now?\n"
			"\n"
			"Do you leave your flat through the DOOR or do you watch some TV?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "DOOR"))
		{
			goto describe_street;
		}
		else if (strstr(answer, "TV"))
		{
			watch_tv = true;
			goto room_start;
		}
		else
		{
			goto unknown_room;
		}
	}
	else if (!suit_up && !watch_tv && umbrella_get)
	{
		printf(
			"\n"
			"You have your umbrella, what do you want to do now?\n"
			"\n"
			"Do you leave your flat through the DOOR or do you get DRESSED?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "DOOR"))
		{
			goto describe_street;
		}
		else if (strstr(answer, "DRESSED"))
		{
			suit_up = true;
			goto room_start;
		}
		else
		{
			goto unknown_room;
		}
	}
	else
	{
		printf(
			"\n"
			"Do you leave your flat through the DOOR, watch TV or get DRESSED?\n"
			"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "DOOR"))
		{
			goto describe_street;
		}
		else if (strstr(answer, "DRESSED"))
		{
			suit_up = true;
			goto room_start;
		}
		else if (strstr(answer, "TV"))
		{
			watch_tv = true;
			goto room_start;
		}
		else
		{
			goto unknown_room;
		}
	}

describe_street:
	
	if (suit_up && umbrella_get)
	{
		printf(
			"\n"
			"'You are looking dapper my man' shouts a passer-by as you leave\n"
			"your appartment.\n"
			"\n"
			"\The sky looks awfully grey, good thing you brought an\n"
			"umbrella.\n"
			"\n");
		
		goto street_scene;
	}
	else if (suit_up)
	{
		printf(
			"\n"
			"'You are looking dapper my man' shouts a passer-by as you leave\n"
			"your appartment.\n"
			"\n"
			"\The sky looks awfully grey.\n"
			"\n");

		goto street_scene;
	}
	else if (umbrella_get)
	{
		printf(
			"\n"
			"You are being looked at incredibly oddly? It's as if no one has seen a man\n"
			"in pyjamas before\n"
			"\n"
			"\The sky looks awfully grey, good thing you brought an\n"
			"umbrella.\n"
			"\n");

		goto street_scene;
	}
	else
	{
		printf(
			"\n"
			"You are being looked at incredibly oddly? It's as if no one has seen a man\n"
			"in pyjamas before\n"
			"\n"
			"\The sky looks awfully grey.\n"
			"\n");

		goto street_scene;
	}
	
street_scene:

	printf(
		"\n"
		"You find yourself on the street outside your appartment\n"
		"\n"
		"Do you go LEFT towards work or RIGHT towards the gym or BACK inside?\n"
		"\n>");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "LEFT"))
		{
			goto woman_scene;
		}
		else if (strstr(answer, "RIGHT"))
		{
			goto mime_scene;
		}
		else if (strstr(answer, "BACK"))
		{
			goto room_start;
		}
		else
		{
			goto unknown_direction;
		}

woman_scene:
	printf(
		"\n"
		"As you head towards work you see a stunning blonde on the other side\n"
		"of the road\n"
		"\n"
		"Do you WAVE to her from your side of the street, CROSS over and try your\n"
		"luck talking to her or go BACK the way you came?\n"
		"\n>");

	if (suit_up && !umbrella_get)
	{
		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "WAVE"))
		{
			printf(
				"\n"
				"It starts to rain, dang why did you not pick up your brolly?\n"
				"\n"
				"As you wave, she waves back and you realise it's Nicole from your\n"
				"building. She looks both ways and crosses the road.\n"
				"\n"
				"You ask her if she'd like to grab a cup of coffee at the\n"
				"cafe you are standing outside while the storm goes over?\n"
				"\n"
				"She says 'Yes' and you head inside before you get too wet.\n"
				"\n");

			goto cafe_end;
		}
		else if (strstr(answer, "CROSS"))
		{
			printf(
				"\n"
				"It starts to rain, dang why did you not pick up your brolly?\n"
				"\n"
				"You look both ways and cross the street. You go up to her and\n"
				"say hi. You realise it's Nicole from your building.\n"
				"\n"
				"You ask her if she'd like to grab a cup of coffee at the\n"
				"cafe across the street?\n"
				"She says 'No' as it's raining and is busy.\n"
				"\n"
				"It starts to thunder so you take shelter under a tree\n"
				"\n"
				"Lightning strikes the tree it starts falling in your dire...\n"
				"SPLAT!!!!!\n"
				"\n");
			
			repeat_day = true;
			suit_up = false;
			umbrella_get = false;
			goto alarm_wake;
		}
		else if (strstr(answer, "BACK"))
		{
			goto street_scene;
		}
		else
		{
			goto unknown_woman;
		}
	}
	else if (!suit_up && umbrella_get)
	{
		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "WAVE"))
		{
			printf(
				"\n"
				"It starts to rain, good thing you picked up your brolly?\n"
				"\n"
				"As you wave at her in your pyjamas, the woman freaks out\n"
				"and runs away!\n"
				"\n"
				"You put your umbrella up and continue to head towards work.\n"
				"\n");

			goto work_end;

		}
		else if (strstr(answer, "CROSS"))
		{
			printf(
				"\n"
				"It starts to rain, good thing you picked up your brolly?\n"
				"\n"
				"As you cross the road in your pyjamas, the woman freaks out and runs away!\n"
				"Dejected you look at your feet, forgetting you are in the middle\n"
				"of the road.\n"
				"\n"
				"You hear a horn blaring.\n"
				"\n"
				"You turn, it's a bus and.......\n"
				"SPLAT!!!!! Your umbrella goes flying into the air\n"
				"\n");

			repeat_day = true;
			suit_up = false;
			umbrella_get = false;
			goto alarm_wake;

		}
		else if (strstr(answer, "BACK"))
		{
			goto street_scene;
		}
		else
		{
			goto unknown_woman;
		}
	}
	else if (suit_up && umbrella_get)
	{
		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "WAVE"))
		{
			printf(
				"\n"
				"It starts to rain, good thing you picked up your brolly?\n"
				"\n"
				"As you wave, she waves back and you realise it's Nicole from your\n"
				"building. She looks both ways and crosses the road.\n"
				"\n"
				"You ask her if she'd like to grab dinner later?\n"
				"\n"
				"She says 'Yes' and you get her number and continue towards work.\n"
				"\n");
			
			goto work_end;
		}
		else if (strstr(answer, "CROSS"))
		{
			printf(
				"\n"
				"It starts to rain, good thing you picked up your brolly?\n"
				"\n"
				"You look both ways and cross the street. You go up to her and\n"
				"say hi. You realise it's Nicole from your building.\n"
				"\n"
				"You ask her if she'd like to grab a cup of coffee at the\n"
				"cafe across the street?\n"
				"She says 'No' as it's raining and is busy, but you convince her\n"
				"to come under your umbrella and she changes her mind.\n"
				"\n"
				"You cross the road and go into the cafe.\n"
				"\n");
				
				goto cafe_end;
		}
		else if (strstr(answer, "BACK"))
		{
			goto street_scene;
		}
		else
		{
			goto unknown_woman;
		}
	}
	else
	{
		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "WAVE"))
		{	
			printf(
				"\n"
				"It starts to rain, dang why did you not pick up your brolly?\n"
				"\n"
				"As you wave at her in your pyjamas, the woman freaks out\n"
				"and runs away!\n"
				"\n"
				"You continue to work as fast as you can since their is no\n"
				"shelter on this side of the road.\n"
				"\n");

			goto work_end;
		}
		else if (strstr(answer, "CROSS"))
		{
			printf(
				"\n"
				"As you cross the road in your pyjamas, the woman freaks out and runs away!\n"
				"Dejected you look at your feet, forgetting you are in the middle\n"
				"of the road.\n"
				"\n"
				"You hear a horn blaring.\n"
				"\n"
				"You turn, it's a bus and.......\n"
				"SPLAT!!!!!\n"
				"\n");

			repeat_day = true;
			suit_up = false;
			umbrella_get = false;
			goto alarm_wake;
		}
		else if (strstr(answer, "BACK"))
		{
			goto street_scene;
		}
		else
		{
			goto unknown_woman;
		}
	}

mime_scene:
	printf(
		"\n"
		"As you head towards the gym a street mime blocks your path\n"
		"He is rather annoying and not particularly good\n"
		"\n"
		"Do you HUMOUR him and watch his performance, SHOVE him out the way\n"
		"so you can get on with your day or go BACK the way you came?\n"
		"\n>");

	if (suit_up && !umbrella_get)
	{
		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "HUMOUR"))
		{
			printf(
				"\n"
				"The mime starts pulling an invisible rope, he starts sweating, must\n"
				"be hard work pulling that invisible rope.\n"
				"\n"
				"He ties the invisible rope to and invisible hook on the ground.\n"
				"He then puts his fingers into his pocket and pulls them out\n"
				"like scissors and cuts the invisible rope.\n"
				"\n"
				"You look up, a piano is hurtling towards you.......\n"
				"SPLAT!!!!!\n"
				"\n");

			repeat_day = true;
			suit_up = false;
			umbrella_get = false;
			goto alarm_wake;

		}
		else if (strstr(answer, "SHOVE"))
		{
			printf(
				"\n"
				"You shove him out the way, you have places to be.\n"
				"\n"
				"As you walk along the mime pulls up beside you riding what\n"
				"appears to be an invisible bike? He gives you the finger and\n"
				"shoves you! You stumble into an open manhole!\n"
				"\n"
				"\n"
				"You are falling through the darkness, hey this isn't so.....\n"
				"SPLAT!!!!!\n"
				"\n");

			repeat_day = true;
			suit_up = false;
			umbrella_get = false;
			goto alarm_wake;

		}
		else if (strstr(answer, "BACK"))
		{
			goto street_scene;
		}
		else
		{
			goto unknown_mime;
		}
	}
	else if (!suit_up && umbrella_get)
	{
		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "HUMOUR"))
		{
			printf(
				"\n"
				"The mime starts pulling an invisible rope, he starts sweating, must\n"
				"be hard work pulling that invisible rope.\n"
				"\n"
				"He ties the invisible rope to and invisible hook on the ground.\n"
				"He then puts his fingers into his pocket and pulls them out\n"
				"like scissors and cuts the invisible rope.\n"
				"\n"
				"You look up, a piano is hurtling towards you!!\n"
				"\n"
				"You raise your umbrella and the piano somehow bounces off it?\n"
				"\n"
				"You continue towards the gym.\n"
				"\n");

			goto gym_end;
		}
		else if (strstr(answer, "SHOVE"))
		{
			printf(
				"\n"
				"You shove him out the way, you have places to be.\n"
				"\n"
				"As you walk along the mime pulls up beside you riding what\n"
				"appears to be an invisible bike? He gives you the finger and\n"
				"shoves you! You stumble into an open manhole!\n"
				"\n"
				"\n"
				"You are falling through the darkness, hey this isn't so.....\n"
				"SPLAT!!!!!\n"
				"\n");

			repeat_day = true;
			suit_up = false;
			umbrella_get = false;
			goto alarm_wake;

		}
		else if (strstr(answer, "BACK"))
		{
			goto street_scene;
		}
		else
		{
			goto unknown_mime;
		}
	}
	else if (suit_up && umbrella_get)
	{
		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "HUMOUR"))
		{
			printf(
				"\n"
				"The mime starts pulling an invisible rope, he starts sweating, must\n"
				"be hard work pulling that invisible rope.\n"
				"\n"
				"He ties the invisible rope to and invisible hook on the ground.\n"
				"He then puts his fingers into his pocket and pulls them out\n"
				"like scissors and cuts the invisible rope.\n"
				"\n"
				"You look up, a piano is hurtling towards you!!\n"
				"\n"
				"You raise your umbrella and the piano somehow bounces off it?\n"
				"\n"
				"You continue towards the gym.\n"
				"\n");

			goto gym_end;
		}
		else if (strstr(answer, "SHOVE"))
		{
			printf(
				"\n"
				"You shove him out the way, you have places to be.\n"
				"\n"
				"As you walk along the mime pulls up beside you riding what\n"
				"appears to be an invisible bike? He gives you the finger and\n"
				"shoves you! You stumble into an open manhole!\n"
				"\n"
				"\n"
				"You are falling through the darkness, hey this isn't so.....\n"
				"SPLAT!!!!!\n"
				"\n");

			repeat_day = true;
			suit_up = false;
			umbrella_get = false;
			goto alarm_wake;

		}
		else if (strstr(answer, "BACK"))
		{
			goto street_scene;
		}
		else
		{
			goto unknown_mime;
		}
	}
	else
	{
		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "HUMOUR"))
		{
			printf(
				"\n"
				"The mime starts pulling an invisible rope, he starts sweating, must\n"
				"be hard work pulling that invisible rope.\n"
				"\n"
				"He ties the invisible rope to and invisible hook on the ground.\n"
				"He then puts his fingers into his pocket and pulls them out\n"
				"like scissors and cuts the invisible rope.\n"
				"\n"
				"You look up, a piano is hurtling towards you.......\n"
				"SPLAT!!!!!\n"
				"\n");

			repeat_day = true;
			suit_up = false;
			umbrella_get = false;
			goto alarm_wake;

		}
		else if (strstr(answer, "SHOVE"))
		{
			printf(
				"\n"
				"You shove him out the way, you have places to be.\n"
				"\n"
				"As you walk along the mime pulls up beside you riding what\n"
				"appears to be an invisible bike? He gives you the finger and\n"
				"shoves you! You stumble into an open manhole!\n"
				"\n"
				"\n"
				"You are falling through the darkness, hey this isn't so.....\n"
				"SPLAT!!!!!\n"
				"\n");

			repeat_day = true;
			suit_up = false;
			umbrella_get = false;
			goto alarm_wake;

		}
		else if (strstr(answer, "BACK"))
		{
			goto street_scene;
		}
		else
		{
			goto unknown_mime;
		}
	}

work_end:

if (suit_up && umbrella_get)
{
	printf(
		"\n"
		"You arrive at work and get to your desk.\n"
		"\n"
		"You complete your days work, go out with Nicole, get\n"
		"married, have 3 kids and live happily ever after\n"
		"\n");

	goto proper_end;
}
else
{
	printf(
		"\n"
		"You arrive at work in your pyjamas. The boss looks incredibly\n"
		"angry. He fires you on the spot!\n"
		"\n"
		"You head home ashamed and depressed. You head up to the roof\n"
		"of your building, go to the edge and leap screaming\n"
		"'Goodbye Cruel World!!!'\n"
		"\n"
		"As you fall you realise life isn't so ba.......\n"
		"SPLAT!!!!!\n"
		"\n");

			repeat_day = true;
			suit_up = false;
			umbrella_get = false;
			goto alarm_wake;

}

cafe_end:
	printf(
		"\n"
		"As you Nicole sit talking in the cafe a clown walks in\n"
		"playing an accordian. He swipes a man's briefcase and\n"
		"runs out leaving the accordian behind\n"
		"\n"
		"You hear the accordian bleeping.\n"
		"\n"
		"Someone shouts 'it's a bom......\n"
		"SPLAT!!!!!\n"
		"\n");
	
	repeat_day = true;
	suit_up = false;
	umbrella_get = false;
	goto alarm_wake;


gym_end:

	if (suit_up && umbrella_get)
	{
		printf(
			"\n"
			"You get to the gym, do about an hours workout and then\n"
			"head off to work.\n"
			"\n");
			
			goto work_end;
	}
	else
	{
		printf(
			"\n"
			"You enter the gym in your pyjamas and refuse you entry.\n"
			"Probably should go to work anyway don't you think, George\n"
			"\n");

			goto work_end;
	}

unknown_room:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto room_start;

unknown_direction:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto street_scene;

unknown_woman:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");

	goto woman_scene;

unknown_mime:
	printf(
		"\n"
		"I did not understand that answer.\n"
		"\n");
	goto mime_scene;

proper_end:
	printf(
		"\n"
		"Well done you have found the proper ending\n"
		"\n"
		"A normal day is the only true outcome for George to\n"
		"stay alive and stop his daily repetition\n"
		"\n"
		"Created and developed by Jon Melmore\n"
		"\n");

	return 0;

}