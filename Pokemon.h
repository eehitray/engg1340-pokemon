//Pokemon.h

#ifndef POKEMON
#define POKEMON

#include<vector>
#include<string>
#include "Move.h"
#include "ScreenRenderer.h"

class Pokemon
{
	std::string name;
	char type;
	int hp;
	int maxhp;
	int level;
	std::vector<Move> moveset;

	public:
	Pokemon(std::string n, char t, int lvl, std::vector<string> stringset);
	std::string getName();
	char getType();
	int getMaxHP();
	int getHP();
	int getLevel();
	std::vector<Move> getFinalDamage(char t);
	std::vector<Move> getMoveset();
	void setName(std::string n);
	void setHP(int HP);
	void setLevel(int lvl);
	void printDetails(ScreenRenderer S);
};

#endif
