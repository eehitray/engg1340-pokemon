#ifndef MAIN_GAME
#define MAIN_GAME

#include <vector>

class Pokemon;
class ScreenRenderer;

class MainGame {

	public:
		void mainGameLoop();
		void initiateBattle(Pokemon, Pokemon, ScreenRenderer);
		void generateRandomSelection(std::vector<int>);

};

#endif
