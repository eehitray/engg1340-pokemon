#ifndef MAIN_GAME
#define MAIN_GAME

#include <vector>
#include <string>

class Pokemon;
class Player;
class ScreenRenderer;
class Map;

//Class to carry out all main game related functions.
class MainGame {

	public:
		// Runs the main game loop.
		void mainGameLoop();

		//Initiate a random encounter with a single Pokemon.
		void randomEncounter(Map&, Player&, ScreenRenderer, bool);

		//Initiate a random encounter with a single Pokemon.
		bool initiateBattle(Player&, Player, ScreenRenderer);

		//Generate a random selection of Pokemon of given levels.
		std::vector<Pokemon> generateRandomSelection(std::vector<int>);

		//Generate a random trainer name.
		std::string getRandomTrainerName();

		//Function to handle user input during the game.
		bool handleInput(char, Map&, Player&, ScreenRenderer);
		
		//Load the player's file if it exists, and create if it doesn't, then start the game.
		Player startGame(ScreenRenderer);

		//Save the player's progress to a file, and end the game.
		void endGame(Player&, Map&, ScreenRenderer);

};

#endif
