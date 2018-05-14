#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	
//       01234567890123456789012345678901234567890123456789012345678901234567890123456789
	printf(
		"\n"
		"AFFAN AZMI FAILZ\n"
		"\n"
		"Right. Your adventure begins now. A situation will be presented to you and you\n"
		"are expected to provide an answer, highlighted in CAPITALS. Type an answer,\n"
		"and enjoy the result. Or not. It's entirely up to you.\n"
		"\n"
		"FAIL HARD ADVENTURER!\n"
		"\n");
	// opening sequence
opening_sequence:
	printf(
		"You are suddenly awoken by the all too familiar sound of your mobile alarm\n"
		"going off. As you slowly get up, you realise that the weekend is over and\n"
		"that you have a coding project which you must hand in at 10 a.m.\n"
		"\n"
		"No worries. That's why you set the alarm for, so you'd wake up and be able\n"
		"to hand in the work on time. You casually reach to turn off the annoying\n"
		"alarm... only to realise the alarm is on snooze and has been going off for a\n"
		"full 20 minutes. You panic. You get angry.\n"
		"\n"
		"Do you go into a SWEARING FIT or RUSH into UNIVERSITY?"
		"\n>");
	// first answer
	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "FIT") && strstr(answer, "SWEARING"))
		{
	    goto swearing_boy;
	}
	else if (strstr(answer, "UNIVERSITY") && strstr(answer, "RUSH"))
	{
	    goto into_uni;
	}
	else
	{
		goto failed_answer;
	}
// anwser options/descriptions
//      01234567890123456789012345678901234567890123456789012345678901234567890123456789
swearing_boy:
    printf(
        "\n"
        "You enter a state of incoherent and incomprehensible swearing.\n"
        "\n");

    goto describe_swearing;

into_uni:
    printf(
        "\n"
        "Stricken with panic, you quickly grab hold of your work and dash out the\n"
		"door.\n"
        "\n");

    goto describe_uni;

failed_answer:
	printf(
		"\n"
		"EPIC FAIL. That is not an answer, TRY AGAIN and actually READ this time...\n"
		"\n");

	goto opening_sequence;
//      01234567890123456789012345678901234567890123456789012345678901234567890123456789
describe_swearing:
	printf(
		"\n"
		"You spend the next 2 hours screaming and swearing. In the first hour, you begin\n"
		"to rant about how unfair life is and why the world hates you. Somewhere in the\n"
		"middle of your rage induced rant, you notice the toilet mirror and proceed to\n"
		"swear at your own reflection. You tell him how much the system is made to fail\n"
		"you, and that luck is never on your side.\n"
		"\n"
		"In the midst of your rage, you pick up your Xbox 360 and toss it at the mirror,\n"
		"hoping to destroy the evil mockery that is your reflection. Satisfied, you\n"
		"raise your arms in triumph, knowing you've exorcised your inner demons.\n"
		"\n"
		"A quick glance around the room and you've realised what a big mess you've made.\n"
		"Not only have you destroyed most of your belongings, but you have also failed\n"
		"to hand in the work, failing the course and effectively failing to build any\n"
		"sort of future for yourself. You sit in the corner crying, realising just how\n"
		"stupid you have been.\n"
		"\n"
		"You fail. You achieve nothing.\n"
		"\n");
	
	goto epic_fail;
//      01234567890123456789012345678901234567890123456789012345678901234567890123456789
describe_uni:
	printf(
		"\n"
		"You dash out onto the street, running crazily while screaming at the top of\n"
		"your voice. While you navigate through the morning crowd, you scream about\n"
		"how life is unfair and how the course is specifically desgined for you to fail.\n"
		"\n"
		"You arrive at the university and face an obstacle: the turnstiles.\n"
		"\n"
		"Do you JUMP OVER or try to produce your UNI CARD?\n"
		"\n>");
	// second answer
	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	if (strstr(answer, "OVER") && strstr(answer, "JUMP"))
		{
	    goto jump_scenario;
	}
	else if (strstr(answer, "CARD") && strstr(answer, "UNI"))
	{
	    goto card_scenario;
	}
