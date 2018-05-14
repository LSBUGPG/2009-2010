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
const char *player_name = "Onett";
const char *player_weapon = "Zeta Slugger";
bool player_used_second_energy = false;
bool player_used_counter_attack = false;
bool player_used_action_point = false;
int player_initiative;

int mecha_total_hit_points = 29;
int mecha_hit_points = mecha_total_hit_points;
int mecha_dexterity = 17;
int mecha_wisdom_modifier = 1;
int mecha_initiative_modifier = 5;
int mecha_attack_modifier = 6;
int mecha_armour_class = 17;
const char *mecha_type = "Seven Headed Altron";
const char *mecha_weapon = "shots";
int mecha_initiative;

enum stage
{
	initiative,
	player_turn,
	mecha_turn,
	player_wins,
	mecha_wins,
	end
};

stage current = initiative;

void do_decide_initiative(void)
{
	player_initiative = roll(20) + player_initiative_modifier;
	mecha_initiative = roll(20) + mecha_initiative_modifier;
	bool tie = (player_initiative == mecha_initiative);
	if (player_initiative > mecha_initiative ||
		(tie && player_initiative_modifier > mecha_initiative_modifier))
	{
		printf("%s is first to strike.\n", player_name);
		current = player_turn;
	}
	else
	{
		printf("The %s is first to strike.\n", mecha_type);
		current = mecha_turn;
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

void do_mecha_attack(void)
{
	printf(
		"The %s makes a %s attack on %s.\n", 
		mecha_type, 
		mecha_weapon, 
		player_name);

	int dice = roll(20);
	bool critical = (dice == 20);
	int hit = dice + mecha_attack_modifier;
	if (critical || hit >= player_armour_class())
	{
		int damage;
		if (critical)
		{
			printf("The %s made a critical hit!\n", mecha_type);
			damage = 10;
		}
		else
		{
			damage = roll(8) + 2;
		}
		printf(
			"The %s hit %s for %d hit points of damage.\n",
			mecha_type,
			player_name,
			damage);

        player_hit_points -= damage;
	}
	else
	{
	    printf("The %s missed.\n", mecha_type);
	}

	if (player_hit_points <= 0)
	{
		current = mecha_wins;
	}
	else
	{
		if (player_hit_points < player_total_hit_points / 2)
		{
			printf("%s is attacked and hurt.\n", player_name);
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
	printf("%s makes a %s attack on the %s.\n", player_name, player_weapon, mecha_type);

	int dice = roll(20);
	bool critical = (dice == 20);
	int hit =   dice +
                get_modifier(player_strength) +
                player_weapon_proficiency +
                player_level / 2 +
                player_combat_advantage;

	if (critical || hit >= mecha_armour_class)
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
			mecha_type,
			damage);

		mecha_hit_points -= damage;
	}
	else
	{
	    printf("%s missed.\n", player_name);
	}
}

void do_player_counter_attack(void)
{
    int bluff = roll(20) + get_modifier(player_charisma) + player_level / 2;
    if (bluff >= 10 + mecha_wisdom_modifier)
    {
        player_combat_advantage = 2;
        printf(
			"%s fakes out the %s and gains an advantage.\n",
			player_name,
			mecha_type);
    }
    else
    {
        printf(
			"%s tries to fake out the attack %s but failed.\n",
			player_name,
			mecha_type);
    }
    player_used_counter_attack = true;
}

void do_player_second_energy(void)
{
	int surge = player_total_hit_points / 4;
	player_hit_points = std::min(player_total_hit_points, player_hit_points + surge);
	player_used_second_energy = true;
	printf("%s feels a fresh surge of Special Energy.\n", player_name);
	do_player_defend();
}

void do_player_turn(void)
{
	bool action_point = false;
	bool cancel_combat_advantage = (player_combat_advantage > 0);
	bool done = false;
	do
	{
	    player_defence_bonus = 0;
		printf("What should %s do in this battle?\n", player_name);
		printf("\tD - Do a Variable SouthBound attack\n");
		printf("\tB - Block The Attack\n");
		if (!player_used_counter_attack)
		{
		    printf("\tC - Counter Attack (can only be used once)\n");
		}
		if (!player_used_second_energy)
		{
			printf("\tS - Regain Second Energy (can only be used once)\n");
		}
		if (!player_used_action_point)
		{
			printf("\tA - Action Point (can only be used once)\n");
		}
		printf(">");

		while (!_kbhit());

		int key = tolower(_getche());
		printf("\n");

		if (key == 'd')
		{
			do_player_melee();
			done = true;
		}
		else if (key == 'b')
		{
			do_player_defend();
			done = true;
		}
		else if (!player_used_counter_attack && key == 'c')
		{
			do_player_counter_attack();
			done = true;
		}
		else if (!player_used_second_energy && key == 's')
		{
			do_player_second_energy();
			done = true;
		}
		else if (!player_used_action_point && key == 'a')
		{
			action_point = true;
			player_used_action_point = true;
		}
		else
		{
			printf("Option unavailable.\n");
		}

		if (done && action_point)
		{
			done = false;
			action_point = false;
			printf("Now choose a second action and think fast.\n");
		}
	}
	while (!done);

	if (cancel_combat_advantage)
	{
		player_combat_advantage = 0;
	}

	if (mecha_hit_points <= 0)
	{
		current = player_wins;
	}
	else
	{
		if (mecha_hit_points < mecha_total_hit_points / 2)
		{
			printf("The %s is losing power.\n", mecha_type);
		}
		current = mecha_turn;
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

		case mecha_turn:
			do_mecha_attack();
			break;

		case player_wins:
			printf("%s defeats the %s.\n", player_name, mecha_type);
			current = end;
			break;

		case mecha_wins:
			printf("The %s has defeated %s.\n", mecha_type, player_name);
			current = end;
			break;

		case end:
			break;
		}
	}
	while (current != end);

	return 0;
}
