//Pokemon.h

#ifndef POKEMON
#define POKEMON

#include<vector>
#include<string>
#include <fstream>

struct Move;
class ScreenRenderer;

class Pokemon
{
	std::string name;
	char type;
	int hp;
	int maxhp;
	int reqxp;
	int currentxp;
	int level;
	int numMoves;
	std::vector<Move> moveset;

	public:
	Pokemon(std::string n, char t, int lvl, std::vector<std::string> stringset);
	Pokemon(std::ifstream&);
	std::string getName();
	char getType();
	int getMaxHP();
	int getHP();
	int getLevel();
	int getReqXP();
	int getCurrentXP();
	std::vector<Move> getFinalDamage(char t);
	std::vector<Move> getMoveset();
	int getNumMoves();
	void setName(std::string n);
	void setHP(int HP);
	void setLevel(int lvl);
	void addXP(ScreenRenderer S, int xp);
	void printDetails(ScreenRenderer S, bool printMoves);
	int opponentXP(int d, int oppHP);
	void writeToFile(std::ofstream&);
	void readFromFile(std::ifstream&);
};

#endif
