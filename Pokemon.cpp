//Pokemon.cpp

#include<string>
#include "Move.h"
#include "Pokemon.h"
#include<vector>

Pokemon::Pokemon(std::string n, char t, int lvl, std::vector<Move> mvset)
{	name = n;
	type = t;
	level = lvl;
	maxhp = lvl*10;
	hp = maxhp;
	moveset = mvset;
}

std::string Pokemon::getName()
{
	return name;		
}

char Pokemon::getType()
{
	return type;
}

int Pokemon::getMaxHP()
{
	return maxhp;
}

int Pokemon::getHP()
{
	return hp;
}

int Pokemon::getLevel()
{
	return level;
}

std::vector<Move> getFinalDamage(std::vector<Move> mvset, char t)
{
	if(type=='F')
	{
		if(t=='W')
			for(int i=0;i<3;i++)
				mvset[i].damage -=1;
		else if(t=='G')
			for(int i=0;i<3;i++)
				mvset[i].damage +=1;
	}
	else if(type=='W')
	{
		if(t=='F')
			for(int i=0;i<3;i++)
				mvset[i].damage +=1;
		else if(t=='G')
			for(int i=0;i<3;i++)
				mvset[i].damage -=1;
	}
	else
	{
		if(t=='F')
			for(int i=0;i<3;i++)
				mvset[i].damage -=1;
		else if(t=='W')
			for(int i=0;i<3;i++)
				mvset[i].damage +=1;
	}
	return mvset;
}

std::vector<Move> Pokemon::getMoveset()
{
	return moveset;
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
	maxhp = level*10;
	moveset[0].damage +=3;
	moveset[1].damage +=5;
	moveset[2].damage +=7;
}

