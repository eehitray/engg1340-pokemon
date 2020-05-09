//Player.h

#ifndef PLAYER
#define PLAYER

#include "Pokemon.h"
#include "Move.h"
#include <string>
#include <vector>
#include <fstream>

class ScreenRenderer;

//Class to store player details and functionality 
class Player
{
	//string storing name of Player
	std::string pname;

	//vector of Pokemon instances, storing Pokemon owned by Player
	std::vector<Pokemon> roster;

	//integers storing row and column position of Player on map
	int r, c;

	//integer storing level of Player, indicating how many trainers the player has beaten 
	int level;

	public:

	//Constructor to store elementary details of Player
	Player(std::string, std::vector<Pokemon>);

	//Constructor to read Player details from file on loading saved game
	Player(std::ifstream&);

	//Getter for pname of Player
	std::string getPname();

	//Getter for roster of Player
	std::vector<Pokemon> getRoster();

	//Getter for r of Player
	int getRow();

	//Getter for c of Player
	int getCol();

	//Getter for level of Player
	int getLevel();

	//Setter for r of Player
	void setRow(int);

	//Setter for c of Player
	void setCol(int);

	//Setter for level of Player
	void setLevel(int);

	//Setter for pname of Player
	void setPname(std::string);

	//Adding new Pokemon to Player roster
	void addtoRoster(Pokemon);

	//Setter for roster of Player
	void setRoster(std::vector<Pokemon>);

	//To check if any Pokemon in Player roster can fight i.e. has hp>0
	bool hasAlivePokemon();

	//To print deatils of Player
	void printDetails(ScreenRenderer S);

	//To add gained xp of Pokemon in roster after battle ends
	void addXP(ScreenRenderer S, std::vector<int> pokxp);

	//To set hp of each Pokemon in roster to maxhp
	void healRoster();

	//Storing data of Player in file on saving and exiting game
	void writeToFile(std::ofstream&);

	//Reading and setting data of Player from file on loading saved game
	void readFromFile(std::ifstream&);
};

#endif
