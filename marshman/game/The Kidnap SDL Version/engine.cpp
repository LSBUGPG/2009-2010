#include <windows.h>
#include <SDL.h>
#include <math.h>

#include "graphics.h"
#include "audio.h"
#include "console.h"

bool fetch_lady = false;
int straw = 5;
bool alice_sad = false;
bool have_candle = false;
bool have_coin = false;
bool used_booth = false;
bool bought_drink = false;
bool have_paper = false;
bool susan_talk = false;
bool captain_talk = false;
bool fight_sailor = false;
bool dispose_alice = false;
void quit(int code)
{
	Mix_CloseAudio();
    SDL_Quit();
    exit(code);
}

void handle_key(SDL_keysym *key)
{
	switch (key->sym)
	{
	case SDLK_ESCAPE:
		quit(0);
		break;
	default:
		console_put_key(char(key->sym));
		break;
	}
}

void process_events(void)
{
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt))
	{
        switch (evnt.type)
		{
		case SDL_KEYUP:
		    handle_key(&evnt.key.keysym);
			break;
		case SDL_QUIT:
		    quit(0);
		    break;
        }
    }
}

                           //////////////////////////////TITLE PAGE///////////////////////////////////
void game(void)
{
	console_print("The Kidnap. A text adventure By Spencer Marshman.");
	console_print(" ");
	console_print(" ");
	console_print(" ");
	console_print("To play, I will describe to you what available options you have in you're current situation. You can "
				"select these options by pressing the corresponding number key.");
	console_print(" ");
	console_print(" ");
	console_print("Best of luck on your journey");
	console_print(" ");
	console_print(" ");
	console_print(" ");
	console_print("Press any key to continue");
	char key = console_get_key();
	

							//////////////////////////////INTRODUCTION///////////////////////////////////
intro: 	
	console_print("");
	console_print("");
	console_print(" ");
	console_print("Six years, six years! For too long you have been at the service of your miserable employer "
				"Lord Farlington.     Six years of continuous, devoted service to that ungrateful bastard and what "
				"do you have to show for it? ");
	console_print(" ");
	console_print("\"I'm sorry but we simply have to let you go, quite frankly if it wasn't for my good lady wife "
				"I would of had you thrown out of here a long time ago, just be thankful that I was willing to be "
				"so generous in the first place\".");
	console_print(" ");
	console_print("Your entire life had been dedicated to the maintenance of Thornley Manor, laid before you a "
				"proud history of service maintained by members of your family for generations."
				"Your previous employer Lady Huntsfield was a kind and generous woman who appreciated all that you "
				"did for her until her dying day.");
	console_print(" ");
	console_print(" ");
	console_print(" ");
	console_print("Press any key to continue");
	key = console_get_key();
		
	console_print(" ");
	console_print(" ");
	console_print(" ");
	console_print("With only a week until the end of your contractual service you have no choice but to find a "
				"way to secure your financial future and repay your current employer for his \"generosity\". "
				"You decided to collaborate with an old acquaintance, John Devlin who suggests that if you "
				"setup an easy access to the manor he will kidnap Lord Farlington's youngest daughter Alice "
				"and hold her for ransom splitting the money fifty-fifty after the job is done. With little choice "
				"you decide to go ahead with this devious scheme but only on the condition that the child is "
				"not harmed.\"But of course\" smiles Devlin.");
	console_print("");
	console_print("");
	console_print("");
						    //////////////////////////////ACT ONE///////////////////////////////////

hallway: // hallway at the start of the game//
	console_print("Tonight is the night when you will execute your plan.   You try to take your mind off of it "
				  "during the day by running some light errands around the house. "
				  "You are currently standing in the main hallway of Thornley Manor. ");
	console_print("");
	console_print("Will you:");
	console_print("  1) Head to the dining room?");
	console_print("  2) Head to the kitchen?");
	console_print("  3) Head to your masters quarters?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("You enter the dining room.");
		console_print("");
		goto dining;
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You enter the kitchen.");
		console_print("");
		goto kitchen;
	}
	else if (key == '3')
	{
		console_print("");
		console_print("You walk towards the door of your masters quarters and knock." 
					"\"Enter\" you hear from the other side as you open the door.");
		goto quarters;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer");
		console_print("");
		console_print("");
		goto hallway;
	}
							
hallway_new: //On return to hallway from another room//
	console_print("");
	console_print("You are currently standing in the main hallway.");
	console_print("");
	console_print("Will you:");
	console_print("  1) Head to the dining room?");
	console_print("  2) Head to the kitchen?");
	console_print("  3) Head to your masters quarters?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("You enter the dining room.");
		console_print("");
		goto dining;
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You enter the kitchen.");
		console_print("");
		goto kitchen;
	}
	else if (key == '3')
		
		if (fetch_lady)
	{
		console_print("");
		console_print("The master will be mad if you do not return with Lady Farlington. " 
					  "You decide that it is in your best interest if you do not enter the room.");
		goto hallway_new;
	}
		
		if (!fetch_lady)
	{
		
		console_print("");
		console_print("You walk towards the door of your Masters Quarters and knock." 
					"\"Enter\" you hear from the other side as you open the door.");
		goto quarters;
	
}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto hallway_new;
	}
dining:	// the dining room//			
		if (alice_sad && straw < 5)

	{
		console_print (""); 
		console_print ("As you open the door you can see that Alice is continuing to be a nuisance. " 
					   "Hoping that it will calm the situation you decide to give Alice a strawberry. "); 
		

		
		goto cutscene_1;
		
		}
		if (alice_sad)
			
		{
		
		console_print ("Alice is continuing to be a nuisance and still refuses to leave. " 
					   "You attempt to reason with the girl but she starts kicking and screaming. \"I want a strawberry\" cries Alice. You decide that " 
					   "there is nothing you can do right now. ");
		goto hallway_new;
		} 
		
		if (!alice_sad)
		
		{	

		console_print("As you step through the door you smell the aroma of what must have been a spectacular feast, "
				  "you will certainly miss the cooks dinners when you have to leave. The room is well lit by "
				  "candlelight and sitting at the dining room table is Lady Farlington and her six year old "
				  "daughter Alice.");
	console_print("");
	console_print("Will you:");
	console_print("  1) Talk to Alice?");
	console_print("  2) Talk to Lady Farlington?");
	console_print("  3) Or leave the dining room?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto talk_alice;
	}
	else if (key == '2')
	{
		console_print("");
		goto talk_lfarlington;
	}
	else if (key == '3')
	{
		console_print("");
		console_print("You leave the dining room ");
		goto hallway_new;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto dining;
	}
		}
talk_alice: //talk to alice//
	console_print("");
	console_print("\"Hello Alice\" you say with a smile. She looks at you with a timid look \"hello\" she whimpers back. ");
	console_print("");
	console_print("Will you:");
	console_print("  1) Talk to Lady Farlington?");
	console_print("  2) Or leave the dining room?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto talk_lfarlington;
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You leave the dining room");
		goto hallway_new;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer");
		console_print("");
		console_print("");
		goto talk_alice;
	}
talk_lfarlington: //talk to lady farlington//
	
	if (!fetch_lady)
	{
	console_print("");
	console_print("\"Is there anything you require Madam?\" you ask. \"No thank you\" Lady Farlington looks at "
					"you with the same gentle smile she always has. You always found it hard to believe that a "
					"woman who could be so gentle and sweet would be married to man such as Mr Farlington. ");
	console_print("");
	console_print("Will you:");
	console_print("  1) Talk to Alice?");
	console_print("  2) Or leave the dining room?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto talk_alice;
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You leave the dining room");
		goto hallway_new;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer");
		console_print("");
		console_print("");
		goto talk_lfarlington;
	}
}
	if (fetch_lady)
	{
		console_print("");
		console_print("You remind Lady Farlington that she needs to get ready for the theatre. \"Oh thankyou, I "
					  "almost completely forgot.\" As she stands to leave Alice starts to tug on her arm. Mummy don't "
					  "go. Alice starts to cry as she rages into a tantrum. Please help me I cant afford to be late. This "
					  "is great, if Lady Farlington misses the theatre tonight all of your plans will be shot down. You "
					  "need to think of something....fast. ");
	
			alice_sad = true;
			goto hallway_new;
	}

kitchen:   //kitchen//
	console_print("");
	console_print("You are standing in the manor's kitchen. It is somewhat messy as evidently it appears that a "
				  "meal was just recently prepared here. The cook isn't currently present at the moment and the "
				  "room seems to be empty. You notice sitting on the kitchen table is a big bowl of fresh strawberries. ");
	console_print("");
console_print("Will you:");
	console_print("  1) Pick some stawberries from the bowl?");
	console_print("  2) Or leave the kitchen?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		if (straw == 0)
		{
			console_print("");
			console_print("You realise that in your greed you have foolishly helped yourself to too many strawberries. "
						  "Paniking you leave the kitchen immediately. ");
		goto hallway_new;
		}
		else
		{
		straw--;
		console_print("");
		console_print("You look cautiously over your shoulder as you help yourself to some strawberrys. "
				      "You decide to eat one now and leave the rest in your pocket for later. "
					  "You hastily leave hoping that no-one notices the missing strawberries. ");  
		goto hallway_new;
		}
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You leave the kitchen and walk back into the hallway. ");
		goto hallway_new;
	}
	else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer");
		console_print("");
		console_print("");
		goto kitchen;
	}

