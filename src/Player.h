//Player.h

#ifndef PLAYER
#define PLAYER

#include "Pokemon.h"
#include "Move.h"
#include<string>
#include<vector>

class ScreenRenderer;

class Player
{
	std::string pname;
	std::vector<Pokemon> roster;
	public:
	Player(std::string n, std::vector<Pokemon> pok);
	std::string getPname();
	std::vector<Pokemon> getRoster();
	void setPname(std::string n);
	void addtoRoster(Pokemon pok);
	void setRoster(std::vector<Pokemon> ros);
	bool hasAlivePokemon();
	void printDetails(ScreenRenderer S);
	void addXP(ScreenRenderer S, std::vector<int> pokxp);
};

#endif
