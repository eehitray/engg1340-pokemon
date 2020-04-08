#ifndef MAIN_GAME
#define MAIN_GAME

#include <vector>

class Pokemon;
class Player;
class ScreenRenderer;

class MainGame {

	public:
		void mainGameLoop();
		void initiateBattle(Player, Player, ScreenRenderer);
		std::vector<Pokemon> generateRandomSelection(std::vector<int>);

};

#endif