quarters: //master farlingtons quarters //
		console_print("");
		console_print("You enter the master's quarters. Lord Farlington is finishing adjusting his frock coat. He "
					  "looks at you with a stern, displeasing look. \"Go and fetch my wife, we are suppose to be "
					  "going to the theatre tonight and the coach ride will take at least an hour to get there\". " 
					  "Just as planned you knew that they would be away for most of the night allowing you to make your "
					  "preparations for John to enter the manor with relative ease. This will be the last possible "
					  "opportunity you will have to attempt this caper as being still employed for the remainder of safety "
					  "You leave and close the door behind you. ");
		 
	{	
		fetch_lady = true;
		goto hallway_new;
	}

cutscene_1: // after giving a strawberry to alice //
		console_print ("");
		console_print ("She takes the strawberry from your hand and stops crying. You promise her more if she "
					   "decides to behave and go to bed.\"Oh thankyou\" says Lady Farlington with a smile, she leaves "
					   "the dining room to get ready for her evening out. "); 
	    console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
	    key = console_get_key();
		console_print(" ");
		console_print(" ");
		console_print(" ");
		console_print(" ");
		console_print ("Later that night you make all of the arrangements for John to enter the house and steal the girl. " 
			           "You dream that night of vast riches and a home to call your own. You awake the next morning full of " 
					   "hope for the future knowing that in the next few days that you will be well off for the rest of your life. " 
					   "However your dreams are shattered as you look down to find Alice dead on your bedroom floor. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
	    key = console_get_key();

bedroom: //your bedroom//
		console_print(" ");
		console_print(" ");
		console_print("A streak of cold blind terror creeps through you as you can't help but gaze upon the "
					  "still body of the young girl on the floor. You hover your hand over her mouth just to make "
					  "sure. You feel grief stricken as you feel no breath from her what so ever. You hastily dress, "
					  "attempting to figure out what your next plan of action should be...... suddenly you hear the "
					  "creaking of footsteps head towards your room. With little time to decide you must act now or "
					  "risk being discovered. ");
		console_print("");
console_print("Will you:");
	console_print("  1) Leave the room immediately?");
	console_print("  2) Take Alice's body with you?");
	console_print("  3) Or will you first check your desk drawers for something that could be of use?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto gameover_1;
	}
	else if (key == '2')
	{
		goto pick_body;

	} 
	else if (key == '3')
	{
		console_print("");
		console_print("You quickly rush over to your desk");
		goto check_desk;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto bedroom;
	}

check_desk: //your desk draws, contains the candle you need to access cave//
		console_print("");
		console_print("You hastily open the desk draws hoping to find something that will be of use to yourself. All "
					  "you can find is a pencil, a small diary book, some small candles and a box of matches. "
					  "Without much thought you quickly grab the items and stuff them into your coat pocket. ");

	  	have_candle = true;
		
		console_print("");
console_print("What will you do now:");
	console_print("  1) Take the body of Alice and leave?");
	console_print("  2) Leave your room immediately?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
	goto pick_body;
	}
	else if (key == '2')
	{
		console_print("");
		goto gameover_1;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto check_desk;
	}
	  
gameover_1: // if you leave without taking alice's body with you //
		console_print("");
		console_print("You dart out of the room with great haste and speed towards the grand staircase. On your way "
					  "out of your door you bump into one of the maids. As the maid turns to face you expecting an "
					  "apology she stares into your eyes noticing the panicked expression on your face. By the time "
					  "you have made it down to the main hallway you hear a scream emanating from your room. "
					  "You desperately attempt to evade capture from the authorities but they promptly find you "
					  "within the week. Branded as a sick child killer your trial is swift and your sentence, brutal. "
					  "The last thing you see is the hood being placed over your head as the crowd cry for you to be "
					  "hung until death. Without being able to prove your innocence, your journey ends here. ");      

		goto the_end;

pick_body: // taking alices body with you lets you progress on to act 2//
		
		console_print("");
		console_print("You pick up Alice's lifeless body from the floor. Her face is cold and expressionless, your "
					  "mind starts to wonder as to who could do such a thing to someone so innocent. Your senses "
					  "focus once again on the sound of footsteps drawing ever closer, with hurriedness you quickly "
					  "slam your door and hold your back up against it. You breath becomes shallow as you hear a "
					  "knocking from the other side. \"May I come in? I've come to fetch your clothes\". You inform "
					  "the maid that you are currently indisposed of and will be available later. The maid hesitates at "
					  "first, she then replies with a stubborn tone. \"Fine but don't come complaining to me when "
					  "you have no clothes to wear tomorrow\" .You hear the sound of the footsteps getting softer as "
					  "the maid walks further across the landing. You breathe a sigh of relief and then slowly open "
					  "the door. You quickly poke your head out and seeing that the coast is clear you sneak out of "
					  "the manor with the Alice's body held in your arms. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
	 
          ////////////////////////////////////////////ACT 2////////////////////////////////////////////////////////////////

		console_print("");
		console_print("It takes you the best part of two days as you slip away from the countryside towards the "
					  "nearest town. You are forced to trek across the long back roads and hidden trails avoiding to "
					  "be seen by other travellers. A million thoughts race through your mind as to what happened. "
					  "Did John really kill this girl? If so, then the fact that he deliberately planted the body in your "
					  "room was to remove himself as a suspect from the sinister deed. John Devlin will have some "
					  "serious questions to answer when you catch up with him but you know full well that he is "
					  "never an easy man to find. Despite this he is a well known man, you are fully aware that by "
					  "exploring the town's seedy underbelly will you be able to draw him out from hiding and "
					  "confront him face to face. You look down towards the body you hold in your arms, Alice's "
					  "skin looks noticeably pale and her clothes much like your own are filthy and are almost "
					  "beyond repair. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
	
crossroad: // start of act 2//
		console_print(" ");
		console_print("You look up to see the sun rise above the sea. You feel the cool, steady breeze of the ocean "
					  "embraces you with a further feeling of a bitter chill inside. You stop to rest, standing at a "
					  "crossroad. There is a sign post, one way leads to cliffs overlooking the shoreline and the other "
					  "leads to a small port town. ");
		
		console_print("");
console_print("Will you:");
	console_print("  1) Head to the cliffs?");
	console_print("  2) Head into town?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto cliffs;
	}
	else if (key == '2')
	{
		console_print("");
		goto gameover_2;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto crossroad;
	}

crossroad_2:	//If leave any town location, this is the centre point of every location in this act//
	
		console_print("");
		console_print("You stop to rest, standing at a crossroad. ");
		console_print("");
		console_print("Where do you want to go:");
		console_print("  1) Will you go to see Joseph?");
		console_print("  2) Head to the cliffs?");
		console_print("  3) Walk to the local church?");
		console_print("  4) Enter to the local tavern?");
		console_print("  5) Head back to Thornley Manor?");
		if (have_paper)
		{
			console_print("  6) Go to the brothel?");
			console_print("  7) Or head to the docks?");
		}
		console_print(">"); 
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto butchers_new1;
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You venture towards the cliffs overlooking the shoreline. The view is impressive as the "
					  "waves crash against the rocks, however you have little time to enjoy them. From where you "
					  "are standing you notice that there is a long dirt trail that leads to the beach. ");
		goto beach_short2;
	}
	else if (key == '3')
	{
		console_print("");
		goto church;
	}
	else if (key == '4')
	{
		console_print("");
		goto tavern;
	}
		else if (key == '5')
	{
		console_print("");
		goto gameover_4;
	}
		else if (key == '6' && have_paper)
		{
		goto brothel;
		}
		else if (key == '7' && have_paper)
		{
		goto docks;
		}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto crossroad_2;
	}
		
cliffs: // the cliffs overlooking the beach //
		console_print(" ");
		console_print("You venture towards the cliffs overlooking the shoreline. The view is impressive as the "
					  "morning sunlight hits the waters, however you have little time to enjoy them. From where "
					  "you are standing you notice that there is a long dirt trail that leads to the beach. ");
		console_print("");
		console_print("Will you:");
		console_print("  1) Follow the trail to the beach?");
		console_print("  2) Head back towards the town?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto beach;
	}
	else if (key == '2')
	{
		console_print("");
		goto gameover_2;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto cliffs;
	}

gameover_2: // If you head into town carrying alices dead body //
		console_print (" ");
		console_print ("You decide to head towards the town hoping to find some answers. You are greeted with "
					   "gasps of shock from the people as you enter the town holding the body of what clearly "
					   "appears to be a dead girl. News has already travelled fast as to the grizzly happenings at "
					   "Thornley Manor, it doesn't take much for the townspeople to realise that you must be the one "
					   "they are looking for from the clothes you are wearing. Their justice is severe as they beat "
					   "your battered body for hours until you can no longer hold consciousness. Your journey ends here "); 
					   
		{
		goto the_end;
		}

