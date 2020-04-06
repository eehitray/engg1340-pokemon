//Pokemon.cpp

#include<string>
#include "Move.h"
#include "Pokemon.h"
#include "ScreenRenderer.h"
#include<vector>

Pokemon::Pokemon(std::string n, char t, int lvl, std::vector<std::string> stringset)
{	name = n;
	type = t;
	level = lvl;
	maxhp = lvl*10;
	hp = maxhp;
	moveset.push_back({stringset[0],3,1});
	moveset.push_back({stringset[1],5,0.8});
	//add command for 3rd move here
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

std::vector<Move> Pokemon::getFinalDamage(char t)
{
	std::vector<Move> mvset = moveset;
	if(type=='F')
	{
		if(t=='W')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage -=1;
		else if(t=='G')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage +=1;
	}
	else if(type=='W')
	{
		if(t=='F')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage +=1;
		else if(t=='G')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage -=1;
	}
	else
	{
		if(t=='F')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage -=1;
		else if(t=='W')
			for(int i=0;i<mvset.size();i++)
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

	if (hp < 0) hp = 0;
}

void Pokemon::setLevel(int lvl)
{
	level = lvl;
	maxhp = level*10;
	moveset[0].damage +=3;
	moveset[1].damage +=5;
	moveset[2].damage +=7;
}

void Pokemon::printDetails(ScreenRenderer S)
{
	S.printToScreen(name);
	for(int i=0;i<moveset.size();i++)
	{
		S.printToScreen(moveset[i].name + " " + std::to_string(moveset[i].damage));
	}
}
