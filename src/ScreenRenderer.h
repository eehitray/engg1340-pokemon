#ifndef SCREEN_RENDERER
#define SCREEN_RENDERER

#include <string>
#include <map>
#include "Pokemon.h"

class Map;

class ScreenRenderer {
	std::map<char, std::string> colorCharMap;

	public:
		ScreenRenderer();
		void clearScreen();
		void printToScreen(std::string s = "");
		void printLineOnBattleScreen(std::string s1 = "", std::string s2 = "", int setw_arg = 10, bool longBorder = false);
		char inputCharNoEnter(std::string s = "");
		std::string inputString(std::string s = "");
		int inputInt(std::string s = "");
		void printHorizontalBorder();
		void printBattleScreen(Pokemon playerPokemon, Pokemon opponentPokemon);
		void printRenderableMap(Map&);
		void printLoadingScreen();
};
#endif