beach:  // the beach leading towards the cave //
		console_print (" ");
		console_print ("It takes another hour or so to reach the bottom of the trail to the beach. Fortunately for "
					   "yourself you don't see anyone about the coast. The wet sand is covered with rocks and old "
					   "bits of driftwood. You notice a cave further across the rock face, your body trembles as you "
					   "feel an overwhelming exhaustion, you can barely hold Alice's body any longer. Something "
					   "needs to be done. ");
		console_print("");
		console_print("Will you:");
		console_print("  1) Bury Alice in the sand?");
		console_print("  2) Venture on further and explore the cave?");
		console_print("  3) Or return to the cliffs?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto gameover_3;
	}
	else if (key == '2')
	{
		console_print("");
		goto cave;
	}
	else if (key == '3')
	{
		console_print("");
		goto cliffs;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto beach;
	}

beach_short1: // if return to the beach holding alice//
		console_print("");
		console_print("You walk back onto the beach holding Alice in your arms. From here there are only two ways to go. ");
		console_print("");
		console_print("Will you:");
		console_print("  1) Return to the cliff?");
		console_print("  2) Venture on further and explore the cave?");
		console_print("  3) Or bury Alice's body in the sand?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto cliffs;
	}
	else if (key == '2')
	{
		console_print("");
		goto cave;
	}
	else if (key == '3')
	{
		console_print("");
		goto gameover_3;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto beach_short1;
	}

beach_short2: //if return to the beach after burying alice in the cave//
		console_print("");
		console_print("You arrive at the beach. The wet sand is covered with rocks and old bits of driftwood. You "
                      "see the cave from before further across the rock face. ");
			console_print("");
		console_print("Will you:");
		console_print("  1) Head to the cave?");
		console_print("  2) Or head back to town?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto cave_2;
	}
	else if (key == '2')
	{
		console_print("");
		goto crossroad_2;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto beach_short2;
	}


gameover_3: //If you attempt to bury alice in the sand //
		console_print("");
		console_print("You spend what seems a lifetime as you try to scrape the wet sand away with the nearby "
					  "driftwood. Eventually it gives way and breaks, forcing you to bury your hands deep into the "
					  "hard wet sand to dig faster. Hours pass by as you finally dispose of Alice's body your hands "
					  "are bloody from the lack of tools, tired and hungry you head towards the nearby town. You "
					  "wander the streets for hours looking for somewhere to seek refuge. As you travel down the "
					  "main street you hear a cry from behind you. \"That's the one, I saw him down by the coast, "
					  "he's the one who buried that poor girl!\" You turn around to see a group of fishermen, "
					  "suddenly you realise in your exhausted state that it wouldn't take long for the morning tide to "
					  "wash away the sand revealing the body you had spent so long attempting to hide. In your "
					  "state you are unable to barely put up a fight or escape. The mob drags you to the authorities "
					  "who sentence you to death by hanging for your crimes. Your journey ends here. ");
		{
			goto the_end;
		}

cave: //if enter the cave for the first time//
		if (!have_candle)

	{
		console_print (""); 
		console_print ("You wander a little further down the beach to a nearby cave. The opening is smaller than you " 
					   "first thought, you peer inside but are unable to see anything you feel around with your hands, " 
					   "you notice that the cave doesn't appear to be very deep either. Finding nothing of use here "
					   "you decide to head back towards the beach. ");

		
		goto beach_short1;
		}
		
		if (have_candle)
			
		{
		
		console_print ("You wander a little further down the beach to a nearby cave. The opening is smaller than you "
					   "first thought, you peer inside but are unable to see anything so you decide to light one of the "
					   "candles in your possession. The cave lights up you notice that cave isn't very deep either, "
					   "however there is a small opening big enough for you to conceal Alice's body. ");
		}
		console_print("");
		console_print("Will you:");
		console_print("  1) Bury Alice in the cave?");
		console_print("  2) Or head back to the beach to find another solution to your dilemma?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("You spend a good deal of time covering Alice's body with rocks. She is now fairly well "
					  "concealed however you know full well that this will only hold as a temporary solution. For "
					  "now you can concentrate on what to do next you head into town to pay a visit to an old "
					  "friend. ");
		goto butchers;
	}
	else if (key == '2')
	{
		console_print("");
		goto beach_short1;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto cave;
	}

cave_2: // if return to the cave after burying alice //
		if (dispose_alice)
		{
		console_print("");
		console_print("You venture back to the cave. You are glad that Alice's body is no longer here as there was "
			          "always a chance that it would have been discovered. With little else to do here you return to "
					  "the beach. ");  
		goto beach_short2;
		}
		if (have_paper)
		{
		console_print("");
		console_print("You light another candle and walk into the cave. Peering in you can still see the re-arrangement "
			          "of newly placed rocks. You lift them one by one and un-veil the body of Alice. "
					  "You try hard to hold in your stomach as you can see that the sea water has taken its toll on the "
					  "poor girl's body. You un-wrap the newspapers you obtained and carefully wrap them around "
					  "her. You lift the body up from the ground and begin to leave the cave. Not wanting to draw "
					  "too much attention to yourself you head back to Joseph's house. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		goto butchers_new2;
		}
		
		if (!have_paper)
		{
		console_print("");
		console_print("You enter the cave and lift up some of the rocks to check if Alice's body has yet to be "
			          "discovered. You breathe a somewhat small sigh of relief as you feel the arm of a girl that only "
					  "several days ago was alive and well. Though you want to get her back to Joseph's as soon as "
					  "possible you know that it will be impossible to sneak the body into town unless you have a "
					  "way to cover up the body. With little choice you put the rocks back and leave the cave. ");
		goto beach_short2;
		}

butchers: //enter the butchers for the first time after burying alice //
		console_print("");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
		key = console_get_key();
		console_print("");
		console_print("After drifting into town you head to the home of your good friend Joseph. You stagger "
					  "towards his door and knock hard against it. Joseph opens the door and greets you, he notices "
					  "the state you're in. \"What on earth is the matter with you?\" He gestures for you to enter his "
					  "home, you sit on a small crooked stool beside an open fire. Joseph has been an old friend of "
					  "yours for years, he is the town's butcher who owns a small yet well stacked shop which does "
					  "him well enough for him to hold a stable living. He is wearing a grubby white shirt under a "
					  "messy and blood stained apron, despite the clothes he is a well kept man with a brown centre "
					  "parting and a long moustache. You know full well from experience that if there ever was a "
					  "problem that you could rely on Joe, you remain quiet for some time until you finally decide to "
					  "explain the situation in full to him."); 
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
 			  
		console_print("");
		console_print("Joe sits down and takes a long, silent draw from his clay "
					  "pipe, he looks mortified by what you have told him, he the looks up at you with a nervous yet "
					  "reassuring smile. \"This is very serious indeed, but I do not believe that you could be capable "
					  "of such a thing. All I can suggest for now is that you go get some rest\". He gestures you to "
					  "head upstairs to a small bedroom where he fetches you a set of new clothes to wear and a "
					  "washcloth. "); 
					  console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();

		console_print("");
		console_print ("You spend some time cleaning yourself and by the time you are done Joseph "
					  "arrives with a bowl of chicken broth and a small loaf of bread. \"Here, eat this\". You wolf "
					  "down the food in a ravaged manor being the first proper meal you've had in two days Joseph "
					  "also fetches you some fruit as well. \"Well until you have figured out what to do you can stay "
					  "here for as long as you want. However I suggest that at some point you will need to fetch the "
					  "girl if you do not wished for it be discovered. If you can conceal her body and bring it back "
					  "here discreetly then I might know someone who can help you\". You thank him for his "
					  "understanding and hospitality, Joseph just smiles back. \"I know fully well that you would do "
					  "the same thing for me my good friend\". "); 
					  console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		
butchers_short:	// start of choices after first visit to butchers, was included to shorten the i dont understand statement //		
		console_print("");
		console_print("He leaves the room to allow you to get some sleep, "
					  "though you are exhausted your sleep is restless, you wake up hours later and dress. There is "
					  "much to do before you can truly rest. ");
		console_print("");
console_print("Where will you go first:");
	console_print("  1) Back to the cliffs?");
	console_print("  2) To the church?");
	console_print("  3) To the local Tavern?");
	console_print("  4) Or back to Thornley Manor?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("You venture towards the cliffs overlooking the shoreline. The view is impressive as the "
					  "waves crash against the rocks, however you have little time to enjoy them. From where you "
					  "are standing you notice that there is a long dirt trail that leads to the beach.");
		goto beach_short2;
	}
	else if (key == '2')
	{
		console_print("");
		goto church;
	}
	else if (key == '3')
	{
		console_print("");
		goto tavern;
	}
	else if (key == '4')
	{
		console_print("");
		goto gameover_4;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto butchers_short;
	}
						
