//Pokemon.h

#ifndef POKEMON
#define POKEMON

#include<vector>
#include<string>
#include <fstream>

struct Move;
class ScreenRenderer;

//Class to store individual pokemon details and functionality
class Pokemon
{
	//string storing name of Pokemon
	std::string name;

	//character storing type of Pokemon
	char type;

	//integer storing current hp(health points) of Pokemon
	int hp;

	//integer storing maximum hp of Pokemon permissible at that level
	int maxhp;

	//integer storing xp(experience points) requried by Pokemon to level up for current level of Pokemon
	int reqxp;

	//integer storing current xp of Pokemon
	int currentxp;

	//integer storing the current level of Pokemon
	int level;

	//integer storing number of moves of Pokemon
	int numMoves;

	//vector of Move instances storing moves of Pokemon
	std::vector<Move> moveset;

	public:
	
	//Constructor to store elementary details of a Pokemon on creation
	Pokemon(std::string n, char t, int lvl, std::vector<std::string> stringset);

	//Constructor to read elementary details of a Pokemon on loading a saved game 
	Pokemon(std::ifstream&);

	//Getter for name of Pokemon
	std::string getName();

	//Getter for type of Pokemon
	char getType();

	//Getter for maxhp of Pokemon
	int getMaxHP();

	//Getter for hp of Pokemon
	int getHP();

	//Getter for level of Pokemon
	int getLevel();

	//Getter for reqxp of Pokemon 
	int getReqXP();

	//Getter for currentxp of Pokemon
	int getCurrentXP();

	//To calculate final damage of Pokemon's moves based on any type advnatage/diadvantage thatmay exist with respect to current opponent Pokemon
	std::vector<Move> getFinalDamage(char t);

	//Getter for moveset of Pokemon
	std::vector<Move> getMoveset();

	//Getter for numMoves of Pokemon
	int getNumMoves();

	//Setter for name of Pokemon
	void setName(std::string n);

	//Setter for hp of Pokemon
	void setHP(int HP);

	//Setter for level and elements dependent on level of Pokemon
	void setLevel(int lvl);

	//Updating currentxp and level of Pokemon based on experience points gained
	void addXP(ScreenRenderer S, int xp);

	//Print Pokemon information relevant to Player
	void printDetails(ScreenRenderer S, bool printMoves);

	//Calcuate xp gained by Pokemon on causing dmage to opponent Pokemon in batt;e
	int opponentXP(int d, int oppHP);

	//Storing data of Pokemon in file on saving an exiting game
	void writeToFile(std::ofstream&);

	//Reading and setting data of Pokemon from file on loading saved game
	void readFromFile(std::ifstream&);
};

#endif
