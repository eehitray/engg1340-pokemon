#include <string>
#include <cstdlib>
#include <vector>

#include "MainGame.h"
#include "ScreenRenderer.h"
#include "Pokemon.h"
#include "Move.h"

void MainGame::mainGameLoop() {
	ScreenRenderer s;
	std::string name, inp;

	std::vector<Move> playerMoves = {{"Player Move 1", 2, 0.9}, {"Player Move 2", 4, 0.4}};
	std::vector<Move> oppMoves = {{"Opponent Move 1", 2, 0.9}, {"Opponent Move 2", 4, 0.4}};

	Pokemon player("Player Pokemon", 'F', 1, playerMoves);
	Pokemon opponent("Oppoennt Pokemon", 'G', 1, oppMoves);

	s.printToScreen("Welcome to Pokemon!");

	name = s.inputString("Enter your name: ");

	s.printToScreen("Hello " + name + "! Ready to begin? ");

	inp = s.inputString("");

	if (inp == "Y") {
		s.clearScreen();
		initiateBattle(player, opponent, s);
	}

}

void MainGame::initiateBattle(Pokemon a, Pokemon b, ScreenRenderer s) {
	int turn = 0;
	std::vector<Move> playerMoves = a.getFinalDamage(a.getMoveset(), b.getType());
	std::vector<Move> oppMoves = b.getFinalDamage(b.getMoveset(), a.getType());

	while (a.getHP() > 0 && b.getHP() > 0) {
		s.printToScreen("Your HP: " + std::to_string(a.getHP()));
		s.printToScreen("Opponent HP: " + std::to_string(b.getHP()));

		if (turn % 2 == 0) { //Player turn
			int moveInd = s.inputInt("Your move (0 or 1): ");

			Move mv = playerMoves[moveInd];

			double prob = ((double) rand() / (RAND_MAX));

			if (prob <= mv.hit) {
				s.printToScreen("You hit using " + mv.name + " for " + std::to_string(mv.damage) + " HP!");
				b.setHP(b.getHP() - mv.damage);
			}
			else s.printToScreen("You missed!");

			s.inputInt("");
		}
		else { //Opponent's turn
			Move mv = oppMoves[rand() % 2];

			double prob = ((double) rand() / (RAND_MAX));

			if (prob <= mv.hit) {
				s.printToScreen("Opponent hit using " + mv.name + " for " + std::to_string(mv.damage) + " HP!");
				a.setHP(a.getHP() - mv.damage);
			}
			else s.printToScreen("Opponent missed!");

			s.inputInt("");
		}

		turn++;

		s.clearScreen();
	}

	if (a.getHP() < 0) s.printToScreen("Opponent won!");
	else s.printToScreen("You won!");

	s.inputInt("");
}
