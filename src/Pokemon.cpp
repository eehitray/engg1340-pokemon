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
	moveset.push_back({stringset[1],5,0.5});
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
	hp = maxhp;
	moveset[0].damage += (level - 1) * 3;
	moveset[1].damage += (level - 1) * 5;
	//moveset[2].damage +=7;
}

void Pokemon::printDetails(ScreenRenderer S, bool printMoves)
{
	S.printToScreen(name);
	S.printToScreen("Level: " + std::to_string(level));
	S.printToScreen("Type: " + std::string(1, type));
	S.printToScreen("HP: " + std::to_string(hp));
	if (printMoves) {
		for(int i=0;i<moveset.size();i++)
		{
			S.printToScreen(moveset[i].name + " - Damage: " + std::to_string(moveset[i].damage));
		}
	}

	S.printToScreen();
}