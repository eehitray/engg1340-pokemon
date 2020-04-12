#include <string>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Pokemon.h"
#include "Move.h"
#include "ScreenRenderer.h"

void ScreenRenderer::clearScreen() {
	std::cout << "\033[2J\033[1;1H";
	std::cout << "\033[2J\033[1;1H";
}

void ScreenRenderer::printToScreen(std::string s) {
	std::cout << s << std::endl;
}

void ScreenRenderer::printLineOnBattleScreen(std::string s1, std::string s2, int spaceWidth) {
	std::cout<<std::left<<std::setw(80)<< s1;
	for(int i=0;i< spaceWidth; i++)
		std::cout<<" ";
	std::cout<< s2 << std::endl;
}

char ScreenRenderer::inputCharNoEnter(std::string s) {
	std::cout << s;

	system("stty raw");
	char c = getchar();
	system("stty cooked");

	std::cout << std::endl;

	return c;
}

std::string ScreenRenderer::inputString(std::string s) {
	std::string input;

	std::cout << s;
	getline(std::cin, input);
	return input;
}

int ScreenRenderer::inputInt(std::string s) {
	int input;

	std::cout << s;
	std::cin >> input;
    return input;	
}

void ScreenRenderer::printBattleScreen(Pokemon *playerPokemon, Pokemon *opponentPokemon)
{
	int spaceWidthInfo = 10;
	int spaceWidthImage = 30;

	int playerPokemonFileLines = 0, opponentPokemonFileLines = 0;

	std::ifstream playerPokemonImage, opponentPokemonImage;
	std::string tempPlayer, tempOpponent;

	std::string playerPokemonFile = playerPokemon -> getName() + ".txt";
	std::string opponentPokemonFile = opponentPokemon -> getName() + ".txt";

	playerPokemonImage.open(playerPokemonFile);
	opponentPokemonImage.open(opponentPokemonFile);

	printLineOnBattleScreen(playerPokemon -> getName(), opponentPokemon -> getName(), spaceWidthInfo);
	printLineOnBattleScreen("Level: " + std::to_string(playerPokemon -> getLevel()), "Level: " + std::to_string(opponentPokemon -> getLevel()), spaceWidthInfo);
	printLineOnBattleScreen("Type: " + std::string(1,playerPokemon -> getType()),"Type: " + std::string(1,opponentPokemon -> getType()), spaceWidthInfo);
	printLineOnBattleScreen("HP: " + std::to_string(playerPokemon -> getHP()), "HP: " + std::to_string(opponentPokemon -> getHP()), spaceWidthInfo);

	printToScreen();
	printToScreen("Moves: ");
	std::vector<Move> mvset = playerPokemon -> getMoveset();
	printToScreen();
	for(int i=0; i< mvset.size(); i++)
	{
		printToScreen(std::to_string(i) + ". " + mvset[i].name + "  Damage: " + std::to_string(mvset[i].damage));
	}

	printToScreen();

	while(getline(playerPokemonImage,tempPlayer))
		++playerPokemonFileLines;
	while(getline(opponentPokemonImage,tempOpponent))
		++opponentPokemonFileLines;

	playerPokemonImage.close();
	opponentPokemonImage.close();

	playerPokemonImage.open(playerPokemonFile);
	opponentPokemonImage.open(opponentPokemonFile);

	if(playerPokemonFileLines > opponentPokemonFileLines)
	{
		for(int i=0;i< playerPokemonFileLines - opponentPokemonFileLines; i++)
		{
			getline(playerPokemonImage,tempPlayer);
			printToScreen(tempPlayer);
		}
	}
	else
	{
		for(int i=0;i< opponentPokemonFileLines - playerPokemonFileLines; i++)
		{
			getline(opponentPokemonImage,tempOpponent);
			printLineOnBattleScreen("" , tempOpponent, spaceWidthInfo); 
		}
	}

	while(getline(playerPokemonImage,tempPlayer) && getline(opponentPokemonImage,tempOpponent))
	{
		printLineOnBattleScreen(tempPlayer, tempOpponent, spaceWidthImage);
	}

	playerPokemonImage.close();
	opponentPokemonImage.close();

	printToScreen();
	printToScreen();
}
