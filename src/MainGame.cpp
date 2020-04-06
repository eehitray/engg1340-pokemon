#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>

#include "MainGame.h"
#include "ScreenRenderer.h"
#include "Pokemon.h"
#include "Move.h"
#include "Player.h"

void MainGame::mainGameLoop() {
	ScreenRenderer s;
	std::string name, inp;

	s.printToScreen("Welcome to Pokemon!");

	name = s.inputString("Enter your name: ");

	Player user(name, generateRandomSelection({1, 1, 2}));
	Player opponent("David", generateRandomSelection({1, 1, 2}));

	s.printToScreen("Hello " + name + "! Ready to begin? ");

	inp = s.inputString("");

	if (inp == "Y") {
		s.clearScreen();
		initiateBattle(user, opponent, s);
	}

}

void MainGame::initiateBattle(Player a, Player b, ScreenRenderer s) {
	int turn = 0;
	int i;
	int moveInd;
	double prob;
	Move mv;

	std::vector<Pokemon> playerRoster = a.getRoster();
	std::vector<Pokemon> oppRoster = b.getRoster();

	int curPlayerPokemonIndex = 0, curOppPokemonIndex = 0;

	Pokemon *curPlayerPokemon = &playerRoster[0];
	Pokemon *curOppPokemon = &oppRoster[0];

	std::vector<Move> curPlayerMoves = curPlayerPokemon -> getMoveset();
	std::vector<Move> curOppMoves = curOppPokemon -> getMoveset();


	while (a.hasAlivePokemon() && b.hasAlivePokemon()) {
		s.printToScreen("Your current Pokemon: ");
		curPlayerPokemon -> printDetails(s);

		s.printToScreen("Your details: ");
		a.printDetails(s);

		s.printToScreen("Opponent's current Pokemon: ");
		curOppPokemon -> printDetails(s);

		if (turn % 2 == 0) { //Player turn
			if (curPlayerPokemon -> getHP() == 0) { //Switch pokemon
				s.printToScreen("Oh no! Your Pokemon fainted! Choose a new Pokemon: ");

				for (i = 0; i < playerRoster.length(); i++) {
					if (i != curPlayerPokemonIndex) {
						s.printToScreen(std::to_string(i) + ": " + playerRoster[i].getHP());
					}
				}

				curPlayerPokemonIndex = s.inputInt("Your Pokemon choice: ");
				curPlayerPokemon = &playerRoster[curPlayerPokemonIndex];
				curPlayerMoves = curPlayerPokemon -> getMoveset();
			}
			else {
				moveInd = s.inputInt("Your move: ");

				mv = curPlayerMoves[moveInd];

				prob = ((double) rand() / (RAND_MAX));

				if (prob <= mv.hit) {
					s.printToScreen("You hit using " + mv.name + " for " + std::to_string(mv.damage) + " HP!");
					curOppPokemon -> setHP(curOppPokemon -> getHP() - mv.damage);
				}
				else s.printToScreen("You missed!");
			}
		}
		else { //Opponent's turn
			if (curOppPokemon -> getHP() == 0) { //Switch pokemon
				s.printToScreen("The opponent's pokemon fainted!");

				curOppPokemon = &oppRoster[++curOppPokemonIndex];
				curOppMoves = curOppPokemon -> getMoveset();

				s.printToScreen("The opponent switches to " + curOppPokemon -> getName() + "!");

			}
			else {
				mv = curOppMoves[rand() % curOppMoves.length()];

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

		s.inputInt("");

		s.clearScreen();
	}

	if (b.hasAlivePokemon()) s.printToScreen("Opponent won!");
	else s.printToScreen("You won!");

	s.inputInt("");
}

std::vector<Pokemon> MainGame::generateRandomSelection(std::vector<int> levels) {
	ifstream in;
	in.open("PokemonList.txt");

	std::vector<Pokemon> full_list, return_list;

	string s;

	string name;
	char type;

	string mv1_name, mv1_dmg, mv1_hit;
	string mv2_name, mv2_dmg, mv2_hit;

	while (getline(in, s)) {
		istringstream st(s);

		st >> name >> type 
		   >> mv1_name >> mv1_dmg >> mv1_hit
		   >> mv2_name >> mv2_dmg >> mv2_hit;

		full_list.push_back(Pokemon(name, type, 1, {{mv1_name, mv1_dmg, mv1_hit}, {mv2_name, mv2_dmg, mv2_hit}}));
	}

	random_shuffle(full_list.begin(), full_list.end());

	for (int i = 0; i < levels.length(); i++) {
		full_list[i].setLevel(levels[i]);
		return_list.push_back(full_list[i]);
	}

	return return_list;
}