butchers_new1: // if you return to the butchers without alices body //
		
		if (dispose_alice)
		{
		console_print("");
		console_print("Considering everything that has happened recently you decide that its best not to return to "
			          "Joseph's and head back into town instead. ");
		goto crossroad_2;
		}
		if (!dispose_alice)
		{
		console_print("");
		console_print("You enter Joe's house. You call out for him but you get no reply, you look over to see a note "
				      "that was placed on the table. It informs you that if he is not in the house then he is busy "
					  "working in the butchers, you take the time to relax for a while and rest your feet, with nothing "
					  "else to do you decide to head back outside. ");
		goto crossroad_2;
		}
butchers_new2: // when you return to the butchers after using the newspapers to conceal alice//
		console_print("");
		console_print("By the time you return to town, you see that the sun is setting. You quicken your pace to get "
					  "to Joseph's house before it gets dark. As you dash through the streets towards his house it "
					  "starts to rain heavily. Your clothes are soaked through as you bang loudly on Joe's door. He "
					  "welcomes you into his home, and he fetches you a bottle of ale to drink. You dump the body "
					  "onto his floor, Joseph looks down at it with a nervous look. \"I guess it's safe to say what "
					  "that's supposed to be\". You give him a grim nod in acknowledgement as he carefully "
					  "unwraps some of the west news paper. \"Jesus Christ\" he proclaims as recoils at the sight of "
					  "the pale and bloated face of Alice. You ask him when he plans on contacting his friend so "
					  "that this messy business can be dealt with. Joe takes a draw from his clay pipe and sits in his "
					  "chair. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
					  
		console_print("");			  
		console_print("\"About five years ago I had a similar situation with one of my cousins. He was "
					  "involved in a messy affair when he was discovered in bed with another mans wife. Now it "
					  "was well known that this man was a notorious fellow, a really bully amongst the "
					  "townspeople, everyone hated the man but no-one ever had the bottle to do something about it. "
					  "That changed on the day when my cousin was caught trousers down with his Mrs. As you can "
					  "imagine the guy was furious he went wild and started attacking him, now you have to "
					  "understand that my cousin is very gentle creature he usually wouldn't hurt a fly, however. "
					  "When presented with a mad-man whose hell bent on demanding satisfaction for defiling the "
					  "sanctity of his marriage he had no choice but to fight back. "); 
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		console_print("");
		console_print("The scuffle ended badly as my "
					  "cousin somehow by pure luck managed to wrestle the man down however he slipped and fell "
					  "on him breaking his neck on the side of the bed. Well you could imagine how much this upset "
					  "him. After all, the boy was only defending himself yet he didn't want to hang for killing "
					  "someone who quite frankly no-one even cared about. Of course I couldn't sit by and let this "
					  "happen so this is when I suggested a way of disposing the body, I warn you now it wasn't "
					  "pretty but remember that I am a butcher after all\". He looks up at with a serious expression. ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();

butchers_new3:	//end of conversation with joe about disposing of alices body used to shorten i dont understand statement//				  
		console_print("");
		console_print("\"Give me the girl and I will make sure that there is no conceivable way that she will be found "
					  "again\". You almost double back in your chair as Joseph's message hits home. Could he "
					  "seriously be suggesting that the only option left is to dismember Alice's remains? You find it "
					  "hard to hold yourself together, surely there is another way. You plead with Joe to reconsider "
					  "his decision, \"I'm sorry, but there really is no other way, this town has been practically turned "
					  "upside down in the search for that girl, it won't be long before they eventually find her\". You "
					  "look down at the body of Alice. Though you had nothing to do with the poor girls murder, "
					  "can you really justify having her earthly remains treated like this. You start to feel sick to "
					  "your stomach, your head dizzy and faint, your lips dry you barely hold enough together to "
					  "look at Joe, he is only offering to help but how can he be so calm. He leans down and picks "
					  "up the body. \"Ok, let's get this over with\". ");
			
			console_print("");
			console_print("What will you do:");
			console_print("  1) Will you allow Joe to go ahead with his plan?");
			console_print("  2) Or plead with him to change his mind and reconsider?");
			console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("You sit back down in your chair and swig on your ale. You remain silent for the rest of the "
			          "evening as you sit and continue to drink until you pass out, you don't sleep very well. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		goto cutscene_2;
	}
	else if (key == '2')
	{
		console_print("");
		goto hesitation;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto butchers_new3;
	}
					

cutscene_2: // after giving alices body to joe //
		console_print("");
		console_print("You wake up the next morning feeling like death itself. Your mouth is dry, your head is "
			          "throbbing and your stomach is shaking. You reek of booze however this is the very least of "
					  "your worries. You continue to ponder on your decision last night and wondered if there was "
					  "any other way. Sometime later you hear footsteps coming from upstairs as Joe makes his way "
					  "down to the main room. \"How are you feeling?\" says Joe, you are barely able to speak but "
					  "you know that he can tell what you are thinking from your expression alone. \"I didn't mean "
					  "to seem crass. Your problem has been taken care of. So.... where will you go from here?\" "
					  "You explain to Joe that you still have un-finished business with Devilin and that you need to "
					  "confront him before you can move on with your life. You thank him for all of his kindness "
					  "and head towards the door. \"I hope you find what you're looking for\" says Joseph as you "
					  "close the door behind you and walk back onto the streets. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		dispose_alice = true;
		goto crossroad_2;

hesitation: // protesting against disposing alices body //
		console_print("");
		console_print("You stutter as you beg Joseph to reconsider. You try to convince him that with a little more "
			          "time you can find a safe way to dispose of Alice in a humane manner. But your pleas go "
					  "unanswered. \"I'm sorry but there has already been a great amount of effort to find this girl "
					  "already, it could only be a matter of time before they come knocking my door. What if "
					  "someone had seen you on the way here? I could lose my livelihood, I could lose my life and "
					  "they'd have every reason to hang me along with you. Unless you want to be caught this is the "
					  "only way that we can deal with this matter. I'm your friend, I'm trying to help you, but you "
					  "have to help me to\". ");
			console_print("");
			console_print("What will you do:");
			console_print("  1) Will you allow Joe to go ahead with his plan?");
			console_print("  2) Or will you attempt to stop him?");
			console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("You sit back down in your chair and swig on your ale. You remain silent for the rest of the "
			          "evening as you sit and continue to drink until you pass out, you don't sleep very well. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		goto cutscene_2;
	}
	else if (key == '2')
	{
		console_print("");
		goto last_chance;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto hesitation;
	}

last_chance: //further protesting//
		console_print("");
		console_print("Without thinking you attempt to grab Alice's body and drag it towards the door. Joseph starts "
			          "to lose his patience with you. \"What are you doing? Have you gone insane?\" he shouts. You "
					  "continue to reason further with Joe but he is getting more frustrated at your ramblings. "
					  "\"You've gotten me pretty deep in your shit, I'm not going to go down with you. For god's "
					  "sake you need to realise that this isn't your fault, you didn't do this to her. Now settle down, "
					  "you don't have to see this, I'll take care of everything\". ");
			console_print("");
			console_print("This is your last chance:");
			console_print("  1) Will you let him take Alice?");
			console_print("  2) Or will you stop him by any means necessary?");
			console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("You sit back down in your chair and swig on your ale. You remain silent for the rest of the "
			          "evening as you sit and continue to drink until you pass out, you don't sleep very well. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		goto cutscene_2;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_2;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto last_chance;
	}

fight_2:	//fight with joesph//
		console_print("");
		console_print("Joe starts to pull Alice's legs across the floor next door to the butchers. You run over to grab "
			          "the body from him. \"Look at what you're doing, look at yourself for god sake!\" You "
					  "consistently beg Joe to reconsider. \"What other choice do we have?\" screams Joseph. He lets "
					  "go of Alice as you hold it close to you and walks into the room next door. He leaves only "
					  "momentarily to return to his living room. \"I'm sorry my friend, but you have left me little "
					  "other choice\". Joseph walks to his front door and locks it with a key that he puts in his trouser "
					  "pocket. \"I've tried to do everything I could to help you, you can't expect me to go down with "
					  "you\". You are surprised as Joseph reveals a cleaver held in left hand. \"Forgive me\" Joseph's "
					  "words seemed filled with remorse as he lunges at you. ");

		console_print("");
		console_print("What will you do:");
		console_print("  1) Duck his first attack?");
		console_print("  2) Or attempt to move around him?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto fight_2A;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_2B;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto fight_2;
	}

fight_2A: // if duck //
		console_print("");
		console_print("You quickly drop your body weight and move to the floor. You feel the breeze pass by you as "
					  "the cleaver just barely misses you. Now is the chance to strike back. ");
		console_print("");
console_print("Will you:");
	console_print("  1) Attempt to snatch the cleaver from Joseph?");
	console_print("  2) Or hit him with a kidney punch?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto gameover_5;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_2C;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto fight_2A;
	}

fight_2B: // If move around //
		console_print("");
		console_print("You manoeuvre to the right of Joseph as you step in causing the cleaver to pass around your "
			          "body, you furiously slam him against the front door. ");
	console_print("Will you:");
	console_print("  1) Kick Joseph?");
	console_print("  2) Or attempt to snatch the cleaver from his hand?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto fight_2D;
	}
	else if (key == '2')
	{
		console_print("");
		goto gameover_5;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto fight_2B;
	}

fight_2C: // kidney punch//
		console_print("");
		console_print("You drive your fist into Joseph's side he leans over and slumps towards the ground dropping "
					  "the cleaver on the floor. ");
		console_print("Will you:");
		console_print("  1) Attempt one more time to reason with Joseph?");
		console_print("  2) Or will you pick up the cleaver?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto fight_2E;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_2finish;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto fight_2C;
	}

fight_2D: //kick//
		console_print("");
		console_print("You drive your foot into Joseph's stomach with enough force for him to double back against "
			          "the door. The force of the blow causes him to drop the cleaver. ");
		console_print("Will you:");
		console_print("  1) Attempt one more time to reason with Joseph?");
		console_print("  2) Or will you pick up the cleaver?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto fight_2E;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_2finish;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto fight_2D;
	}

fight_2E: //attemp to reason with joseph again//
		console_print("");
		console_print("You start to shout at Joe. You still can't believe that he would do such a thing feeling "
			          "betrayed you demand to let you leave with Alice's remains. \"Alright\" remarks Joseph. He "
					  "gets up from the floor and walks towards you. You feel the sharp stab of a small blade that "
					  "Joseph had concealed striking you in the arm. It looks like that the man who you once you "
					  "called your friend is now beyond reasoning. ");
		console_print("Will you:");
		console_print("  1) Attempt to pick up the cleaver from the floor?");
		console_print("  2) Or attack Joesph before he gets the drop on you?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto fight_2finish;
	}
	else if (key == '2')
	{
		console_print("");
		goto gameover_6;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto fight_2E;
	}

gameover_5: //if attempt to snatch the cleaver from joes hands//
		console_print("");
		console_print("You attempt to wrestle the cleaver from Joseph's hands. However his grip is strong, he "
			          "pushes you aside and you feel an incredible amount of pain as the cold metal of the cleaver "
					  "drives into your shoulder. You start to feel nauseous and faint as you spill blood on the floor. "
					  "\"I'm sorry, but you left me with no choice\" You shortly pass out afterwards. Your journey "
					  "ends here. ");
		goto the_end;

gameover_6: //if attempt to attack joe instead of trying to get the cleaver//
		console_print("");
		console_print("Though the cleaver would be useful, you are uncertain as to if you make your way past "
			          "Joseph. Instead you attempt to punch him. Your attacks are ineffective as with each attempt "
					  "you are slashed repeatedly by Joe's small yet sharp blade. It does not take long until you are "
					  "un-able to put up anymore of a fight. Joseph walks over to pick up the cleaver and swings it "
					  "at your face. You don't even feel the next blow. Your journey ends here. ");
		goto the_end;

fight_2finish: //if grab the cleaver and finish off joe//
		console_print("");
		console_print("With everything to lose, you dart across the floor and grab the cleaver, filled with blind rage "
					  "you relentlessly hack the cleaver into Joe's body until he no longer moves. You come to "
					  "moments later to realise what you have done, for what seems like a lifetime you are unable to "
					  "even move knowing what you have done. You then spend the entire night moving Alice's "
					  "remains to a nearby mortuary, you care little of the sloppy job you made to break into the "
					  "establishment, you just know that you need to fulfil the promise you made or otherwise "
					  "Joseph's death would mean for nothing. Afterwards you return to Joseph's house to move his "
					  "body into the meat locker and change your clothes. By the time you have done all of this you "
					  "can see the sun rise, exhausted and feeling sick you leave Joseph's house and lock the front "
					  "door before his customers come to visit. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
		key = console_get_key();

		dispose_alice = true;
		goto crossroad_2;

church: //church//
		if (have_coin && used_booth)
		{
		console_print("");
		console_print("You return to the church and sit at a pew. You begin to prey hoping that by some chance of "
				      "miracle that your innocence will be proven allowing for things to return to the way they once "
					  "were. Feeling that there is little else to do here you later decide to leave. ");
		goto crossroad_2;

		}
		
		if (have_coin && !used_booth)
		
		{
		console_print("");
		console_print("You return to the church and sit at a pew. You begin to prey hoping that by some chance of "
			          "miracle that your innocence will be proven allowing for things to return to the way they once "
					  "were. You look across the hall and notice that the confessional booth is empty. "); 
			console_print("");
		console_print("What will you do:");
		console_print("  1) Use the confession booth?");
		console_print("  2) Or leave the church?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto confession_booth;
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You leave the church and head back to town.");
		goto crossroad_2;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto church;
	}
		}
		
		if (!have_coin && used_booth)
		{
		console_print("");
		console_print("You return to the church and sit at a pew. You begin to prey hoping that by some chance of "
					  "miracle that your innocence will be proven allowing for things to return to the way they once "
					  "were. You look across the hall and notice in front of you sits a young and beautiful woman "
					  "deep in prayer, she also appears to be crying. ");
		console_print("");
		console_print("What will you do:");
		console_print("  1) Do you wish to talk to the lady?");
		console_print("  2) Or leave the church?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto talk_churchlady;
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You leave the church and head back to town.");
		goto crossroad_2;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto church;
	}
		}
		if (!have_coin && !used_booth)

		{
		console_print("");
		console_print("The local parish has several people sitting in solitary prayer. You decide to take a pew and "
					  "gather your thoughts for a way out of this predicament, you begin to prey hoping that by "
					  "some chance of miracle that your innocence will be proven allowing for things to return to "
					  "the way they once were. A priest is standing close to where you are he looks down at you "
					  "with a solemn expression. \"The almighty will listen to your prayers, all you must do is "
					  "believe in him\". Though the words should be comforting you find it very doubtful that your "
					  "prayers will be answered. You look across the hall and notice that the confessional booth is "
					  "empty. Also further in front of you sits a young and beautiful woman deep in prayer, she also "
					  "appears to be crying. ");
					  console_print("");
console_print("Will you:");
	console_print("  1) Talk to the lady?");
	console_print("  2) Use the confession booth?");
	console_print("  3) Or leave?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto talk_churchlady;
	}
	else if (key == '2')
	{
		console_print("");
		goto confession_booth;
	}
	else if (key == '3')
	{
		console_print("");
		console_print("You leave the church and head back to town. ");
		goto crossroad_2;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto church;
	}
		}

talk_churchlady: //talk to crying woman in church required in order to obtain coins //
		if (used_booth)
		{
		console_print("");
		console_print("Feeling rather sorry for the young lady you ask her if there is anything you can do to help. "
					  "She looks up at you and notices the melancholy look in your eye. She reaches down to her "
					  "purse and pulls out some coins and places them into your hand. \"I see you appear to be down "
					  "on your luck as well, it's ok I feel you need these more than I.\" You try to insist that the "
					  "charitable handout is not necessary however the young woman insists that you accept her "
					  "offer. You thank her kindly for her offer and she presently stands and leaves. ");
		have_coin = true;
		console_print("");
		console_print("You decide that to leave the church soon after. ");
			goto crossroad_2;
		}
		if (!used_booth)
		{
		console_print("");
		console_print("Feeling rather sorry for the young lady you ask her if there is anything you can do to help. "
					  "She looks up at you and notices the melancholy look in your eye. She reaches down to her "
					  "purse and pulls out some coins and places them into your hand. \"I see you appear to be down "
					  "on your luck as well, it's ok I feel you need these more than I.\" You try to insist that the "
					  "charitable handout is not necessary however the young woman insists that you accept her "
					  "offer. You thank her kindly for her offer and she presently stands and leaves. ");
		have_coin = true;
		console_print("");
		console_print("What will you do now:");
		console_print("  1) Will you use the confessional?");
		console_print("  2) Or decide to leave?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto confession_booth;
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You leave the church and head back to town.");
		goto crossroad_2;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto talk_churchlady;
	}
		}
confession_booth: //confessional booth//
		console_print("");
		console_print("Feeling the burden of keeping this terrible secret to yourself grows heavy on your heart. You " 
					  "look up towards the confessional booth, still noticing it is empty you walk towards the door "
					  "sit on the seat and close the door behind you. A little while later a small slat to your right "
					  "opens and through a small fabric mesh you hear a whispered voice from the other side \"You "
					  "wish to confess something my child?\" You pause to collect your thoughts, you wonder if you "
					  "should be here at all but the guilt of the situation is driving you crazy, it is true you didn't "
					  "murder the girl but you are responsible for setting up the kidnap with John Devlin in the first "
					  "place. \"Do you have a sin to confess which you must confess to the lord?\" ");
		console_print("");
        console_print("What will you do:");
		console_print("  1) Tell the priest about the kidnap plot and confess your crime?");
		console_print("  2) Or lie and pretend to confess about something else?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("You whisper to the priest everything that had transpired, at first you hear nothing from the "
					  "booth, the priest eventually whispers back. \"You have done the right thing my child, the lord "
					  "god will forgive you for your crimes and you shall seek salvation in the life eternal\". The slat "
					  "then closes. You sit in silence for some time, it feels better to have finally removed a little "
					  "part of your overbearing guilt feeling like you can continue you get up and leave the parish. "
					  "As you step outside several police officers are waiting for you they restrain you and take you "
					  "to prison to await for your sentence. It seems that the priest informed the authorities, without "
					  "any way to prove that you are not responsible for the murder, your journey ends here. ");
		goto the_end;
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You hesitate for a moment, you want to tell the priest but you are un-sure as to wither it wise "
					  "to do so. \"You have nothing to fear here\" whispers the priest from the other side of the mesh. "
					  "You come up with a story that you owe money however your details are sketchy and the "
					  "priest seems quite upset with your false confession. \"I suggest that you leave immediately\" "
					  "the priest's whisper turns into a harsh murmur. Embarrassed and feeling foolish you quickly "
					  "leave the confessional. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		used_booth = true; 
		goto church;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto confession_booth;
	}

tavern: //tavern//
		if (have_paper)
		{
		console_print("");
		console_print("You return to the tavern, you ask around the crowd if they have seen John Devlin, however "
					  "no-one seems to be willing to give you any information. Seeing there is little that you can do "
					  "you decide to leave. ");
		goto crossroad_2;
		}
		
		if (!have_paper)
		{
		console_print("");
		console_print("You walk into the local tavern, The Wheelwrights Arms. You are instantly hit with a wafting "
					  "smell of raw sweat and tobacco. The tavern is packed with drunken revellers, all the dregs of "
					  "society seem to be gathered in this collected place. Despite how repulsive you find this "
					  "cesspool you know that this is right kind of place in which to find John Devlin. You walk "
					  "over to the bar and call the barkeeper over. \"What do you want\" he says with a gruff "
					  "domineer. You explain that you are looking for John Devlin, he stops for a moment a looks at "
					  "you with an un-friendly stare. \"Haven't heard him\". You try to get more information out of "
					  "him but he seems unwilling to co-operate, before you can convince him otherwise he has "
					  "already walked away. You scan the area but you see no sign of Jim, however across the bar "
					  "from you notice a salutary looking woman giving you the eye.");
				console_print("");
				console_print("Will you:");
				console_print("  1) Decide to leave?");
				console_print("  2) Go talk to the woman?");
				console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("With no sign of John you decide to head back into town.");
		goto crossroad_2;
	}
	else if (key == '2')
	{
		console_print("");
		goto talk_woman;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto tavern;
	}
		}
talk_woman: //talk to woman at bar if have coins it will open two new locations and give you newspapers to use later//
		if (!have_coin)
		{
		console_print("");
		console_print("You walk over to the woman. She is wearing an old, petticoat, she gives you a toothy grin. "
			          "You can tell by the look of her that she has been around the block a few times. \"Oh buy me a "
					  "drink will yah?\" You rummage through your pockets but are un-able to find any money to "
					  "pay for one. The bartender notices your protestations and leans over in your direction. \"If you "
					  "don't have any money then I suggest you get out\". You take the bartenders advice and leave "
					  "the tavern immediately. ");
		goto crossroad_2;
		}
		
		if (have_coin)
		{
		goto talk_woman2;
		}	

talk_woman2:		// if have coins to buy the woman at the bar a drink //
		console_print("");
		console_print("You walk over to the woman. She is wearing an old, petticoat, she gives you a toothy grin. "
					  "You can tell by the look of her that she has been around the block a few times. \"Oh buy me a "
					  "drink will yah?\" You rummage through your pockets and produce the coins that you were "
					  "given earlier, you use a few of them to buy an ale for yourself and one for your new drinking "
					  "companion. \"Thanking you kindly\" says the woman, you spend some time introducing "
					  "yourself and ask her as to the whereabouts of John Devlin. "); 
		
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		
		console_print("");
		console_print("She ponders for a while. \"Why do "
					  "you have business with him?\" You concoct a convincing story that he owed you some money "
					  "from a card game, she gives you an unconvincing look and you wonder if the cover story has "
					  "worked at all, however she is more than happy to divulge the information with you. \"To be "
					  "honest I haven't seen him around for a long while, however I know that he regularly visits "
					  "Susan down on the estate, she's one of the working girls you see\". You note this information "
					  "down in your diary, she looks at you with a concerned look on her face. \"Look if you're in "
					  "some sort of trouble I know a ship owner who's down by the docks for a few days, why don't "
					  "you go and have a word with him?\" You thank the woman for her time and finish your drink "
					  "promptly, stand and leave. "); 
		
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();

		console_print("");
		console_print("On your way out of the door you see a young boy walks up "
					  "towards you, he looks up at you with an innocent expression on his face. \"Please, wont you "
					  "buy a buy a paper\" Not wanting to upset the boy you use the last of your money to purchase a "
					  "news paper, as he hands the paper over you notice that he has given several copies by "
					  "accident, as you about to bring this to the boys attention but are stopped by what you read on "
					  "the front page. You learn that Alice's kidnapping has been reported and that a ransom note "
					  "was left in Mr Farlington's room. Authorities and local volunteers are currently searching for "
					  "the girl and whichever party was responsible for her disappearance. Your heart starts to "
					  "pound, you can't believe that despite everything that has happened that John would still have "
					  "the audacity to send a ransom note hoping to receive money. You wish your search for John "
					  "would hasten so your questions could finally be answered. However a much more urgent "
					  "piece of business needs to be attended to, you know that it is only a matter of time before "
					  "Alice's body is discovered. ");
		have_paper = true; 
		console_print(" ");
	    console_print("Press any key to continue");
		console_print(" ");
			
			key = console_get_key();
			goto crossroad_2;

gameover_4:	//if you go back to thornley manor//
		console_print("");
		console_print("You spend half a day travelling back across the countryside to Thornley Manor hoping to  "
			          "either find some answers or possibly find the man who murdered Alice. It is night by the time "
					  "you arrive at the Manor grounds. As you venture through the gardens, you notice that the "
					  "grounds lanterns are un-lit due to strong winds tonight. The silence is almost creepy as there "
					  "seems to be no signs of life anywhere, some ten minutes pass as you stroll through the "
					  "gardens you notice a whimpering in the distance, as you move closer to investigate you see a "
					  "woman dressed in black wearing a vale over her face. "); 
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
		key = console_get_key();

		console_print ("");
		console_print ("As you are about to slip past you lose your footing and fall in front of the mysterious "
					  "woman. \"It's you! How do you have the nerve to come back here after what you did?\" The "
					  "voice however is most familiar to yourself, you look up at the woman who you now "
					  "recognise as Lady Farlington she looks at you with a most bitter look as she shouts. \"Why "
					  "have you come back? Are you here to steal me as well?\" You try your hardest to explain to "
					  "why this situation has happened, however you are unable to gather to strength to speak, "
					  "confused and frustrated you attempt to run away not long after you are grabbed by the "
					  "grounds men and taken to prison for your supposed crimes. Your journey ends here. ");
		goto the_end;

brothel: //if you goto the brothel//
		if (dispose_alice)
		{
		console_print("");
		console_print("With little care you storm down to the estate and kick in the door to Susan's home. You begin "
			          "to trash her house demanding that she gives you the location of John Devlin's last known "
					  "whereabouts. Like a demon possessed you don't stop until she is scared senseless begging for "
					  "you to stop. \"Please, he said he'd kill me if I let anyone know\". Tired and frustrated, against "
					  "your previous moral compass you start to threaten her yourself. \"All right, he has a place "
					  "down by the docks just please don't hurt me\". You take a step back to witness the destruction "
					  "you have caused around you, it's not like your yourself anymore all you can do is say sorry as "
					  "you dart out Susan's house towards the docks. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
		key = console_get_key();
		goto cutscene_3;
		}
		if (susan_talk)
		{
		console_print ("");
		console_print ("You return to the estate hoping that you might be able to get additional information from "
					   "Susan about John Devilin's whereabouts. You bang on the door continuously but much to "
					   "your disappointment no-one comes to answer. Feeling powerless to do anything you decide to "
					   "leave hoping to catch her about later. ");
		goto crossroad_2;
		}
		
		if (!susan_talk)
		{
		console_print ("");
		console_print ("You arrive at the estate, you ask some passersby as to the whereabouts of Susan. One "
					   "gentleman points towards a small and dilapidated house. You knock hard on the rotting "
					   "wooden door. Moments later the door opens a jar, you see a young woman with curly, auburn "
					   "hair, she is wearing a red dress made from worn out crushed velvet. You ask if this is the "
					   "residence of Susan, she looks up at you suddenly. \"I'm Susan, what can I do you for?\" You "
					   "explain to Susan that you urgently need to see John Devlin and ask if there is anything that "
					   "she might know as to his whereabouts. She looks up at you with an angry expression. \"How "
					   "dare you say that name in front of me, if you have anything to do with then I suggest you go "
					   "now\". You plead with her for her co-operation but to no avail as she slams the door in your "
					   "face. You decide that it is best to leave for now until you have found a way to persuade her "
					   "otherwise. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		susan_talk = true;
		goto crossroad_2;
		}

docks: //docks//
		if (captain_talk && fight_sailor)
		{
		console_print("");
		console_print("You head down to the town docks. You can see that a large ship is currently anchored at the "
				      "port and that there are great preparations to get the ship ready for its next voyage. However "
					  "being able to do little else here you decide to leave. ");
		goto crossroad_2;
		}
		
		if (!captain_talk && fight_sailor)
		{
		console_print("");
		console_print("You walk onto the docks. You can see that a large ship is currently anchored at the port and "
			          "that there are great preparations to get the ship ready for its next voyage. It is extremely busy "
					  "at the docks as you make your way across the jetty trying to push past the bustling crowd. "
					  "Beyond this you can see two men discussing something at length and referencing to a map, "
					  "you notice by that due to the clothes that he is wearing that the older gentleman out of the two "
					  "must be the captain. ");
console_print("");
console_print("Will you:");
	console_print("  1) Speak to the captain?");
	console_print("  2) Or leave the docks?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto talk_captain;
		
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You leave the docks and head back into town.");
		goto crossroad_2;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto docks;
	}
		}
		
		if (captain_talk && !fight_sailor)
		{
		console_print ("");
		console_print ("You head down to the town docks. You can see that a large ship is currently anchored at the "
					   "port and that there are great preparations to get the ship ready for its next voyage. It is "
					   "extremely busy at the docks as you make your way across the jetty trying to push past the "
					   "bustling crowd. Your attention is drawn to further beyond them as you see what appears to be "
					   "a small fishing vessel which at this very moment it currently appears to be-unmanned. ");
console_print("");
console_print("Do you:");
	console_print("  1) Wish to leave?");
	console_print("  2) Or investigate the small boat?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("You leave the docks and head back into town.");
		goto crossroad_2;
	}
	else if (key == '2')
	{
		console_print("");
		goto boat;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto talk_captain;
	}
		}
		
        if (!captain_talk && !fight_sailor)
		{
		console_print (" ");
		console_print ("You head down to the town docks. You can see that a large ship is currently anchored at the "
					   "port and that there are great preparations to get the ship ready for its next voyage. It is "
					   "extremely busy at the docks as you make your way across the jetty trying to push past the "
					   "bustling crowd. Beyond this you can see two men discussing something at length and "
					   "referencing to a map, you notice by that due to the clothes that he is wearing that the older "
					   "gentleman out of the two must be the captain. Also you attention is drawn to further beyond "
					   "them as you see what appears to be a small fishing vessel which at this very moment it "
					   "currently appears to be-unmanned. ");
		console_print("");
console_print("Do you wish to:");
	console_print("  1) Talk to the Captain?");
	console_print("  2) Investigate the small boat?");
	console_print("  3) Or leave?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
	goto talk_captain;
	}
	else if (key == '2')
	{
		console_print("");
	goto boat;
	}
	else if (key == '3')
	{
		console_print("");
		console_print("You leave the docks and head back into town.");
		goto crossroad_2;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto docks;
	}
		}
talk_captain: //talk to the ships captain//
		if (fight_sailor)
		{
		console_print("");
		console_print("You make your way towards the two gentlemen, you can see that they are using various "
					  "instruments to navigate a route for their voyage. You wait for a while however they seem to "
					  "be busy in conversation with each other, with little choice you make your presence known. "
					  "The older of the two men turns his attention from the map and looks up towards you. \"What "
					  "you be wanting?\" asks the captain, he is an older gentleman with grey hairy and bushy "
					  "as he talks to you he removes some tobacco from a small wooden box and fills his pipe. You "
					  "explain to him that you would like to come aboard their ship offering yourself as a worker "
					  "with no will to be paid, he gives you a look up and down and simply squints as he says \"No "
					  "can do\". You further beg the captain to allow you on board but he simply refuses to listen to "
					  "your pleas. Realising that there is little else you can do you bid him good day. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		captain_talk = true;
		goto crossroad_2;
		}
		if (!fight_sailor)
		{
		console_print("");
		console_print("You make your way towards the two gentlemen, you can see that they are using various "
					  "instruments to navigate a route for their voyage. You wait for a while however they seem to "
					  "be busy in conversation with each other, with little choice you make your presence known. "
					  "The older of the two men turns his attention from the map and looks up towards you. \"What "
					  "you be wanting?\" asks the captain, he is an older gentleman with grey hairy and bushy "
					  "as he talks to you he removes some tobacco from a small wooden box and fills his pipe. You "
					  "explain to him that you would like to come aboard their ship offering yourself as a worker "
					  "with no will to be paid, he gives you a look up and down and simply squints as he says \"No "
					  "can do\". You further beg the captain to allow you on board but he simply refuses to listen to "
					  "your pleas. Realising that there is little else you can do you bid him good day. ");
		captain_talk = true;
console_print("");
console_print("Do you:");
	console_print("  1) Wish to leave?");
	console_print("  2) Or investigate the small boat?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("You leave the docks and head back into town.");
		goto crossroad_2;
	}
	else if (key == '2')
	{
		console_print("");
		goto boat;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto talk_captain;
	}
		}
boat: //if investigate the small boat//
		console_print("");
		console_print("You continue to make your way past a group of sailors. You notice that they seem to be "
					  "relaxing before the ship sails. At the end of the jetty is the small boat that you spotted earlier, "
					  "also to your surprise there seems to be no-one around, as you are about to sneak on to the "
					  "vessel you notice that near the helm lies a large sailor on the floor. Luckily for you it appears "
					  "that the sailor is fast asleep. ");
console_print("");
console_print("Will you:");
	console_print("  1) Head back towards the docks?");
	console_print("  2) Or use the boat?");
	console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto docks;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_1;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto boat;
	}

fight_1: // fight with sailor //
		console_print("");
		console_print("You quickly untie the ropes that hold the boat to the jetty. As you are about to take the helm "
					  "the large sailor wakes up from his slumber, he notices what you are attempting to do and "
					  "without hesitation he launches himself at you. ");
		console_print("");
		console_print("Will you:");
		console_print("  1) Throw a left hook?");
		console_print("  2) Or wrestle him to the ground?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		console_print("You launch your fist into the sailors face. Unable to tell if it was luck or skill you are "
					  "surprised as you send him flying, knocking his head on the side of the boat. The sailor's body "
					  "slumps to the floor. Exhausted you look upon the body of the sailor. He is out cold but he is "
					  "still breathing. You notice that your ruckus has attracted a lot of attention as you can hear "
					  "cries from more sailors as they head across the jetty towards the boat. Not wanting to get "
					  "caught in anything further you decide that it's best to quickly leave while no-one can make "
					  "out your face. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		fight_sailor = true;
		goto docks;
	}
	else if (key == '2')
	{
		console_print("");
		console_print("You attempt to wrestle the sailor to the ground, however he is too heavy for you to budge. "
			          "You suddenly feel an overwhelming amount of pain as the sailor strikes you with a blow to "
					  "the face. You struggle to stand as the sailor hits you in the face again, you believe that he is "
					  "saying something to you, however you are un-able to hear what he is saying due to the "
					  "ringing in your ears. You eventually drift into un-consciousness. You awaken hours later  "
					  "feeling sore, you look around noticing that you are sitting on the docks however the boat has "
					  "since departed. ");  
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
		key = console_get_key();
		fight_sailor = true;
		goto docks;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto fight_1;
	}

	//////////////////////////////////////////////////////ACT 3//////////////////////////////////////////////////////////////

cutscene_3:	// on the way to john devlins hideout //
		console_print("");
		console_print("Almost at breaking point you storm through the streets with no subtlety towards the houses "
			          "by the docks. For the first time ever you don't even care if anyone notices you as bump past a "
					  "police constable, the time for sneaking around and being discreet was over, all that mattered "
					  "now was finally meeting face to face with the man who had ruined your life. You think back "
					  "over the events of the last few days, the things you've seen and the things you've had to do to "
					  "get here. Even if you manage to confront Deviln one doubt comes to mind, where will you go "
					  "from here? How can you go back to a normal life, you look into the waters beside the docks, "
					  "all you see looking back at you is the monster that you have become. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
		key = console_get_key();

hideout:
		console_print("");
		console_print("You walk across the jetty towards the last house on the street. The one with the waterwheel "
			          "that's where you were told to go. You wonder if the information that Susan gave you was the "
					  "truth. Could it be a trap? Has he moved on by now? Unlikely, he would have to wait around "
					  "for a few days if he was serious about obtaining the ransom money, since a note was left at "
					  "the manor you suspect that he will try to find a way to take the money and run during the "
					  "switch. After all you of all people should know by now that when John Devlin doesn't want "
					  "to be found, he makes sure of it. As you approach further you stop, the house has a small "
					  "staircase that leads up to the front door. Just shortly before the door lies a sleeping pit-bull "
					  "tied to a small post by a chain. ");
		console_print("");
		console_print("Will you:");
		console_print("  1) Look for a different way in?");
		console_print("  2) Or will you attempt to sneak past the dog?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto back_entrance;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_3;
	}
	else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto hideout;
	}

back_entrance:	
		console_print("");
		console_print("Rather than taking the risk of alerting the dog you make your way around the side of the "
			          "house hoping to find another way in. All you can see is a small open window that you may be "
					  "able to climb into but the wall looks smooth and may be hard to do so. ");
		console_print("");
		console_print("Will you:");
		console_print("  1) Attempt to climb in through the window?");
		console_print("  2) Or go back round the front and sneak past the dog?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto sneak_in;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_3;
	}
	else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto back_entrance;
	}

sneak_in:
		console_print("");
		console_print("It takes you a couple of attempts but you are finally able to climb in through the small "
					  "window of the house. You drop through the opening onto the wooden floor, the house is "
					  "dimly lit and there are clearly signs that someone has been living here. You freeze as the door "
					  "next to you slowly opens you hide yourself behind the door to see who enters the room. You "
					  "hold your breath as you observe the mysterious figure, suddenly the dog from outside begins "
					  "to bark. \"Will you keep it down you stupid dog\". The voice is instantly recognisable, even "
					  "despite the dim light you recognise the man's face to be that of John Devlin. Now is your "
					  "chance to strike before he spots you. ");
		console_print("");
		console_print("Will you:");
		console_print("  1) Hit him round the back of the head while you have the chance?");
		console_print("  2) Or search for an object to attack him with?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto fight_3A;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_3finish;
	}
	else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto sneak_in;
	}

fight_3:
		console_print("");
		console_print("You cautiously tiptoe your way up the stairs towards the front door. As you are about to open "
			          "the door you hear a loud growl beside you, the dog has woken up and lunges towards you. "
					  "You freeze as it leaps up to pounce upon you, but it stops in its tracks as it is held back by the "
					  "chain tied to his collar. With the noise you have made you have little choice but to slam the "
					  "door open. You step into the house, it is dimly lit and there are clearly signs that someone has "
					  "been living here. The door across the room opens \"Will you keep it down you stupid dog\". "
					  "The voice is instantly recognisable, you stand face to face with the man you have been "
					  "hunting this entire time, you stare into the face of John Devlin. No words were spoken, there "
					  "was no time for a reunion as Devlin gives you no opportunity to get the drop on him. He goes "
					  "in straight for the kill. ");
		console_print("");
		console_print("Will you:");
		console_print("  1) Jab him in the stomach?");
		console_print("  2) Attempt to trip him over?");
		console_print("  3) Or strike him in the face?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto fight_3B;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_3C;
	}
	else if (key == '3')
	{
		console_print("");
		goto fight_3D;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto fight_3;
	}

fight_3A:
		console_print("");
		console_print("You use the opportunity to attack John Devlin while he isn't looking you clasp both of your "
			          "hands together and drive them into the back of his head. He staggers then turns to face you "
					  "recognising your face he goes in straight for the kill. ");
		console_print("");
		console_print("Will you:");
		console_print("  1) Jab him in the stomach?");
		console_print("  2) Attempt to trip him over?");
		console_print("  3) Or strike him in the face?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto fight_3B;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_3C;
	}
	else if (key == '3')
	{
		console_print("");
		goto fight_3D;
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto fight_3A;
	}

fight_3B:
		console_print("");
		console_print("As Devlin darts towards you, you drive your fist into his stomach, he leans forward but is un- phased "
			          "phased as he smacks you in the face. You vision momentarily fades as you hear a ringing in "
					  "your ears. You need to react quickly or otherwise he will get another hit in. ");
		console_print("");
		console_print("Will you:");
		console_print("  1) Attempt to trip him over?");
		console_print("  2) Or will you strike him in the face?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto fight_3C;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_3D;
	}
	else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto fight_3B;
	}

fight_3C:	
		console_print("");
		console_print("You stick your foot out and push Devilin towards the floor. He topples over on his front, here "
					  "is your chance to strike. ");
		console_print("");
		console_print("Will you:");
		console_print("  1) Kick him in the head?");
		console_print("  2) Or attempt to find an object to hit him with?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto gameover_7;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_3finish2;
	}
	else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto fight_3C;
	}

