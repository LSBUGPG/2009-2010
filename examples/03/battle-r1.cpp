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

struct creature
{
	int strength;
	int constitution;
	int dexterity;
	int wisdom;
	int charisma;
	int total_hit_points;
	int hit_points;
	int level;
	int armour_bonus;
	int shield_bonus;
	int defence_bonus;
	int weapon_proficiency;
	int combat_advantage;
	int initiative_modifier;
	const char *name;
	const char *type;
	const char *weapon;
	bool used_second_wind;
	bool used_feint;
	bool used_action_point;
	int initiative;
};

creature player;
creature goblin;

void create_player(void)
{
	player.strength = 16 + 2; // + human race bonus
	player.constitution = 13;
	player.dexterity = 14;
	player.wisdom = 11;
	player.charisma = 12;
	player.total_hit_points = 15 + player.constitution;
	player.hit_points = player.total_hit_points;
	player.level = 1;
	player.armour_bonus = 7; // scale mail
	player.shield_bonus = 2; // heavy shield
	player.defence_bonus = 0; // bonus when defending
	player.weapon_proficiency = 3;
	player.combat_advantage = 0;
	player.initiative_modifier = get_modifier(player.dexterity) + player.level / 2;
	player.name = "Erik";
	player.type = "Human Fighter";
	player.weapon = "longsword";
	player.used_second_wind = false;
	player.used_feint = false;
	player.used_action_point = false;
	player.initiative = 0;
}

void create_goblin(void)
{
	goblin.strength = 14;
	goblin.constitution = 13;
	goblin.dexterity = 17;
	goblin.wisdom = 12;
	goblin.charisma = 8;
	goblin.total_hit_points = 29;
	goblin.hit_points = goblin.total_hit_points;
	goblin.level = 1;
	goblin.armour_bonus = 2; // leather armour
	goblin.shield_bonus = 0; // no shield
	goblin.defence_bonus = 0; // bonus when defending
	goblin.weapon_proficiency = 2;
	goblin.combat_advantage = 0;
	goblin.initiative_modifier = get_modifier(goblin.dexterity) + 2; // special +2
	goblin.name = "Splug";
	goblin.type = "Goblin Warrior";
	goblin.weapon = "spear";
	goblin.used_second_wind = false;
	goblin.used_feint = false;
	goblin.used_action_point = false;
	goblin.initiative = 0;
}

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
	player.initiative = roll(20) + player.initiative_modifier;
	goblin.initiative = roll(20) + goblin.initiative_modifier;
	bool tie = (player.initiative == goblin.initiative);
	if (player.initiative > goblin.initiative ||
		(tie && player.initiative_modifier > goblin.initiative_modifier))
	{
		printf("%s is first to strike.\n", player.name);
		current = player_turn;
	}
	else
	{
		printf("The %s is first to strike.\n", goblin.type);
		current = monster_turn;
	}
}

int player_armour_class(void)
{
	return	10 + 
			player.armour_bonus + 
			player.shield_bonus + 
			player.level / 2 + 
			player.defence_bonus;
}

int goblin_armour_class(void)
{
	return 10 +
		   goblin.armour_bonus +
		   goblin.shield_bonus +
		   get_modifier(goblin.dexterity) + // dexterity bonus for leather armour
		   goblin.level / 2 +
		   goblin.defence_bonus + 
		   2; // unknown extra goblin bonus
}

void do_monster_attack(void)
{
	printf(
		"The %s makes a %s attack on %s.\n", 
		goblin.type, 
		goblin.weapon, 
		player.name);

	int dice = roll(20);
	bool critical = (dice == 20);
	int hit = dice + 
              get_modifier(goblin.strength) +
              goblin.weapon_proficiency +
              goblin.level / 2 +
              goblin.combat_advantage +
			  2; // extra goblin modifier

	if (critical || hit >= player_armour_class())
	{
		int damage;
		if (critical)
		{
			printf("The %s made a critical hit!\n", goblin.type);
			damage = 10;
		}
		else
		{
			damage = roll(8) + 2;
		}
		printf(
			"The %s hit %s for %d hit points of damage.\n",
			goblin.type,
			player.name,
			damage);

        player.hit_points -= damage;
	}
	else
	{
	    printf("The %s missed.\n", goblin.type);
	}

	if (player.hit_points <= 0)
	{
		current = monster_wins;
	}
	else
	{
		if (player.hit_points < player.total_hit_points / 2)
		{
			printf("%s is bloodied.\n", player.name);
		}
		current = player_turn;
	}
}

