#ifndef MAIN_GAME
#define MAIN_GAME

#include "Pokemon.h"
#include "ScreenRenderer.h"

class MainGame {

	public:
		void mainGameLoop();
		void initiateBattle(Pokemon, Pokemon, ScreenRenderer);

};

#endif
