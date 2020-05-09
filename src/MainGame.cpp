#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <ctime>

#include "MainGame.h"
#include "ScreenRenderer.h"
#include "Pokemon.h"
#include "Move.h"
#include "Player.h"
#include "Map.h"

/*
 * Runs the main game loop.
 */
void MainGame::mainGameLoop() {
	srand(time(NULL));

	//ScreenRenderer instance used for printing throughout the program.
	ScreenRenderer s;

	s.printLoadingScreen();

	//Load the player, or create new player.
	Player p = startGame(s);

	//Load the map, and set coordinates from previous game (if any).
	Map m("map.txt", p.getRow(), p.getCol());

	s.printToScreen("Hello " + p.getPname() + "! Ready to begin? (y for yes) ");

	char inp = s.inputCharNoEnter();

	bool hasMoved = false;

	//Main game loop
	while (inp != 'z') {
		s.clearScreen();

		//hasMoved stores if the player has moved
		hasMoved = handleInput(inp, m, p, s);

		//Print the map onto screen
		s.printRenderableMap(m);

		s.printToScreen();
		s.printToScreen();

		//If the player is before a trainer, prompt the player to fight him
		if (m.isBeforeTrainer(p.getLevel())) 
			s.printToScreen("To proceed further, you must face the area trainer. Are you ready? (b for yes)");

		//If the player is in a Pokemon cetre, prompt the player to heal all Pokemon
		if(m.getTileAtPlayerPos() == 'C' && hasMoved) {
			s.printToScreen("You have entered the Pokemon Centre, would you like to heal your Pokemon (Press 'h' to heal)");
		}		
		
		//Generate a random encounter
		randomEncounter(m, p, s, hasMoved);

		inp = s.inputCharNoEnter();
	}

	//Write to file and end the game
	endGame(p, m, s);
}

/*
 * Initiate a random encounter with a single Pokemon.
 *
 * Parameters:
 * Map& m - Map instance, used to check Player's location
 * Player& p - Player instance, used to initiate battle with Player
 * ScreenRenderer s - ScreenRenderer instance, used to print to screen
 * bool hasMoved - boolean storing whether player has moved
 */
void MainGame::randomEncounter(Map& m, Player& p, ScreenRenderer s, bool hasMoved) {
	//If the player has moved, and is currently on grass ('G'), there may be a random battle
	if (m.getTileAtPlayerPos() == 'G' && hasMoved) {

		//Generate a random number between 0 and 1
		double prob = ((double) rand() / (RAND_MAX));

		//If the number is less than 0.12 (12% chance), and the player has alive Pokemon, start a battle
		if (prob < 0.12 && p.hasAlivePokemon()) {
			s.printToScreen("You encountered a random Pokemon!");
			s.inputCharNoEnter();
			s.clearScreen();

			//Initiate the battle with a random Pokemon of the Player's base level
			initiateBattle(p, Player("", generateRandomSelection({m.getBasePokemonLevel()})), s);
		}
	}
}

/*
 * Run through a battle between two players.
 *
 * Parameters:
 * Player& a - the user Player
 * Player& b - the oppenent
 * ScreenRenderer s - ScreenRenderer instance, used to print to screen
 *
 * Returns:
 * bool - true if the user won, false otherwise
 */
