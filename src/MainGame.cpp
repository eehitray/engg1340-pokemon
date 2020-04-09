#include <string>
#include <iostream>
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

void MainGame::mainGameLoop() {
	srand(time(NULL));
	ScreenRenderer s;
	std::string name;
	char inp;

	s.printToScreen("Welcome to Pokemon!");

	name = s.inputString("Enter your name: ");

	Player user(name, generateRandomSelection({1, 1, 2}));
	Player opponent("David", generateRandomSelection({1, 1, 2}));

	s.printToScreen("Hello " + name + "! Ready to begin? (y for yes) ");

	inp = s.inputCharNoEnter();

	if (inp == 'y') {
		s.clearScreen();
		initiateBattle(user, opponent, s);
	}
 
}

void MainGame::initiateBattle(Player a, Player b, ScreenRenderer s) {
	int turn = 0;
	int i;
	int moveInd;
	double prob;
	std::vector<int> exp(3,0);
	Move mv;

	std::vector<Pokemon> playerRoster = a.getRoster();
	std::vector<Pokemon> oppRoster = b.getRoster();

	int curPlayerPokemonIndex = 0, curOppPokemonIndex = 0;

	Pokemon *curPlayerPokemon = &playerRoster[0];
	Pokemon *curOppPokemon = &oppRoster[0];

	std::vector<Move> curPlayerMoves = curPlayerPokemon -> getFinalDamage(curOppPokemon -> getType());
	std::vector<Move> curOppMoves = curOppPokemon -> getFinalDamage(curPlayerPokemon -> getType());


	while (a.hasAlivePokemon() && b.hasAlivePokemon()) {
		s.printToScreen("Your current Pokemon: ");
		curPlayerPokemon -> printDetails(s, true);

		s.printToScreen("Your details: ");
		a.printDetails(s);

		s.printToScreen("Opponent's current Pokemon: ");
		curOppPokemon -> printDetails(s, false);

		if (turn % 2 == 0) { //Player turn
			if (curPlayerPokemon -> getHP() == 0) { //Switch pokemon
				s.printToScreen("Oh no! Your Pokemon fainted! Choose a new Pokemon: ");

				for (i = 0; i < playerRoster.size(); i++) {
					if (i != curPlayerPokemonIndex && playerRoster[i].getHP() != 0) {
						s.printToScreen(std::to_string(i) + ": " + playerRoster[i].getName());
					}
				}

				curPlayerPokemonIndex = s.inputCharNoEnter("Your Pokemon choice: ") - 48;
				curPlayerPokemon = &playerRoster[curPlayerPokemonIndex];
				curPlayerMoves = curPlayerPokemon -> getFinalDamage(curOppPokemon -> getType());
				curOppMoves = curOppPokemon -> getFinalDamage(curPlayerPokemon -> getType());
			}
			else {
				moveInd = s.inputCharNoEnter("Your move: ") - 48;

				mv = curPlayerMoves[moveInd];

				prob = ((double) rand() / (RAND_MAX));

				if (prob <= mv.hit) {
					s.printToScreen("You hit using " + mv.name + " for " + std::to_string(mv.damage) + " HP!");
					exp[curPlayerPokemonIndex] += curPlayerPokemon -> opponentXP(mv.damage, curOppPokemon -> getHP());
					curOppPokemon -> setHP(curOppPokemon -> getHP() - mv.damage);
				}
				else s.printToScreen("You missed!");
			}
		}
		else { //Opponent's turn
			if (curOppPokemon -> getHP() == 0) { //Switch pokemon
				s.printToScreen("The opponent's pokemon fainted!");

				curOppPokemon = &oppRoster[++curOppPokemonIndex];
				curOppMoves = curOppPokemon -> getFinalDamage(curPlayerPokemon -> getType());
				curPlayerMoves = curPlayerPokemon -> getFinalDamage(curOppPokemon -> getType());

				s.printToScreen("The opponent switches to " + curOppPokemon -> getName() + "!");

			}
			else {
				mv = curOppMoves[rand() % curOppMoves.size()];

				prob = ((double) rand() / (RAND_MAX));

				if (prob <= mv.hit) {
					s.printToScreen("Opponent hit using " + mv.name + " for " + std::to_string(mv.damage) + " HP!");
					curPlayerPokemon -> setHP(curPlayerPokemon -> getHP() - mv.damage);
				}
				else s.printToScreen("Opponent missed!");
			}
		}

		turn++;

		a.setRoster(playerRoster);
		b.setRoster(oppRoster);

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
