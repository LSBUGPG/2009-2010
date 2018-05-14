#include <cstdio>
#include <cstring>

int main(int argc, char *argv[])
{
    const int MAXIMUM_COMMAND_LENGTH = 80;
    char answer[MAXIMUM_COMMAND_LENGTH];
	bool have_money = false;
	bool bear_seen = false;
	bool horse_seen = false;


	printf(
		"\n"
		"Welcome Adventurer, to my world. I will describe your situation,\n"
		"and you must tell me what you wish to do.\n"
		"Ensure i can hear the capitilised words \n"
		"\n"
		"Good luck!...\n"
		"\n"
		"\n"
		"          You May just need it... \n"
		"\n"
		"Or not. \n"
		"\n");

	describe_path:
	printf(
		"You have been traveling all day, you and your horse are weary.\n"
		"looking to the sky you see dusk is soon approatching.\n"
		"To your left lies a dark cave and to your right a thicket\n"
		"\n"
		"Do you TAKE the CAVE, camp UNDER the THICKET or CARRY ON as\n"
		"the next villiage can't be too far away?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	
	if (strstr(answer, "TAKE")  || strstr(answer, "CAVE"))
	{
		printf(
			" You turn your mount and head towards the cave. At the cave you \n"
			" dismount and leave your horse outside then head into the cave.\n "
		"\n");
		
	
		goto cave_description;
	}
	else if (strstr(answer, "UNDER")  || strstr(answer, "THICKET"))
	{	printf(
		"You dismount and lead you horss to the thicket. "
		"\n");
	
		goto thicket_description;
	}
	else if (strstr(answer, "CARRY")  || strstr(answer, "ON"))
	{	printf(
		"You carry on hoping to find the next villiage soon."
		"\n");
	
		goto carry_on;
	}
	else 
	{	
		printf(
		"Sorry travler I didn't understand, plese repeat your choice."
		"\n");
	
		goto describe_path;
	}
	

	cave_description:
	printf(
		"\n"
		"Having enterd the cave you are unable to explore as it is pitch black,\n" 
		"\n"
		"Do you LIGHT your torch or do you RETURN outside?\n"
		"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	
		if (strstr(answer, "LIGHT"))
		{
			printf(
			" You reach into your pack and after lighting,\n"
			"your torch you are geeeted by a small snug cave.\n "
		"\n");

			printf(
			"Looking round the cave you see first a small worn chest that could\n"
			"contain some valuables. As you step towards the chest you\n"
			"are stopped by a gruff snort, a few feet away from you a large bear is \n"
			"sleeping, as you turn to look the bear stirs, threataning to wake up.\n"
			", terified you sprint out of the cave, your sudden aperance\n"
			"along with the torch startles your horse causing it to bolt off down \n"
			"the path. You turn to run after it but trip, hit your\n"
			"head on a stone and pass out\n");
			
		
			printf(
			"When you come to dawn has broken and your horse is long gone, you bind\n"
			"your head the best you can with some cloth from your pack,\n"
			"there is little else to be done.\n"
			"\n");
		
			bear_seen = true;
			goto path_day;
		}

		else if (strstr(answer, "return"))
		{		
	printf(
		"you head outside mount and and retun to the path\n"
		"\n");
		
		goto describe_path;
		}

		else
		{
			goto cave_description;
		}
		


	thicket_description:
	printf(
		"You quickly scount the thicket and find that all seems to be in order, you\n"
		"then tie up your horse and settle down for the night.\n"
		"\n"
		"\n");
	
		
	printf(
	"You wake up not long after dawn the following day, the sky is clear and \n"
	"the sun is bright. Stretching, you look around and as your gaze strays \n"
	"to where your horse was tied up to discover it is gone, only the broken \n"
	"straps of the reigns remain\n");
	

	
		goto path_day;



	carry_on:
	printf(
	   "You have not travled far when you hear some rusteling to your left\n"
	   "before you can react a stone flys at out from a bush and knocks you off you\n"
	   "horse where you quickly loose concience\n");


	printf(
		"When you come to the sun is in the sky and your horse is long gone, \n"
		"probably taken by whoever threw the stone. You bind your head the best\n"
		" you can with some cloth from your pack, there is little else to be done.\n"
		"\n");


	goto path_day;


	path_day:
	printf(
	   "you are back on the path now but with little money and no horse things look bleak.\n"
		"Few choices are left to you, you can HEAD down the ROAD\n"
		"and hope to find the next villiage\n"
		"or do you TRY the CAVE and hope for the best\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);

	if (strstr(answer, "HEAD")  || strstr(answer, "ROAD"))
			
	{
		goto travel_villiage;
	}
	else if (strstr(answer, "TRY")  || strstr(answer, "CAVE"))
	{	
		printf(
		"you head toewards the cave hopeing to find something useful.\n "
		"\n");
	
		goto cave_day;
	}
	
	
	else 
	{	
		printf(
		"Sorry travler I didn't understand, plese repeat your choice."
		"\n");
	
		goto path_day;
	}
		
	
	cave_day:
	printf(
		"you head into the cave, it is dim but with some sunlight filtering \n"
		"through you are able to see inside,");
	
		if(bear_seen)
	{		
		printf(
			"the bear is gone,");
	
	
		goto cave_day2;
	}
		else
		{
			goto cave_day2;
		}

	cave_day2:
		printf(
			"there are some scraps of what could be bone in one corner ,\n"
			"and in another a chest it is closed but not locked.\n"
			"Do you CHECK the CHEST or do you RETURN outside?\n"
			"\n>");
		

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
			
	if (have_money)
	{
		printf(
		"You again check the chest, it remians empty as you have already\n"
		"taken the coin pouch from it.\n"
		"You have a quick glance round the rest of the cave but there is\n"
		"nothing that looks remotely useful so you head back to the path\n");

		goto path_money;
	}
	else if (strstr(answer, "CHECK")  || strstr(answer, "CHEST"))
	{		
		printf(
			" Finally you luck seams to be turning, insie the chest in a large poutch\n"
			"of coins, very useful in your present situation.\n "
		"you close the chest nad head back to the path before the owners return\n"
		"\n");
		
have_money = true;
	
		goto path_money;
	}
	else if (strstr(answer, "RETURN"))
	{	
		printf(
		"You head back outside to the path.\n "
		"\n");
	
		goto path_day;
	}
	
	else 
	{
		printf(
			"Sorry travler I didn't understand, plese repeat your choice."
		"\n");
	
		goto cave_day;
	}

path_money:
	printf(
		"With things looking up you return to the path, you seam to have \n"
		"gaind all you can from this area so, \n");
		

	
		goto travel_villiage;
	

	travel_villiage:
	printf(
		"You head down the road and after an hours walk you reach the viliage.\n");



		if (horse_seen)
		{	
			printf(
			" You head stright to the stable owner to get your horse back\n"
		
			"\n");
		}
		else
		{printf(
			"With little direction you wander round the villiage untill you spot the inn.\n"
			"\n"
			"As you reach the inn you pass the stables and to your disbelif you spot \n"
			"your horse. You cant belive your luck, as you go to open the stall the  \n"
			"stable owner, backed up by a few large men walks up to you. You explain your .\n"
			"and that this horse is yours. Unfortunately the stable owner is unmoved, \n"
			"plight but he say that dispite the fact a few shady men sold him the horse \n"
			"eariler that day. There is no way you can prove it is yours. With no\n"
			"proof and the stables guarded there is no way to simply take yor horse.\n"
			"\n");
	
	
		horse_seen = true;
			goto stable_man;
	}

	stable_man:
	printf(
	   "\n"
		"the stable own asks if you have 10 gold coins to pay for your horse.\n");
	   if (have_money)
		{  
			printf(
				"You now have the money to pay for your horse.\n"
				"Do you PAY the stable owner LEAVE him for now and search\n"
				"for other means to retrive your horse?\n"
				"\n>");
			
			fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);

	if (strstr(answer, "PAY"))
			
	{
		printf(
		   "\n"
		   "You pay the stable owner reluctantly and he returns you horse to you.\n");
	   
		   goto the_end;
	}
	else if (strstr(answer, "LEAVE") )
	{	
		printf(
		"You stubbornly refuse to pay for your own property, instead you\n "
		"decide to look elsware\n"
		"\n");
	
		goto money_look;
	}
	else 
	{	
		printf(
		"Sorry travler I didn't understand, plese repeat your choice."
		"\n");
	
		goto stable_man;
	}
			
	   }
	   else 
	   {
		   printf(
		   	"you dont have the funds, with no way to pay you \n"
			"cannot get you horse at the moment\n"
			"\n");

	goto stable_ask;
}

	stable_ask:
	printf(
	   "The stable own seem to understand you pligt but as he is not going to give \n"
	   "things away for free he offers you the chance to work as a mean of paying\n"
	   "\n"
	   "Do you ACCEPT the work or do you search ELSWARE for money\n"
	  "\n"
	   "\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);

	if (strstr(answer, "ACCEPT"))
	{
		printf(
		"You see that taking the work is your best bet,\n" 
		"it will delay you but at lest you'll get your horse.\n"
		"\n");
	
		goto have_worked;
	}
	else if (strstr(answer, "ELSWARE"))
	{
		printf(
		"You head to the villiage common, but its dresterted."
		"\n");
	
		goto money_look;
	}
	else 
	{
		printf(
		"Sorry travler I didn't understand, plese repeat your choice."
		"\n");
	
		goto stable_ask;
	}
		
	money_look:
	printf(
		"your options are few, most people in the villiage seam disinterested,\n" 
	" in no small part due to your lack of money. as you think through you options\n"
	"you remeber the cave you passed earlier\n"

	"As your options are few do you TAKE the WORK offerd to you or do you RETURN to the CAVE?"
	"\n"
	"\n>");

	fgets(answer, MAXIMUM_COMMAND_LENGTH, stdin);
	_strupr_s(answer, MAXIMUM_COMMAND_LENGTH);
	
	if (strstr(answer, "TAKE")  || strstr(answer, "WORK"))
	{	
		printf(
			"you decide to swallow your pride and work for the stable master\n"
		"\n");
		
	
		goto stable_ask;
	}
	else if (strstr(answer, "RETURN")  || strstr(answer, "CAVE"))
	{	
		printf(
		"you decided to check the cave, couldnt hurt I suppose.\n"
		"you head out of the villiage and back down the path to the cave\n"
		"\n");

		printf(
		"After a short while you reach the cave and head streight in");
	
		goto cave_day;
	}
	
	else 
	{
		printf(
			"Sorry travler I didn't understand, plese repeat your choice."
		"\n");
	
		goto money_look;
	}

have_worked:
	printf(
		"after a week working for the stable master he see that you are an honest\n"
		" and decides you have done enough to earn the horse, he gives you your \n"
		"horse and even a little extra money to help you on your way,\n"
		"you thnak him for his help then take your leave");

		goto the_end;

the_end:
	printf(
		"with nothing else to do you are eager to see the back of this villiage and\n"
		"after stocking up on a few supplies you head streight out of the villiage\n"
		"and back on your travels.\n"
		"\n"
		"\n"
		"\n"
		"THE END");


}
