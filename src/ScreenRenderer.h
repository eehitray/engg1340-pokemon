#ifndef SCREEN_RENDERER
#define SCREEN_RENDERER

#include <string>
#include <map>
#include "Pokemon.h"

class Map;

//Class for all screen printing and input related functions
class ScreenRenderer {
	//Map to store each character in the map text file and its corresponding colour to be printed
	std::map<char, std::string> colorCharMap;

	public:
		//Constructor for ScreenRenderer. Maps the various tiles to their colour codes.
		ScreenRenderer();
	
		//Clears the screen.
		void clearScreen();

		//Prints a line to the screen.
		void printToScreen(std::string s = "");

		//To regulate formatted printing on Battle Screen
		void printLineOnBattleScreen(std::string s1 = "", std::string s2 = "", int setw_arg = 10, bool longBorder = false);
	
		//Inputs a character from the user in a non-blocking way.
		char inputCharNoEnter(std::string s = "");

		//Inputs a string from the user.
		std::string inputString(std::string s = "");

		//Inputs an int from the user.
		int inputInt(std::string s = "");
		
		//Print horizontal border of '-'
		void printHorizontalBorder();

		//To print battle details and pokemon artowrk during battle
		void printBattleScreen(Pokemon playerPokemon, Pokemon opponentPokemon);

		//Prints the renderable section of the map (see Map.cpp for details).
		void printRenderableMap(Map&);

		//Print screen to start game for user
		void printLoadingScreen();
};
#endif
