//Pokemon.cpp

#include<string>
#include "Move.h"
#include "Pokemon.h"
#include<vector>

Pokemon::Pokemon(std::string n, char t, int lvl, std::vector<Move> mvset)
{
	name = n;
	type = t;
	level = lvl;
	hp = maxhp(lvl) //the function we create to calculate max hp per level
	moveset = mvset;
}

std::string Pokemon::getName()
{
	return name;		
}

int Pokemon::getType()
{
	return type;
}

int Pokemon::getHP()
{
	return hp;
}

int Pokemon::getLevel()
{
	return level;
}

std::vector<std::string> Pokemon::getMoveName()
{
	std::vector<std::string> mvnames;
	for(int i=0;i<3;i++)
		mvname.push_back(moveset[i].name);
	return mvnames;
}

int Pokemon::getDamage(int pos)
{
	return moveset[pos].damage;
}

double Pokemon::getHit(int pos)
{
	return moveset[pos].hit;
}

void Pokemon::setName(std::string n)
{
	name = n;
}

void Pokemon::setHP(int HP)
{
	hp = HP;
}

void Pokemon::setLevel(int lvl)
{
	level = lvl;
}

void Pokemon::setDamage()
{
	moveset[0].damage = tier1(level);
	moveset[1].damage = tier2(level);
	moveset[2].damage = tier3(level);
}
