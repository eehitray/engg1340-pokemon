//Pokemon.h

#ifndef POKEMON
#define POKEMON

#include<vector>
#include<string>

struct Move;
class ScreenRenderer;

class Pokemon
{
	std::string name;
	char type;
	int hp;
	int maxhp;
	int level;
	std::vector<Move> moveset;

	public:
	Pokemon(std::string n, char t, int lvl, std::vector<std::string> stringset);
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
	void printDetails(ScreenRenderer S, bool printMoves);
};

#endif
