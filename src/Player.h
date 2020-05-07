//Player.h

#ifndef PLAYER
#define PLAYER

#include "Pokemon.h"
#include "Move.h"
#include <string>
#include <vector>
#include <fstream>

class ScreenRenderer;

class Player
{
	std::string pname;
	std::vector<Pokemon> roster;
	int r, c;
	int level;

	public:
	Player(std::string, std::vector<Pokemon>);
	Player(std::ifstream&);
	std::string getPname();
	std::vector<Pokemon> getRoster();
	int getRow();
	int getCol();
	int getLevel();
	void setRow(int);
	void setCol(int);
	void setLevel(int);
	void setPname(std::string);
	void addtoRoster(Pokemon);
	void setRoster(std::vector<Pokemon>);
	bool hasAlivePokemon();
	void printDetails(ScreenRenderer S);
	void addXP(ScreenRenderer S, std::vector<int> pokxp);
	void healRoster();
	void writeToFile(std::ofstream&);
	void readFromFile(std::ifstream&);
};

#endif