fight_3D:
		console_print("");
		console_print("With tremendous force you hit Devlin full on in the face he doubles back not realising what "
			          "has just happened. You seem to have the upper hand. ");
		console_print("");
		console_print("Will you:");
		console_print("  1) Strike him again?");
		console_print("  2) Or trip him over onto the floor?");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		console_print("");
		goto gameover_8;
	}
	else if (key == '2')
	{
		console_print("");
		goto fight_3C;
	}
	else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto fight_3D;
	}

gameover_7:
		console_print("");
		console_print("You drive your foot into Devlin's face. You see him cough up blood onto the floor. You "
			          "attempt to kick him again however this time he anticipates your action and grabs your foot "
					  "pulling you to the ground. You sight goes momentarily fuzzy as you try to gather your senses, "
					  "by the time you have you are facing down the barrel of a pistol held in Devlin's hands. "
					  "Unable to do anything he pulls the trigger. Your journey ends here. ");
		goto the_end;

gameover_8:
		console_print("");
		console_print("Pressing the advantage you hit Devlin again the face, he stumbles against the wall hitting his "
			          "head against it. You stop to take your breath not noticing that John reaches for his pocket and "
					  "pulls out a pistol, he aims and pulls the trigger. You find it hard to breathe as you hit the floor "
					  "in agonising pain. Your journey ends here. ");
		goto the_end;

