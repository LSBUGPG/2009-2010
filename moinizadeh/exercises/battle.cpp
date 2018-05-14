#include <cstdio>
#include <ctime>
#include <cstdlib> // rand
#include <algorithm> // std::min
#include <ctype.h> // tolower
#include <conio.h> // _kbhit and _getche

int roll(int faces)
{
	return (rand() % faces) + 1;
}

int get_modifier(int stat)
{
	return (stat / 2) - 5;
}

int player_constitution = 13;
int player_total_hit_points = 15 + player_constitution;
int player_hit_points = player_total_hit_points;
int player_strength = 16 + 2; // + human race bonus
int player_dexterity = 14;
int player_charisma = 12;
int player_level = 1;
int player_armour_bonus = 7; // scale mail
int player_shield_bonus = 2; // heavy shield
int player_defence_bonus = 0; // bonus when defending
int player_weapon_proficiency = 3;
int player_combat_advantage = 0;
int player_initiative_modifier =	get_modifier(player_dexterity) + 
									player_level / 2;
const char *player_name = "Fishmonger ";
const char *player_weapon = "Trout";
bool player_used_second_wind = false;
bool player_used_feint = false;
bool player_used_action_point = false;
int player_initiative;
int max_mp = 3;
int current_mp = max_mp;

int monster_total_hit_points = 29;
int monster_hit_points = monster_total_hit_points;
int monster_dexterity = 17;
int monster_wisdom_modifier = 1;
int monster_initiative_modifier = 5;
int monster_attack_modifier = 6;
int monster_armour_class = 17;
const char *monster_type = "Angry Granny ";
const char *monster_weapon = "Handbag";
int monster_initiative;

enum stage
{
	initiative,
	player_turn,
	monster_turn,
	player_wins,
	monster_wins,
	end
};

stage current = initiative;

void do_decide_initiative(void)
{
	player_initiative = roll(20) + player_initiative_modifier;
	monster_initiative = roll(20) + monster_initiative_modifier;
	bool tie = (player_initiative == monster_initiative);
	if (player_initiative > monster_initiative ||
		(tie && player_initiative_modifier > monster_initiative_modifier))
	{
		printf("%s is first to strike.\n", player_name);
		current = player_turn;
	}
	else
	{
		printf("The %s is first to strike.\n", monster_type);
		current = monster_turn;
	}
}

int player_armour_class(void)
{
	return	10 + 
			player_armour_bonus + 
			player_shield_bonus + 
			player_level / 2 + 
			player_defence_bonus;
}

void do_monster_attack(void)
{
	printf(
		"The %s makes a %s attack on %s.\n", 
		monster_type, 
		monster_weapon, 
		player_name);

	int dice = roll(20);
	bool critical = (dice == 20);
	int hit = dice + monster_attack_modifier;
	if (critical || hit >= player_armour_class())
	{
		int damage;
		if (critical)
		{
			printf("The %s made a critical hit!\n", monster_type);
			damage = 10;
		}
		else
		{
			damage = roll(8) + 2;
		}
		printf(
			"The %s hit %s for %d hit points of damage.\n",
			monster_type,
			player_name,
			damage);

        player_hit_points -= damage;
	}
	else
	{
	    printf("The %s missed.\n", monster_type);
	}

	if (player_hit_points <= 0)
	{
		current = monster_wins;
	}
	else
	{
		if (player_hit_points < player_total_hit_points / 2)
		{
			printf("%s is bloodied.\n", player_name);
		}
		current = player_turn;
	}
}

void do_player_defend(void)
{
	printf("%s defends.\n", player_name);
    player_defence_bonus = 2;
}

void do_player_melee(void)
{
	printf("%s makes a %s attack on the %s.\n", player_name, player_weapon, monster_type);

	int dice = roll(20);
	bool critical = (dice == 20);
	int hit =   dice +
                get_modifier(player_strength) +
                player_weapon_proficiency +
                player_level / 2 +
                player_combat_advantage;

	if (critical || hit >= monster_armour_class)
	{
		int damage;
		if (critical)
		{
			printf("%s made a critical hit!\n", player_name);
			damage = 8 + get_modifier(player_strength);
		}
		else
		{
			damage = roll(8) + get_modifier(player_strength);
		}
		printf(
			"%s hit the %s for %d hit points of damage.\n",
			player_name,
			monster_type,
			damage);

		monster_hit_points -= damage;
	}
	else
	{
	    printf("%s missed.\n", player_name);
	}
}

