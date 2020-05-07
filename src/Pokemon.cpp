//Pokemon.cpp
#include<string>
#include "Move.h"
#include "Pokemon.h"
#include "ScreenRenderer.h"
#include<vector>
#include <fstream>

Pokemon::Pokemon(std::string n, char t, int lvl, std::vector<std::string> stringset)
{	name = n;
	type = t;
	currentxp = 0;
	moveset.push_back({stringset[0],3,1});
	moveset.push_back({stringset[1],5,0.7});
	moveset.push_back({stringset[2],7,0.5});
	setLevel(lvl);
	//add command for 3rd move here
}

Pokemon::Pokemon(std::ifstream& f) {
	readFromFile(f);
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

int Pokemon::getReqXP()
{
	return reqxp;
}

int Pokemon::getCurrentXP()
{
	return currentxp;
}

std::vector<Move> Pokemon::getFinalDamage(char t)
{
	std::vector<Move> mvset = moveset;
	if(type=='F')
	{
		if(t=='W')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage -= level;
		else if(t=='G')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage += level;
	}
	else if(type=='W')
	{
		if(t=='F')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage += level;
		else if(t=='G')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage -= level;
	}
	else
	{
		if(t=='F')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage -= level;
		else if(t=='W')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage += level;
	}
	return mvset;
}

std::vector<Move> Pokemon::getMoveset()
{
	return moveset;
}

int Pokemon::getNumMoves() {
	return numMoves;
}

void Pokemon::setName(std::string n)
{
	name = n;
}

void Pokemon::setHP(int HP)
{
	hp = HP;

	if (hp < 0) hp = 0;
	if (hp > maxhp) hp = maxhp;
}

void Pokemon::setLevel(int lvl)
{
	level = lvl;
	maxhp = level*10;
	hp = maxhp;
	reqxp = level*100;
	moveset[0].damage = level * 3;
	moveset[1].damage = level * 5;
	moveset[2].damage = level * 7;
	if (level >= 2) numMoves = 3;
	else numMoves = 2;
}

void Pokemon::addXP(ScreenRenderer S,int xp)
{
	while(xp>0)
	{
		if(currentxp+xp < reqxp)
		{
			currentxp += xp;
			S.printToScreen(name + " gained " + std::to_string(xp) +" XP!");
			xp = 0;
		}
		else
		{
			S.printToScreen(name + " gained " + std::to_string(reqxp - currentxp) +" XP!");
			xp = xp - reqxp + currentxp;
			currentxp=0;
			setLevel( getLevel() + 1); 
			S.printToScreen(name + " levelled up!");
		}
	}
}

void Pokemon::printDetails(ScreenRenderer S, bool printMoves)
{
	S.printToScreen(name);
	S.printToScreen("Level: " + std::to_string(level));
	S.printToScreen("Type: " + std::string(1, type));
	S.printToScreen("HP: " + std::to_string(hp));
	S.printToScreen("XP: " + std::to_string(currentxp));
	if (printMoves) {
		for(int i=0;i<numMoves;i++)
		{
			S.printToScreen(moveset[i].name + " - Damage: " + std::to_string(moveset[i].damage));
		}
	}

	S.printToScreen();
}

int Pokemon::opponentXP(int d, int oppHP)
{
	int xp;
	if(d>oppHP)
	{
		xp = (oppHP*10)/4;
		return xp;
	}
	else
	{
		xp = (d*10)/4;
		return xp;
	}
}

void Pokemon::writeToFile(std::ofstream& f) {
	f << name << std::endl
	  << type << std::endl
	  << hp << std::endl
	  << maxhp << std::endl
	  << reqxp << std::endl
	  << currentxp << std::endl
	  << level << std:: endl;

	int movesetSize = (int) moveset.size();

	f << movesetSize << std::endl;

	for (Move m : moveset) {
		f << m.name << std::endl
		  << m.damage << std::endl
		  << m.hit << std::endl;
	}	
}

void Pokemon::readFromFile(std::ifstream& f) {
	int tempHp;

	f >> name
	  >> type
	  >> tempHp
	  >> maxhp
	  >> reqxp
	  >> currentxp
	  >> level;

	int movesetSize;
	f >> movesetSize;

	for (int i = 0; i < movesetSize; i++) {
		Move m;
		f >> m.name >> m.damage >> m.hit;
		moveset.push_back(m);
	}

	setLevel(level);
	hp = tempHp;
}