bool MainGame::initiateBattle(Player &a, Player b, ScreenRenderer s) {

	//Current turn index (starting with user)
	int turn = 0;

	//Temporary variable
	int i;

	//Player's move index
	int moveInd;

	//Player's choice (may include switching)
	char moveChar;

	//Variable to store generated probability of a Player's move hitting the other Pokemon
	double prob;

	//Vector to store the experience gained by the user's Pokemon
	std::vector<int> exp(3,0);

	//Temporary instance of Move
	Move mv;

	//Vector containinig user player's Pokemon
	std::vector<Pokemon> playerRoster = a.getRoster();

	//Vector containing opponent player's Pokemon
	std::vector<Pokemon> oppRoster = b.getRoster();

	//Index of the user and the opponent's current Pokemon in their roster
	int curPlayerPokemonIndex = 0, curOppPokemonIndex = 0;

	//Find first alive Pokemon in Player's roster
	for (; curPlayerPokemonIndex < playerRoster.size(); curPlayerPokemonIndex++) if (playerRoster[curPlayerPokemonIndex].getHP() > 0) break;

	//Get pointers to the current Pokemon of user and opponent
	Pokemon *curPlayerPokemon = &playerRoster[curPlayerPokemonIndex];
	Pokemon *curOppPokemon = &oppRoster[curOppPokemonIndex];

	//Get the moveset of the user's and the opponent's current moves
	std::vector<Move> curPlayerMoves = curPlayerPokemon -> getFinalDamage(curOppPokemon -> getType());
	std::vector<Move> curOppMoves = curOppPokemon -> getFinalDamage(curPlayerPokemon -> getType());

	s.clearScreen();

	//Loop while both players have at least one living Pokemon
	while (a.hasAlivePokemon() && b.hasAlivePokemon()) {

		//Print battle screen
		s.printHorizontalBorder();
		s.printBattleScreen(*curPlayerPokemon, *curOppPokemon);
		s.printHorizontalBorder();

		//Player turn
		if (turn % 2 == 0) { 

			//If player's Pokemon has fainted, ask him to switch
			if (curPlayerPokemon -> getHP() == 0) { 
				s.printLineOnBattleScreen("Oh no! Your Pokemon fainted! Choose a new Pokemon: ");

				//Print available Pokemon
				for (i = 0; i < playerRoster.size(); i++) {
					if (i != curPlayerPokemonIndex && playerRoster[i].getHP() != 0) {
						s.printLineOnBattleScreen(std::to_string(i) + ": " + playerRoster[i].getName());
					}
				}

				//Get user's input, and update his current pokemon, his moves and opponent's moves
				curPlayerPokemonIndex = s.inputCharNoEnter("Your Pokemon choice: ") - 48;
				curPlayerPokemon = &playerRoster[curPlayerPokemonIndex];
				curPlayerMoves = curPlayerPokemon -> getFinalDamage(curOppPokemon -> getType());
				curOppMoves = curOppPokemon -> getFinalDamage(curPlayerPokemon -> getType());
			}

			//If the player's Pokemon is alive, prompt him to make a move
			else {
				moveChar = s.inputCharNoEnter("Your move (s for switch pokemon, 0-" + std::to_string(curPlayerPokemon -> getNumMoves() - 1) + " for move): ");

				//If the player chooses to switch Pokemon, print the available Pokemon and switch
				if (moveChar == 's') {
					s.printLineOnBattleScreen("Available Pokemon: ");

					//Print available Pokemon
					for (i = 0; i < playerRoster.size(); i++) {
						if (i != curPlayerPokemonIndex && playerRoster[i].getHP() != 0) {
							s.printLineOnBattleScreen(std::to_string(i) + ": " + playerRoster[i].getName());
						}
					}

					//Get user's input, and update his current pokemon, his moves and opponent's moves
					curPlayerPokemonIndex = s.inputCharNoEnter("Your Pokemon choice: ") - 48;
					curPlayerPokemon = &playerRoster[curPlayerPokemonIndex];
					curPlayerMoves = curPlayerPokemon -> getFinalDamage(curOppPokemon -> getType());
					curOppMoves = curOppPokemon -> getFinalDamage(curPlayerPokemon -> getType());
				}

				//If the player has chosen to make a move, carry out the move
				else {

					//Get the move at the requested index
					moveInd = moveChar - 48;

					mv = curPlayerMoves[moveInd];

					//Generate a random number, and decide whether the move hits or not according to the move's probability
					prob = ((double) rand() / (RAND_MAX));
					if (prob <= mv.hit) {
						//Reduce opponent Pokemon's health and add XP to current pokemon
						s.printLineOnBattleScreen("You hit using " + mv.name + " for " + std::to_string(mv.damage) + " HP!");
						exp[curPlayerPokemonIndex] += curPlayerPokemon -> opponentXP(mv.damage, curOppPokemon -> getHP());
						curOppPokemon -> setHP(curOppPokemon -> getHP() - mv.damage);
					}

					//If player misses, inform him
					else s.printLineOnBattleScreen("You missed!");
				}	
			}
		}
		
		//Opponent's turn
		else { 

			//If the opponent's Pokemon is dead, switch it for the next Pokemon
			if (curOppPokemon -> getHP() == 0) { 
				s.printLineOnBattleScreen("The opponent's pokemon fainted!");

				//Move to next Pokemon, update opponent's and player's moves
				curOppPokemon = &oppRoster[++curOppPokemonIndex];
				curOppMoves = curOppPokemon -> getFinalDamage(curPlayerPokemon -> getType());
				curPlayerMoves = curPlayerPokemon -> getFinalDamage(curOppPokemon -> getType());

				s.printLineOnBattleScreen("The opponent switches to " + curOppPokemon -> getName() + "!");

			}
			
			//Opponent makes a move
			else {
				//Choose a random move for the opponent
				mv = curOppMoves[rand() % curOppPokemon -> getNumMoves()];

				//Generate a random number, and decide whether the move hits or not according to the move's probability
				prob = ((double) rand() / (RAND_MAX));
				if (prob <= mv.hit) {

					//Reduce player Pokemon's health
					s.printLineOnBattleScreen("Opponent hit using " + mv.name + " for " + std::to_string(mv.damage) + " HP!");
					curPlayerPokemon -> setHP(curPlayerPokemon -> getHP() - mv.damage);
				}

				//If opponent misses, inform player
				else s.printLineOnBattleScreen("Opponent missed!");
			}
		}

		//Move to next turn
		turn++;

		//Update rosters of player and opponent to reflect changes in health
		a.setRoster(playerRoster);
		b.setRoster(oppRoster);
		
		//Print the border and input
		s.printHorizontalBorder();
		s.inputCharNoEnter("Press any key to continue...");

		s.clearScreen();

	}

	//Add gained XP to player's Pokemon
	a.addXP(s,exp);
	
	//Report who won
	bool victory = false;
	if (b.hasAlivePokemon()) s.printToScreen("Opponent won!");
	else {
		s.printToScreen("You won!");
		victory = true;
	}

	s.inputCharNoEnter("Press any key to continue...");

	//If player won, then inform him
	return victory;
}

