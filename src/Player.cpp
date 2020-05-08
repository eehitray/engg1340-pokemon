//Player.cpp

#include "Pokemon.h"
#include "Move.h"
#include "Player.h"
#include "ScreenRenderer.h"
#include<vector>
#include<string>
#include <fstream>

/*
   Constructor to store elementary details of Player

   Parameters:
   string n - string storing name of Player
   vector<Pokemon> pok - vector of Pokemon owned by Player

*/
Player::Player(std::string n, std::vector<Pokemon> pok)
{
	pname = n;
	roster = pok;
	
	//default location of Player (-1,-1)
	r = -1;
	c = -1;

	//Player begins from level 0
	level = 0;
}

/*
   Constructor to read Player details from file on loading saved game

   Parameters:
   ifstream& f - input stream linking to file where Player details are stored from last point in previous game
*/
Player::Player(std::ifstream& f) {
	readFromFile(f);
}

/*
   Getter for pname of Player

   Returns:
   string - pname of Player
*/
std::string Player::getPname()
{
	return pname;
}

/*
   Getter for roster of Player

   Returns:
   vector<Pokemon> - roster of Player
*/
std::vector<Pokemon> Player::getRoster()
{
	return roster;
}

/*
   Getter for r of Player

   Returns:
   int - r of Player
*/
int Player::getRow() {
	return r;
}

/*
   Getter for c of Player

   Returns:
   int - c of Player
*/
int Player::getCol() {
	return c;
}

/*
   Getter for level of Player

   Returns:
   int - level of Player
*/
int Player::getLevel() {
	return level;
}

/*
   Setter for r of Player

   Parameters:
   int newRow - integer storing row number of position of Player in map
*/
void Player::setRow(int newRow) {
	r = newRow;
}

/*
   Setter for c of Player

   Parameters:
   int newCol - integer storing column number of position of Player in map
*/
void Player::setCol(int newCol) {
	c = newCol;
}

/*
   Setter for pname of Player

   Parameters:
   string n -  string storing name of Player
*/
void Player::setPname(std::string n)
{
	pname = n;
}

/*
   Setter for level of Player

   Parameters:
   int lvl - integer storing new current level of Player
*/
void Player::setLevel(int lvl) {
	level = lvl >= 0 ? lvl : 0;
}

/*
   Adding new Pokemon to Player roster

   Parameters:
   Pokemon pok - Pokemon instance, that needs to be added to Player roster
*/
void Player::addtoRoster(Pokemon pok)
{
	roster.push_back(pok);
}

/*
   Setter for roster of Player

   Parameters:
   vector<Pokemon> ros - vector of Pokemon instances that are to be set as roster of Player
*/
void Player::setRoster(std::vector<Pokemon> ros)
{
	roster = ros;
}

/*
   To check if any Pokemon in Player roster can fight i.e. has hp>0

   Returns:
   bool - true if any Pokemon in roster has hp>0, false if all Pokemon in roster have hp=0
*/
bool Player::hasAlivePokemon()
{
	for(int i=0;i<roster.size();i++)
	{
		if(roster[i].getHP() != 0)
			return true;
	}
	return false;
}

/*
   To print details of Player 

   Parameters:
   ScreenRenderer S - ScreenRenderer instance, used to print to screen
*/
void Player::printDetails(ScreenRenderer S)
{
	S.printToScreen("Your details are: ");
	S.printToScreen("Name: " + pname);
	S.printToScreen();
	S.printToScreen("Your Pokemon: ");
	for(int i=0;i<roster.size();i++)
	{
		roster[i].printDetails(S, true);
	}
}


/*
   To add gained xp by Pokemon in roster after battle ends

   Parameters:
   ScreenRenderer S - ScreenRenderer instance, used to print to screen
   vector<int> pokxp - vector of integers storing xp gained by each pokemon in roster
*/
void Player::addXP(ScreenRenderer S, std::vector<int> pokxp)
{
	for(int i=0;i<pokxp.size();i++)
	{
		if(pokxp[i]!=0)
			roster[i].addXP(S, pokxp[i]);
	}
}

/*
   To set hp of each Pokemon in roster to maxhp
*/
void Player::healRoster()
{
	for(int i=0;i<roster.size();i++)
	{
		roster[i].setHP(roster[i].getMaxHP());
	}
}

/*
   Storing data of Player in file on saving and exiting game

   Parameters:
   ofstream& f - output tream linking to file where Player data is to be stored on saving and exiting game
*/
void Player::writeToFile(std::ofstream& f) {
	f << pname << std::endl
	  << r << std::endl
	  << c << std::endl
	  << level << std::endl;
	
	int rosterSize = (int) roster.size();

	f << rosterSize << std::endl;

	//Calling function to write to data to file for each Pokemon in Player roster
	for (Pokemon p : roster) p.writeToFile(f);
}

/*
   Reading and setting data of Player from file on loading saved game

   Parameters:
   ifstream& f - input stream linking to file where Player data is stored
*/
void Player::readFromFile(std::ifstream& f) {
	f >> pname >> r >> c >> level;

	int rosterSize;

	f >> rosterSize;

	roster.clear();

	//Reading and setting data of each Pokemon in Playe roster
	for (int i = 0; i < rosterSize; i++) {
		roster.push_back(Pokemon(f));
	}
}