void do_player_defend(void)
{
	printf("%s defends.\n", player.name);
    player.defence_bonus = 2;
}

void do_player_melee(void)
{
	printf("%s makes a %s attack on the %s.\n", player.name, player.weapon, goblin.type);

	int dice = roll(20);
	bool critical = (dice == 20);
	int hit =   dice +
                get_modifier(player.strength) +
                player.weapon_proficiency +
                player.level / 2 +
                player.combat_advantage;

	if (critical || hit >= goblin_armour_class())
	{
		int damage;
		if (critical)
		{
			printf("%s made a critical hit!\n", player.name);
			damage = 8 + get_modifier(player.strength);
		}
		else
		{
			damage = roll(8) + get_modifier(player.strength);
		}
		printf(
			"%s hit the %s for %d hit points of damage.\n",
			player.name,
			goblin.type,
			damage);

		goblin.hit_points -= damage;
	}
	else
	{
	    printf("%s missed.\n", player.name);
	}
}

void do_player_feint(void)
{
    int bluff = roll(20) + get_modifier(player.charisma) + player.level / 2;
    if (bluff >= 10 + get_modifier(goblin.wisdom))
    {
        player.combat_advantage = 2;
        printf(
			"%s fakes out the %s and gains an advantage.\n",
			player.name,
			goblin.type);
    }
    else
    {
        printf(
			"%s tries to fake out the %s but failed.\n",
			player.name,
			goblin.type);
    }
    player.used_feint = true;
}

void do_player_second_wind(void)
{
	int surge = player.total_hit_points / 4;
	player.hit_points = std::min(player.total_hit_points, player.hit_points + surge);
	player.used_second_wind = true;
	printf("%s feels a fresh surge of energy.\n", player.name);
	do_player_defend();
}

void do_player_turn(void)
{
	bool action_point = false;
	bool cancel_combat_advantage = (player.combat_advantage > 0);
	bool done = false;
	do
	{
	    player.defence_bonus = 0;
		printf("What should %s do this round?\n", player.name);
		printf("\tM - Melee attack\n");
		printf("\tD - Defend\n");
		if (!player.used_feint)
		{
		    printf("\tF - Feint (once per combat)\n");
		}
		if (!player.used_second_wind)
		{
			printf("\tS - Second Wind (once per combat)\n");
		}
		if (!player.used_action_point)
		{
			printf("\tA - Action Point (once per combat)\n");
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
		else if (!player.used_feint && key == 'f')
		{
			do_player_feint();
			done = true;
		}
		else if (!player.used_second_wind && key == 's')
		{
			do_player_second_wind();
			done = true;
		}
		else if (!player.used_action_point && key == 'a')
		{
			action_point = true;
			player.used_action_point = true;
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

	if (cancel_combat_advantage)
	{
		player.combat_advantage = 0;
	}

	if (goblin.hit_points <= 0)
	{
		current = player_wins;
	}
	else
	{
		if (goblin.hit_points < goblin.total_hit_points / 2)
		{
			printf("The %s is bloodied.\n", goblin.type);
		}
		current = monster_turn;
	}
}

int main(int argc, char *argv[])
{
	create_player();
	create_goblin();

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
			printf("%s defeats the %s.\n", player.name, goblin.type);
			current = end;
			break;

		case monster_wins:
			printf("The %s has defeated %s.\n", goblin.type, player.name);
			current = end;
			break;

		case end:
			break;
		}
	}
	while (current != end);

	return 0;
}