fight_3finish:
		console_print("");
		console_print("You quietly creep behind Devlin as he is dealing with the dog. Your eyes scan the room "
			          "searching for an object that would be of use, you then spot a poker sitting by the fireplace. "
					  "You carefully step over towards the fireplace and pick up the poker. With no hesitation you "
					  "drive the poker into Devlin's head. He crawls across the floor and without remorse you "
					  "repeatedly batter him to death. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		goto cutscene_4;

fight_3finish2:
		console_print("");
		console_print("You use the advantage you have in order to find something of use. Your eyes scan the room "
			          "until you notice a poker sitting by the fireplace. You grab the poker and with no hesitation "
					  "you drive the poker into Devlin's head. He crawls across the floor and without remorse you "
					  "repeatedly batter him to death. ");
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
			key = console_get_key();
		goto cutscene_4;

cutscene_4:		
		console_print("");
		console_print("Though the fight is over your hands are still shaking. Your heart continues to pound at an "
			          "alarming rate, as you realise the full extent of your actions. Thinking back over the past few "
					  "days your sole goal has been to track down Devlin and kill him for what he has done to your "
					  "life. However you feel no satisfaction from your revenge, nothing was said and nothing was "
					  "explained. You will never know why Alice died on that terrible night all that you know is that "
					  "in order to defeat the demon Devlin, you have become a demon yourself, you have become "
					  "what you despised all of this time, you have become a murderer. After everything you have "
					  "done there is no way you can go back to your old life, you slump on John's bed feeling cold "
					  "and empty. You stub your toe on a chest at the foot of the bed, you open it purely out of "
					  "curiosity and discover something magnificent. Inside the chest lies a staggering amount of "
					  "money and expensive jewellery. You take as much as you can feasibly carry and head across "
					  "the jetty to the shipping yard. "); 
		console_print(" ");
		console_print(" ");
	    console_print(" ");
	    console_print("Press any key to continue");
			
		key = console_get_key();
		console_print("");			  
		console_print("The ship that had arrived yesterday is still there, you walk over "
					  "the captain and ask for passage on his boat. \"I ain't got room for travellers........\" you cut his "
					  "sentence short as you discreetly pass a bag of money into his hand he gives you a wry smile "
					  "after inspecting your generous offer. The ship sailed later that evening, you're not entirely sure "
					  "sure how long the voyage will be, you don't even care where it's going. All that matters is "
					  "that you have been able to give yourself a second chance, a chance to repent for what you "
					  "have done. Your nightmare is over. ");
					  console_print("");
					  console_print("The End.");

		goto the_end;

the_end: // end screen includes retry function //
		console_print("");
		console_print("Would you like to retry?:");
		console_print("  1) Yes");
		console_print("  2) No");
		console_print(">");
	key = console_get_key();
	if (key == '1')
	{
		fetch_lady = false;
		straw = 5;
		alice_sad = false;
		have_candle = false;
		have_coin = false;
		used_booth = false;
		bought_drink = false;
		have_paper = false;
		susan_talk = false;
		captain_talk = false;
		fight_sailor = false;
		dispose_alice = false;
		console_print("");
		goto intro;
	}
	else if  (key == '2')
	{
		console_print("");
		quit(0);		
	}
		else
	{
		console_print("");
		console_print("I'm sorry I don't understand that answer ");
		console_print("");
		console_print("");
		goto the_end;
	}
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("Audio / video initialization failed: %s\n", SDL_GetError());
        quit(1);
    }

	if (!init_audio())
	{
		quit(1);
	}

	if (!init_graphics())
	{
		quit(1);
	}

	if (!init_console(game))
	{
		quit(1);
	}

	Mix_Music *music;
	load_music(music, "music.ogg");
	
	Mix_PlayMusic(music, -1);

	while (true)
	{
		process_events();
		console_update();
		console_draw();
    }

	return 0;
}
