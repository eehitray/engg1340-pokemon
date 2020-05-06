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

void MainGame::mainGameLoop() {
	srand(time(NULL));
	ScreenRenderer s;

	s.printLoadingScreen();

	Player p = startGame(s);

	Map m("map.txt", p.getRow(), p.getCol());

	s.printToScreen("Hello " + p.getPname() + "! Ready to begin? (y for yes) ");

	char inp = s.inputCharNoEnter();

	bool hasMoved = false;

	while (inp != 'z') {
		s.clearScreen();
		hasMoved = handleInput(inp, m, p, s);
		s.printRenderableMap(m);

		s.printToScreen();
		s.printToScreen();

		if (m.getTileAtPlayerPos() == 'G' && hasMoved) {
			double prob = ((double) rand() / (RAND_MAX));

			if (prob < 0.12 && p.hasAlivePokemon()) {
				s.printToScreen("You encountered a random Pokemon!");
				s.inputCharNoEnter();
				s.clearScreen();
				initiateBattle(p, Player("", generateRandomSelection({1})), s);
			}
		}
		inp = s.inputCharNoEnter();
	}
 

	//Write to file
	endGame(p, m, s);
}

void MainGame::initiateBattle(Player &a, Player b, ScreenRenderer s) {
	int turn = 0;
	int i;
	int moveInd;
	char moveChar;
	double prob;
	std::vector<int> exp(3,0);
	Move mv;

	std::vector<Pokemon> playerRoster = a.getRoster();
	std::vector<Pokemon> oppRoster = b.getRoster();

	int curPlayerPokemonIndex = 0, curOppPokemonIndex = 0;

	//Find first alive Pokemon
	for (; curPlayerPokemonIndex < playerRoster.size(); curPlayerPokemonIndex++) if (playerRoster[curPlayerPokemonIndex].getHP() > 0) break;

	Pokemon *curPlayerPokemon = &playerRoster[curPlayerPokemonIndex];
	Pokemon *curOppPokemon = &oppRoster[curOppPokemonIndex];

	std::vector<Move> curPlayerMoves = curPlayerPokemon -> getFinalDamage(curOppPokemon -> getType());
	std::vector<Move> curOppMoves = curOppPokemon -> getFinalDamage(curPlayerPokemon -> getType());

	s.clearScreen();

	while (a.hasAlivePokemon() && b.hasAlivePokemon()) {

		s.printHorizontalBorder();
		s.printBattleScreen(*curPlayerPokemon, *curOppPokemon);
		s.printHorizontalBorder();

		if (turn % 2 == 0) { //Player turn
			if (curPlayerPokemon -> getHP() == 0) { //Switch pokemon
				s.printLineOnBattleScreen("Oh no! Your Pokemon fainted! Choose a new Pokemon: ");

				for (i = 0; i < playerRoster.size(); i++) {
					if (i != curPlayerPokemonIndex && playerRoster[i].getHP() != 0) {
						s.printLineOnBattleScreen(std::to_string(i) + ": " + playerRoster[i].getName());
					}
				}

				curPlayerPokemonIndex = s.inputCharNoEnter("Your Pokemon choice: ") - 48;
				curPlayerPokemon = &playerRoster[curPlayerPokemonIndex];
				curPlayerMoves = curPlayerPokemon -> getFinalDamage(curOppPokemon -> getType());
				curOppMoves = curOppPokemon -> getFinalDamage(curPlayerPokemon -> getType());
			}
			else {
				moveChar = s.inputCharNoEnter("Your move (s for switch pokemon, 0-2 for move): ");

				if (moveChar == 's') {
					s.printLineOnBattleScreen("Available Pokemon: ");

					for (i = 0; i < playerRoster.size(); i++) {
						if (i != curPlayerPokemonIndex && playerRoster[i].getHP() != 0) {
							s.printLineOnBattleScreen(std::to_string(i) + ": " + playerRoster[i].getName());
						}
					}

					curPlayerPokemonIndex = s.inputCharNoEnter("Your Pokemon choice: ") - 48;
					curPlayerPokemon = &playerRoster[curPlayerPokemonIndex];
					curPlayerMoves = curPlayerPokemon -> getFinalDamage(curOppPokemon -> getType());
					curOppMoves = curOppPokemon -> getFinalDamage(curPlayerPokemon -> getType());
				}
				else {
					moveInd = moveChar - 48;

					mv = curPlayerMoves[moveInd];

					prob = ((double) rand() / (RAND_MAX));

					if (prob <= mv.hit) {
						s.printLineOnBattleScreen("You hit using " + mv.name + " for " + std::to_string(mv.damage) + " HP!");
						exp[curPlayerPokemonIndex] += curPlayerPokemon -> opponentXP(mv.damage, curOppPokemon -> getHP());
						curOppPokemon -> setHP(curOppPokemon -> getHP() - mv.damage);
					}
					else s.printLineOnBattleScreen("You missed!");
				}	
			}
		}
		else { //Opponent's turn
			if (curOppPokemon -> getHP() == 0) { //Switch pokemon
				s.printLineOnBattleScreen("The opponent's pokemon fainted!");

				curOppPokemon = &oppRoster[++curOppPokemonIndex];
				curOppMoves = curOppPokemon -> getFinalDamage(curPlayerPokemon -> getType());
				curPlayerMoves = curPlayerPokemon -> getFinalDamage(curOppPokemon -> getType());

				s.printLineOnBattleScreen("The opponent switches to " + curOppPokemon -> getName() + "!");

			}
			else {
				mv = curOppMoves[rand() % curOppMoves.size()];

				prob = ((double) rand() / (RAND_MAX));

				if (prob <= mv.hit) {
					s.printLineOnBattleScreen("Opponent hit using " + mv.name + " for " + std::to_string(mv.damage) + " HP!");
					curPlayerPokemon -> setHP(curPlayerPokemon -> getHP() - mv.damage);
				}
				else s.printLineOnBattleScreen("Opponent missed!");
			}
		}

		turn++;

		a.setRoster(playerRoster);
		b.setRoster(oppRoster);
		
		s.printHorizontalBorder();
		s.inputCharNoEnter("Press any key to continue...");

		s.clearScreen();

	}

	a.addXP(s,exp);
	
	if (b.hasAlivePokemon()) s.printToScreen("Opponent won!");
	else s.printToScreen("You won!");

	s.inputCharNoEnter("Press any key to continue...");
}

