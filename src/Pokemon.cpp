//Pokemon.cpp
#include<string>
#include "Move.h"
#include "Pokemon.h"
#include "ScreenRenderer.h"
#include<vector>
#include <fstream>

/*
   Constructor to store elemetary details of a Pokemon on creation

   Parameters:
   string n - string storing name of Pokemon
   char t - character storing Pokemon type
   int lvl - integer storing level of Pokemon
   vector<string> stringset - vector of strings storing name of Moves of the Pokemon
*/
Pokemon::Pokemon(std::string n, char t, int lvl, std::vector<std::string> stringset)
{	name = n;
	type = t;

	//Default current experience points are 0
	currentxp = 0;

	moveset.push_back({stringset[0],3,1});
	moveset.push_back({stringset[1],5,0.7});
	moveset.push_back({stringset[2],7,0.5});

	setLevel(lvl);
}

/*
   Constructor to read elementary details of a Pokemon on loading of saved game

   Parameters:
   ifstream& f - input stream linking to file with Pokemon's stored details fom last point in previous game
*/
Pokemon::Pokemon(std::ifstream& f) {
	readFromFile(f);
}

/*
   Getter for name of Pokemon

   Returns:
   string - name of Pokemon
*/   
std::string Pokemon::getName()
{
	return name;		
}

/*
   Getter for type of Pokemon

   Returns:
   char - type of Pokemon
*/
char Pokemon::getType()
{
	return type;
}

/*
   Getter for maxhp of Pokemon

   Returns:
   int - maxhp of Pokemon
*/
int Pokemon::getMaxHP()
{
	return maxhp;
}

/*
   Getter for hp of Pokemon

   Returns:
   int - hp of Pokemon
*/
int Pokemon::getHP()
{
	return hp;
}

/*
   Getter for level of Pokemon

   Returns:
   int - level of Pokemon
*/
int Pokemon::getLevel()
{
	return level;
}

/*
   Getter for reqxp of Pokemon

   Returns:
   int - reqxp of Pokemon
*/
int Pokemon::getReqXP()
{
	return reqxp;
}

/*
   Getter for currentxp of Pokemon

   Returns:
   int - currentxp of Pokemon
*/
int Pokemon::getCurrentXP()
{
	return currentxp;
}

/*
   To calculate final damage of a Pokemon's moves based on any type advantage/disadvantage that may exist with respect to current opponent Pokemon

   Parameters:
   char t - character storing type of current opponent Pokemon

   Returns:
   vector<Move> - vector of Move instances with updated damage of each Move based on opponent Pokemon type
*/
std::vector<Move> Pokemon::getFinalDamage(char t)
{
	std::vector<Move> mvset = moveset;

	//When current Player Pokemon is fire type
	if(type=='F')
	{
		//Damage of moves decreaed when battling water type Pokemon
		if(t=='W')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage -= level; 

		//Damage of moves increased when battling grass type Pokemon
		else if(t=='G')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage += level;
	}

	//When current Player Pokemon is water type
	else if(type=='W')
	{
		//Damage of moves increased when battling fire type Pokemon
		if(t=='F')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage += level;

		//Damage of moves decreased when battling grass type Pokemon
		else if(t=='G')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage -= level;
	}

	//When current Player Pokemon is grass type
	else
	{
		//Damage of moves decreased when battling fire type Pokemon
		if(t=='F')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage -= level;

		//Damage of moves increased when battling water type Pokemon
		else if(t=='W')
			for(int i=0;i<mvset.size();i++)
				mvset[i].damage += level;
	}
	return mvset;
}

/*
   Getter for moveset of Pokemon

   Returns:
   vector<Move> - moveset of Pokemon
*/
std::vector<Move> Pokemon::getMoveset()
{
	return moveset;
}

/*
   Getter for numMoves of Pokemon

   Returns:
   int - numMoves of Pokemon
*/
int Pokemon::getNumMoves() {
	return numMoves;
}

/*
   Setter for name of Pokemon

   Parameters:
   string n - string storing name of Pokemon
*/
void Pokemon::setName(std::string n)
{
	name = n;
}

/*
   Setter for hp of Pokemon

   Parameters:
   int HP - integer storing the new current hp of Pokemon
*/
void Pokemon::setHP(int HP)
{
	hp = HP;

	//Pokemon hp cannot be less than 0 (on fainting)
	if (hp < 0) hp = 0; 

	//Pokemon hp cannot exceed maxhp for that level 
	if (hp > maxhp) hp = maxhp;
}

/*
   Setter for level and elements dependent on level of Pokemon

   Parameters:
   int lvl - integer storing the new current level of Pokemon
*/
void Pokemon::setLevel(int lvl)
{
	level = lvl;
	maxhp = level*10;  
	hp = maxhp;
	reqxp = level*100;

	//As level increases, damage of Pokemon's moves increases
	moveset[0].damage = level * 3;
	moveset[1].damage = level * 5;
	moveset[2].damage = level * 7;

	//Unlocking of 3rd move on crossing level 2
	if (level >= 2) numMoves = 3;
	else numMoves = 2;
}

/*
   Updating currrentxp and level of Pokemon based on experience points gained

   Parameters:
   ScreenRenderer S - ScreenRenderer instance, used to print to screen
   int xp - experinece points gained by Pokemon in battle
*/
void Pokemon::addXP(ScreenRenderer S,int xp)
{
	while(xp>0)
	{
		//Experience points gained but not enough to level up
		if(currentxp+xp < reqxp)
		{
			currentxp += xp;
			S.printToScreen(name + " gained " + std::to_string(xp) +" XP!");
			xp = 0;
		}
		
		//Experience points gained enough to level up
		else
		{
			//Adding only those xp required to level up, to allow extra extra xp to be added on next iteration of loop
			S.printToScreen(name + " gained " + std::to_string(reqxp - currentxp) +" XP!");
			xp = xp - reqxp + currentxp;
			currentxp=0;
			
			//To update level by 1
			setLevel( getLevel() + 1); 

			S.printToScreen(name + " levelled up!");
		}
	}
}

/*
   Print Pokemon information relevant to Player

   Parameters:
   ScreenRenderer S - ScreenRenderer instance, used to print to screen
   bool printMoves - boolean storing whether to print moves of Pokemon, true if displaying Player Pokemon details, false when displaying Opponent Pokemon details
*/
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

/*
   Calculate xp gained by Pokemon on causing damage to opponent Pokemon in battle

   Parameters:
   int d - integer storing damage caused by Player's Pokemon's move
   int oppHP - integer storing opponent's HP before Player's Pokemon's move

   Returns:
   int - xp gained by Player Pokemon for causing damage to opponent Pokemon
*/
int Pokemon::opponentXP(int d, int oppHP)
{
	int xp;
	//If opponent Pokemon faints, then calculate xp based on remaining opponent hp
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

/*
   Storing data of Pokemon in file on saving and exiting game

   Parameters:
   ofstream& f - output stream linking to file where Pokemon data is to be stored on saving and exiting game
*/
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

/*
   Reading and setting data of Pokemon from file on loading saved game

   Parameters:
   ifstream& f - input stream linking to file where Pokemon data is stored
*/
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