void do_player_feint(void)
{
    int bluff = roll(20) + get_modifier(player_charisma) + player_level / 2;
    if (bluff >= 10 + monster_wisdom_modifier)
    {
        player_combat_advantage = 2;
        printf(
			"%s fakes out the %s and gains an advantage.\n",
			player_name,
			monster_type);
    }
    else
    {
        printf(
			"%s tries to fake out the %s but failed.\n",
			player_name,
			monster_type);
    }
    player_used_feint = true;
}

void do_player_second_wind(void)
{
	int surge = player_total_hit_points / 4;
	player_hit_points = std::min(player_total_hit_points, player_hit_points + surge);
	player_used_second_wind = true;
	printf("%s feels a fresh surge of energy.\n", player_name);
	do_player_defend();
}

void do_player_shazam(void)
{
	int chance = roll(20);
	player_combat_advantage = 3;
		
	printf( "%s gets an increaced attack.\n",player_name);	
			
			
			if (chance >= 10)
		{
			player_hit_points = std::min(player_total_hit_points, player_hit_points + 10);
			printf( "%s feels rejuvinated.\n", player_name);
		}
}




void do_player_turn(void)
{
	bool action_point = false;
	bool cancel_combat_advantage = (player_combat_advantage > 0);
	bool done = false;
	do
	{
	    player_defence_bonus = 0;
		printf("What should %s do this round?\n", player_name);
		printf("\tM - Melee attack\n");
		printf("\tD - Defend\n");
		if (!player_used_feint)
		{
		    printf("\tF - Feint (once per combat)\n");
		}
		if (!player_used_second_wind)
		{
			printf("\tS - Second Wind (once per combat)\n");
		}
		if (!player_used_action_point)
		{
			printf("\tA - Action Point (once per combat)\n");
		}
		if (current_mp >= 3)
		{
			printf("\tW - Shazam (Every 3rd turn)\n");
		}
		printf(">");

		while (!_kbhit());

		int key = tolower(_getche());
		printf("\n");

		if (key == 'm')
		{
			do_player_melee();
			done = true;
		}
		else if (key == 'd')
		{
			do_player_defend();
			done = true;
		}
		else if (!player_used_feint && key == 'f')
		{
			do_player_feint();
			done = true;
		}
		else if (!player_used_second_wind && key == 's')
		{
			do_player_second_wind();
			done = true;
		}
		else if (!player_used_action_point && key == 'a')
		{
			action_point = true;
			player_used_action_point = true;
		}
		else if (current_mp >= 3 && key == 'w')
		{
			do_player_shazam();
			current_mp = 0;
			done = true;
		}
		else
		{
			printf("Option unavailable.\n");
		}

		if (done && action_point)
		{
			done = false;
			action_point = false;
			printf("Now choose a second action.\n");
		}
	}
	while (!done);

	current_mp = std::min(max_mp, current_mp + 1);


	if (cancel_combat_advantage)
	{
		player_combat_advantage = 0;
	}

	if (monster_hit_points <= 0)
	{
		current = player_wins;
	}
	else
	{
		if (monster_hit_points < monster_total_hit_points / 2)
		{
			printf("The %s is bloodied.\n", monster_type);
		}
		current = monster_turn;
	}
}

int main(int argc, char *argv[])
{
	srand(int(time(0)));

	do
	{
		switch (current)
		{
		case initiative:
			do_decide_initiative();
			break;

		case player_turn:
			do_player_turn();
			break;

		case monster_turn:
			do_monster_attack();
			break;

		case player_wins:
			printf("%s defeats the %s.\n", player_name, monster_type);
			current = end;
			break;

		case monster_wins:
			printf("The %s has defeated %s.\n", monster_type, player_name);
			current = end;
			break;

		case end:
			break;
		}
	}
	while (current != end);

	return 0;
}