std::vector<Pokemon> MainGame::generateRandomSelection(std::vector<int> levels) {
	std::ifstream in;
	in.open("poklist_twomoves.txt");

	std::vector<Pokemon> full_list, return_list;

	std::string s;

	std::string name;
	char type;

	std::string mv1_name;
	std::string mv2_name;

	while (getline(in, s)) {
		std::istringstream st(s);

		st >> name >> type 
		   >> mv1_name >> mv2_name;

		full_list.push_back(Pokemon(name, type, 1, {mv1_name, mv2_name}));
	}

	random_shuffle(full_list.begin(), full_list.end());

	for (int i = 0; i < levels.size(); i++) {
		full_list[i].setLevel(levels[i]);
		return_list.push_back(full_list[i]);
	}

	return return_list;
}

bool MainGame::handleInput(char inp, Map& m, Player p, ScreenRenderer s) {
	switch (inp) {
		case 'w':
			m.moveUp();
			return true;
		case 'a':
			m.moveLeft();
			return true;
		case 's':
			m.moveDown();
			return true;
		case 'd':
			m.moveRight();
			return true;
		case 'p':
			s.clearScreen();
			p.printDetails(s);
			s.inputCharNoEnter("Press any key to continue.");
			s.clearScreen();
			return false;
			
	}

	return false;
}

Player MainGame::startGame(ScreenRenderer s) {
	s.clearScreen();
	std::string name = s.inputString("Enter your name: ");

	std::ifstream saveFile(name + ".bin", std::ios::binary);

	if (saveFile) {
		char c = s.inputCharNoEnter("A save file was found for your character. Would you like to load it (y), or would you like to start a new game? (n; file will be overwritten)");

		if (c == 'y') {
			Player p = Player(saveFile);
			saveFile.close();
			return p;
		}
	}

	saveFile.close();

	return Player(name, generateRandomSelection({1, 1, 2}));
}

void MainGame::endGame(Player& p, Map m, ScreenRenderer s) {
	p.setRow(m.getPlayerRow());
	p.setCol(m.getPlayerCol());

	std::ofstream f(p.getPname() + ".bin", std::ios::binary);
	p.writeToFile(f);
	f.close();

	s.printToScreen("Thanks for playing! Your progress has been saved. Come back soon!");
}