/*
 * Generate a random selection of Pokemon of given levels.
 *
 * Parameters:
 * std::vector<int> levels - Vector containing the levels of the Pokemon to be generated
 *
 * Returns:
 * std::vector - Vector containing the Pokemon
 */
std::vector<Pokemon> MainGame::generateRandomSelection(std::vector<int> levels) {

	//Open the list of Pokemon
	std::ifstream in;
	in.open("poklist.txt");

	std::vector<Pokemon> full_list, return_list;

	std::string s;

	std::string name;
	char type;

	std::string mv1_name;
	std::string mv2_name;
	std::string mv3_name;

	//Read in all the Pokemon from the file
	while (getline(in, s)) {
		std::istringstream st(s);

		st >> name >> type 
		   >> mv1_name >> mv2_name >> mv3_name;

		//Create the Pokemon and push them into full_list
		full_list.push_back(Pokemon(name, type, 1, {mv1_name, mv2_name, mv3_name}));
	}

	//Shuffle the list of Pokemon
	random_shuffle(full_list.begin(), full_list.end());

	//Apply the levels given in the parameter to the Pokemon
	for (int i = 0; i < levels.size(); i++) {
		full_list[i].setLevel(levels[i]);

		//Push the updated Pokemon into return_list
		return_list.push_back(full_list[i]);
	}

	//Close the input file
	in.close();

	//Return the list of Pokemon (return_list)
	return return_list;
}

/*
 * Generate a random trainer name.
 *
 * Returns:
 * std::string - Name of the trainer
 */
std::string MainGame::getRandomTrainerName() {
	//Open the file containing all possible trainer names
	std::ifstream in;
	in.open("trainer_names.txt");

	std::vector<std::string> full_list;

	std::string s;

	//Read in all trainer names and add them to full_list
	while (getline(in, s)) {
		full_list.push_back(s);
	}

	//Shuffle the list
	random_shuffle(full_list.begin(), full_list.end());

	//Close the file
	in.close();

	//Return the first random name from list of trainers
	return full_list[0];
}

/*
 * Function to handle user input during the game.
 *
 * Parameters:
 * char inp - the character inputted by the user
 * Map& m - the Map object, used to update the player's location
 * Player&p - the Player object, used to heal the player or start a battle with a trainer
 * ScreenRenderer s - ScreenRenderer object, used to print to screen
 *
 * Returns:
 * bool - whether the user's input resulted in a movement
 */
