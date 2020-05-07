#ifndef MAIN_GAME
#define MAIN_GAME

#include <vector>
#include <string>

class Pokemon;
class Player;
class ScreenRenderer;
class Map;

class MainGame {

	public:
		void mainGameLoop();
		void randomEncounter(Map&, Player&, ScreenRenderer, bool);
		bool initiateBattle(Player&, Player, ScreenRenderer);
		std::vector<Pokemon> generateRandomSelection(std::vector<int>);
		std::string getRandomTrainerName();
		bool handleInput(char, Map&, Player&, ScreenRenderer);
		Player startGame(ScreenRenderer);
		void endGame(Player&, Map&, ScreenRenderer);

};

#endif