//      01234567890123456789012345678901234567890123456789012345678901234567890123456789
jump_scenario:
	printf(
		"\n"
		"You decide to jump over the turnstiles. You're already in full sprint, time is\n"
		"against you and why bother with university procedure anyway? To hell with all\n"
		"that! You begin to focus on the goal ahead, and everything seemingly moves in\n"
		"slow motion. Your valiant charge towards the turnstiles plays out like this...\n"
		"\n"
		"15 metres.\n"
		"\n"
		"You focus on the object ahead. There can be no mistakes. You think about how\n"
		"cool you look leaping over the turnstiles at full speed, not unlike an\n"
		"Olympic athlete.\n"
		"\n"
		"10 metres.\n"
		"\n"
		"A stupid looking grin has already spread across your face at the thought of\n"
		"jumping the turnstiles. At the corner of your eye, you notice a figure moving\n"
		"into your line of sight...\n"
		"\n"
		"5 metres.\n"
		"\n"
		"The point of no return. There can be no turning back now. You've reached your\n"
		"top speed, your flimsy caffeine powered legs pushing you as hard as they can,\n"
		"but the figure earlier is now standing in front of you. At that moment you\n"
		"realise that it's the security guy, and he stands with his feet firmly spread\n"
		"and a mighty hand thrown forward, attempting to tell you to stop.\n"
		"\n"
		"4 metres.\n"
		"\n"
		"OH...\n"
		"\n"
		"1 metre.\n"
		"\n"
		"SHI...\n"
		"\n"
		"IMPACT.\n"
		"\n"
		"You hit the security guy full-on, and even manage to complete a full\n"
		"sommersault in the process. You then land, face first, into the ground.\n"
		"\n"
		"Everything goes dark. You are unable to continue because, well, your\n"
		"UNCONSCIOUS.\n"
		"\n>");
	
	goto epic_fail;
//      01234567890123456789012345678901234567890123456789012345678901234567890123456789
card_scenario:
	printf(
		"\n"
		"You stop just short of smashing into the turnstiles, realising that the\n"
		"university is very particular about the issue of identity and proper\n"
		"use of identification.\n"
		"\n"
		"You furiously pat yourself, hoping to have the item on you. You touch\n"
		"something on your chest... Yes! You always have it dangling on your neck like\n"
		"some sort of bad accessory. You slam the card on the reader, the turnstile\n"
		"clicks and you rush through... only to have the metallic shaft stab you in the\n"
		"crotch. A loud OOOMPH! escapes your lips and you hunch over in pain. It's the\n"
		"LRC, the turnstiles are built the wrong away around. You recover, try again,\n"
		"and dash towards the computer lab.\n"
		"\n"
		"You kick the door open, and you slam your work onto the tutor's desk. You raise\n"
		"your fist in the air, victorius. You run around the lab, throwing high-fives to\n"
		"your fellow coursemates. You beat the system, you beat the world that hates\n"
		"you, nothing could possibly ruin this perfect moment! Eat that world!\n"
		"\n"
		"You feel a persistent tapping on your shoulder. Your best friend is trying to\n"
		"get your attention. You look and him and ask him what. He points at the lower\n"
		"half of your body. The shocking realisation hits you.\n"
		"\n"
		"You are not wearing any pants. You just ran through the street, screaming like\n"
		"a mad person, almost destroying your crotch on the way in, and celebrated the\n"
		"glory of victory with no pants on. Now, drenched in sweat and bruised all over,\n"
		"you realise that everyone is staring.\n"
		"\n"
		"At you.\n"
		"\n"
		"And your little friend.\n"
		"\n>");

	goto epic_fail;

epic_fail:
	printf("EPIC FAIL.\n");
	
	return 0;
}