bool MainGame::handleInput(char inp, Map& m, Player& p, ScreenRenderer s) {
	switch (inp) {
		
		//If the user pressed 'w', move up
		case 'w':
			m.moveUp();

			//If the user reached a row containing a trainer he has not defeated yet, move back down
			if (m.getPlayerRow() == m.getNthTrainer(p.getLevel())) m.moveDown();

			return true;

		//If the user pressed 'a', move left
		case 'a':
			m.moveLeft();
			return true;
			
		//If the user pressed 's', move down
		case 's':
			m.moveDown();
			return true;

		//If the user pressed 'd', move right
		case 'd':
			m.moveRight();
			return true;
			
		//If the user pressed 'p', display the user's details
		case 'p':
			s.clearScreen();
			p.printDetails(s);
			s.inputCharNoEnter("Press any key to continue.");
			s.clearScreen();
			return false;

		//If the user pressed 'b' and he is before a trainer, initiate a battle with the trainer
		case 'b':
	
			//Ensure that the player is at a trainer
			if (m.isBeforeTrainer(p.getLevel())) {

				//Generate a random trainer name, and inform player of the battle beginning
				std::string randomTrainerName = getRandomTrainerName();
				s.printToScreen(randomTrainerName + " challenges you!");
				s.inputCharNoEnter();
				s.clearScreen();

				//Start user's battle with a trainer whose Pokemon are of (1,1,2) levels higher than the user's player
				bool victory = initiateBattle(p, Player(randomTrainerName, generateRandomSelection({m.getBasePokemonLevel(), m.getBasePokemonLevel(), m.getBasePokemonLevel() + 1})), s);

				//If the user won, congratulate him and increase the user's level
				if (victory) {
					s.printToScreen("Congratulations!");
					p.setLevel(p.getLevel() + 1);

					//If the user beats the final trainer, let him know that he has finished the game
					if (p.getLevel() == m.getNumTrainers()) {
						s.printToScreen("You have beaten the game!");
						s.printToScreen("Feel free to roam around and play the game as long as you want.");
					}
				}
				
				//If the user lost, inform him
				else {
					s.printToScreen("Better luck next time!");
				}

				s.inputCharNoEnter();
				s.clearScreen();
			}	
			return false;

		//If the user pressed 'h' and he is in a Pokemon centre, heal his Pokemon
		case 'h':

			//Ensure that the player is in a Pokemon centre
			if(m.getTileAtPlayerPos() == 'C') {

				//Heal the player's Pokemon
				p.healRoster();
				s.printToScreen("Your Pokemon have been healed!");
				s.inputCharNoEnter();
				s.clearScreen();
			}	
			return false;
			
	}

	return false;
}

/*
 * Load the player's file if it exists, and create if it doesn't, then start the game.
 *
 * Parameters:
 * ScreenRenderer s - ScreenRenderer instance used to print to screen.
 *
 * Returns:
 * Player - the Player object, either created or loaded from existing file.
 */
Player MainGame::startGame(ScreenRenderer s) {
	s.clearScreen();

	//Prompt user for his name
	std::string name = s.inputString("Enter your name: ");

	//Load ifstream object tied to file determined by user's name
	std::ifstream saveFile(name + ".bin", std::ios::binary);

	//If the file exists...
	if (saveFile) {

		//Inform the user that the file exists and give them the option to load their previous game. 
		char c = s.inputCharNoEnter("A save file was found for your character. Would you like to load it (y), or would you like to start a new game? (n; file will be overwritten) ");

		//If the user chooses to load their previous game, create a Player instance from the file
		if (c == 'y') {
			Player p = Player(saveFile);
			saveFile.close();
			return p;
		}
	}

	//Close the file
	saveFile.close();

	//Generate a new player
	return Player(name, generateRandomSelection({1, 1, 2}));
}

/*
 * Save the player's progress to a file, and end the game.
 *
 * Parameters:
 * Player& p - the Player object to save
 * Map& p - Map object to extract Player's coordinates
 * ScreenRenderer s - ScreenRenderer instance used to print to screen
 */
void MainGame::endGame(Player& p, Map& m, ScreenRenderer s) {
	//Extract Player's coordinates from the Map object and set them in the Player object
	p.setRow(m.getPlayerRow());
	p.setCol(m.getPlayerCol());

	//Write the Player object to file
	std::ofstream f(p.getPname() + ".bin", std::ios::binary);
	p.writeToFile(f);
	f.close();

	//Thank the user for playing
	s.printToScreen("Thanks for playing! Your progress has been saved. Come back soon!");
}
