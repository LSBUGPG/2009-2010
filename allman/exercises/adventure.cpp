#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	//  012345678901234567890123456789012345678901234567890123456789012345678901234567890
intro:
	printf(
		"\n"
		"Shh.. Don't try to speak, you've taken quite a beating. Normally we'd of done,\n"
		"much worse to traitors of the king. But alas we prison guards get bored...\n"
		"If you want to live, you'll answer our riddles or die a horrible and slow death!\n"
		"\n"
		"We're going to have fun with you, fresh meat, ehehehehe.\n"
		"\n");

describe_cell:
	printf(
		"\n"
		"You are in a dank cell, sunlight peeks in through the cracks in the wall.\n"
		"You're chained in shackles and cannot move; out of the corner of your eye,\n"
		"you can see a half eaten corpse, with a few rats still nibbling at it.\n"
		"\n");
question_one:
	printf(
		"Riddle me this boy, this thing runs but cannot walk, sometimes sings,\n"
		"but never talks, lacks arms, has hands; lacks a head but has a face.\n"
		"What is it?\n"
		"\n"
		"A CLOCK? A WAGON? A RIVER?\n"
		"\n");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "A WAGON") || strstr(answer, "A RIVER"))
	{
		goto game_over;
	}
	else if (!strstr(answer, "A CLOCK"))
	{
		goto repeat_question1;
	}
	else (!strstr(answer, "A CLOCK"));
	{
		goto question_two;
	}

question_two:
    printf(
        "\n"
        "Very good, looks like you get to live for a few more minutes.\n"
		"Now for something harder.\n"
		"What is it you must always keep, after giving it to someone else?\n"
        "\n"
		"A HANDKERCHIEF? A PROMISE? A RING?\n"
		"\n");
	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "A HANDKERCHIEF") || strstr(answer, "A RING"))
	{
		goto game_over;
	}
	else if (strstr(answer, "A PROMISE"))
	{
		goto question_three;
	}
	else if (!strstr(answer, "A PROMISE"))
	{
		goto repeat_question2;
	}
	


question_three:
	printf(
		"\n"
		"Oh ho ho, very good, there may be hope for you yet.\n"
		"Well this one's bound to be a killer, literally.\n"
		"\n"
		"What English word retains the same pronunciation.\n" 
		"even after you take away four of its five letters?\n"
		"\n"
		"TRUCE? QUEUE? JUICE?\n"
		"\n");

		fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
		_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
		if (strstr(answer, "TRUCE") || strstr(answer, "JUICE"))
		{
			goto game_over;
		}
		else if (strstr(answer, "QUEUE"))
		{ 
			goto question_four;
		}
		else if (!strstr(answer, "QUEUE"))
		{
			goto repeat_question3;
		}
	

question_four:
		printf(
			"\n"
			"Well colour me impressed, you certainly want to live don't you?\n"
			"You're almost there, just two more questions left! Don't die on me yet.\n"
			"This time I won't give you any choices.\n"
			"\n"
			"This is as light as a feather, yet no man can hold it for long.\n" 
			"What is it?\n"
			"\n"
			"Type HINT for a clue\n"
			"\n");

			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
			_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
			if (strstr(answer, "BREATH"))
			{
				goto question_finale;
			}
			else if (strstr(answer, "HINT"))
			{
				goto hint_one;
			}
			else (!strstr(answer, "BREATH"));
			{
				goto game_over;
			}
				
	
question_finale:
		printf(
			"\n"
			"Well check out the brain box on you! It's almost a shame we have somebody,\n"
			"of your intellect locked up here... Almost.\n"
			"One more question and you're a free man, you must be shaking in your breeches\n"
			"\n"
			"This old one runs forever, but never moves at all. He has not lungs nor throat,\n"
			"but still a mighty roaring call. What is it?\n"
			"\n"
			"Type HINT for a clue\n"
			"\n");

			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
			_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
			if (strstr(answer, "A WATERFALL"))
			{
				goto true_ending;
			}
			else if (strstr(answer, "HINT"))
			{
				goto hint_two;
			}
			else (!strstr(answer, "A WATERFALL"));
			{
				goto game_over;
			}
	
	
game_over:
    printf(
        "\n"
        "Ooh, tough luck, now Terrance and I get to have a little fun with you.\n"
        "And we're awfully bored, hahahaha...\n"
		"\n"
		"You were killed by the jailers for answering the question wrong.\n"
		"\n"
		"Better luck next time.\n"
		"\n"
		"Type RESTART to try again.\n"
		"\n");

			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
			_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
			if (strstr(answer, "RESTART"))
				goto intro;
			
			return 0;
		

true_ending:
	printf(
		"\n"
		"Very good indeed, but I must confess, we..err...\n"
		"Can't just let you leave, infact, we're still going to beat you,\n"
		"just not to death, today.\n"
		"\n"
		"As the guards set about you with their truncheons, you wonder if it was worth,\n"
		"answering their questions in the first place...\n"
		"\n"
		"Game Over\n"
		"\n");
	
	goto credits;

credits:
	printf(
		"\n"
		"Text Dungeon\n"
		"By\n"
		"Clinton Allman\n"
		"\n");
		
		return 0;
		

repeat_question1:
	printf(
		"\n"
		"Eh, what? Speak up peasant or you'll feel the back of my hand!\n"
		"Repeat your answer.\n"
		"\n");
	
			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
			_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
			if (strstr(answer, "A CLOCK"))
			{
				goto question_two;
			}
			else if (strstr(answer, "A WAGON") || strstr(answer, "A RIVER"))
			{
				goto game_over;
			}
			else  (!strstr(answer, "A CLOCK"));
			{
				goto repeat_question1;
			}
		
repeat_question2:
	printf(
		"\n"
		"Eh, what? Speak up peasant or you'll feel the back of my hand!\n"
		"Repeat your answer.\n"
		"\n");
	
			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
			_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
			if (strstr(answer, "A PROMISE"))
			{
				goto question_three;
			}
			else if (strstr(answer, "A HANDKERCHIEF") || strstr(answer, "A RING"))
			{
				goto game_over;
			}
			else (!strstr(answer, "A PROMISE"));
			{
				goto repeat_question2;
			}
repeat_question3:
	printf(
		"\n"
		"Eh, what? Speak up peasant or you'll feel the back of my hand!\n"
		"Repeat your answer.\n"
		"\n");
	
			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
			_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
			if (strstr(answer, "QUEUE"))
			{
				goto question_four;
			}
			else if (strstr(answer, "TRUCE") || strstr(answer, "JUICE"))
			{
				goto game_over;
			}
			else (!strstr(answer, "QUEUE"));
			{
				goto repeat_question3;
			}

hint_one:
	printf(
	"\n"
	"Heh, need help already eh, I'll give you a hint.\n"
	"Think inhale and exhale, you scum.\n"
	"\n");

			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
			_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
			if (strstr(answer, "BREATH"))
			{
				goto question_finale;
			}
			else if (strstr(answer, "HINT"))
			{
				goto hint_one;
			}
			else (!strstr(answer, "BREATH"));
			{
				goto game_over;
			}

hint_two:
	printf(
	"\n"
	"Another hint! I should gouge your eyes!.\n"
	"You often find these in jungles.\n"
	"\n");

			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
			_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
			if (strstr(answer, "A WATERFALL"))
			{
				goto true_ending;
			}
			else if (strstr(answer, "HINT"))
			{
				goto hint_two;
			}
			else (!strstr(answer, "A WATERFALL"));
			{
				goto game_over;
			}


		}
				
	