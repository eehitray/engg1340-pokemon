#ifndef SCREEN_RENDERER
#define SCREEN_RENDERER

#include <string>
#include "Pokemon.h"

class ScreenRenderer {
	public:
		void clearScreen();
		void printToScreen(std::string s = "");
		void printLineOnBattleScreen(std::string s1 = "", std::string s2 = "", int setw_arg = 10, bool longBorder = false);
		char inputCharNoEnter(std::string s = "");
		std::string inputString(std::string s = "");
		int inputInt(std::string s = "");
		void printHorizontalBorder();
		void printBattleScreen(Pokemon *playerPokemon, Pokemon *opponentPokemon);
};
#endif
