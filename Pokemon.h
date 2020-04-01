//Pokemon.h

#ifndef POKEMON
#define POKEMON

#include<vector>
#include<string>
#include "Move.h"

class Pokemon
{
	std::string name;
	char type;
	int hp;
	int level;
	std::vector<Move> moveset;

	public:
	Pokemon(std::string n, char t, int lvl, std::vector<Move> mvset);
	std::string getName();
	int getType();
	int getHP();
	int getLevel();
	std::vector<std::string> getMoveName();
	int getDamage(int pos);
	double getHit(int pos);
	void setName(std::string n);
	void setHP(int HP);
	void setLevel(int lvl);
	void setDamage();
};

#endif
