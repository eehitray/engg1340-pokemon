#include <string>
#include <map>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Pokemon.h"
#include "Move.h"
#include "ScreenRenderer.h"
#include "Map.h"

ScreenRenderer::ScreenRenderer() {
	colorCharMap.insert(std::pair<char, std::string> ('G', "\033[3;42;30m \033[0m"));
	colorCharMap.insert(std::pair<char, std::string> ('R', "\033[3;43;30m \033[0m"));
	colorCharMap.insert(std::pair<char, std::string> ('P', "\033[3;46;30m \033[0m"));
	colorCharMap.insert(std::pair<char, std::string> ('C', "\033[3;41;30m \033[0m"));
	colorCharMap.insert(std::pair<char, std::string> ('T', "\033[3;45;30m \033[0m"));
}

void ScreenRenderer::clearScreen() {
	std::cout << "\033[2J\033[1;1H";
	std::cout << "\033[2J\033[1;1H";
}

void ScreenRenderer::printToScreen(std::string s) {
	std::cout << s << std::endl;
}

void ScreenRenderer::printLineOnBattleScreen(std::string s1, std::string s2, int spaceWidth, bool longBorder) {
	std::cout<<std::left<<std::setw(80)<< s1;
	for(int i=0;i< spaceWidth; i++)
		std::cout<<" ";
	std::cout<< std::left << std::setw(80) << s2;
	if(longBorder == true)
		std::cout<< std::right << std::setw(21) << "|" << std::endl;
	else
		std::cout<< std::right << "|" << std::endl;
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

void ScreenRenderer::printHorizontalBorder() {
	for(int i=0;i<171;i++)
		std::cout<<"-";
	std::cout<<std::endl;
}

void ScreenRenderer::printBattleScreen(Pokemon playerPokemon, Pokemon opponentPokemon)
{
	int spaceWidthInfo = 10;
	int spaceWidthImage = 30;

	int playerPokemonFileLines = 0, opponentPokemonFileLines = 0;

	std::ifstream playerPokemonImage, opponentPokemonImage;
	std::string tempPlayer, tempOpponent;

	std::string playerPokemonFile = playerPokemon.getName() + ".txt";
	std::string opponentPokemonFile = opponentPokemon.getName() + ".txt";

	playerPokemonImage.open(playerPokemonFile);
	opponentPokemonImage.open(opponentPokemonFile);

	printLineOnBattleScreen(playerPokemon.getName(), opponentPokemon.getName(), spaceWidthInfo);
	printLineOnBattleScreen("Level: " + std::to_string(playerPokemon.getLevel()), "Level: " + std::to_string(opponentPokemon.getLevel()), spaceWidthInfo);
	printLineOnBattleScreen("Type: " + std::string(1,playerPokemon.getType()),"Type: " + std::string(1,opponentPokemon.getType()), spaceWidthInfo);
	printLineOnBattleScreen("HP: " + std::to_string(playerPokemon.getHP()), "HP: " + std::to_string(opponentPokemon.getHP()), spaceWidthInfo);

	printLineOnBattleScreen();
	printLineOnBattleScreen("Moves: ");
	std::vector<Move> mvset = playerPokemon.getMoveset();
	printLineOnBattleScreen();
	for(int i=0; i< mvset.size(); i++)
	{
		printLineOnBattleScreen(std::to_string(i) + ". " + mvset[i].name + "  Damage: " + std::to_string(mvset[i].damage));
	}

	printLineOnBattleScreen();

	while(getline(playerPokemonImage,tempPlayer))
		++playerPokemonFileLines;
	while(getline(opponentPokemonImage,tempOpponent))
		++opponentPokemonFileLines;
	
	playerPokemonImage.clear();
	playerPokemonImage.seekg(0,std::ios::beg);
	opponentPokemonImage.clear();
	opponentPokemonImage.seekg(0,std::ios::beg);

	if(playerPokemonFileLines > opponentPokemonFileLines)
	{
		for(int i=0;i< playerPokemonFileLines - opponentPokemonFileLines; i++)
		{
			getline(playerPokemonImage,tempPlayer);
			printLineOnBattleScreen(tempPlayer, "", spaceWidthImage);
		}
	}
	else
	{
		for(int i=0;i< opponentPokemonFileLines - playerPokemonFileLines; i++)
		{
			getline(opponentPokemonImage,tempOpponent);
			printLineOnBattleScreen("" , tempOpponent, spaceWidthInfo, true);  
		}
	}

	while(getline(playerPokemonImage,tempPlayer) && getline(opponentPokemonImage,tempOpponent))
	{
		printLineOnBattleScreen(tempPlayer, tempOpponent, spaceWidthImage, true);
	}

	playerPokemonImage.close();
	opponentPokemonImage.close();

	printLineOnBattleScreen();
	printLineOnBattleScreen();
}

void ScreenRenderer::printRenderableMap(Map m) {
	std::vector<std::vector<char>> renderableMap = m.getRenderableMap();
	int playerR = m.getPlayerRenderRow();
	int playerC = m.getPlayerCol();
	for (int i = 0; i < renderableMap.size(); i++) {
		for (int j = 0; j < renderableMap[i].size(); j++) {
			if (i == playerR && j == playerC) {
				std::cout << colorCharMap['P'];
			}
			else {
				std::cout << colorCharMap[renderableMap[i][j]];
			}
		}
		std::cout << std::endl;
	}
}

void ScreenRenderer::printLoadingScreen() {
	
	std::ifstream pokemonLogo("pokemon_logo.ans");
	std::string logoLine;

	while(getline(pokemonLogo, logoLine))
	{
		printToScreen(logoLine);
	}

	std::cout << "Welcome to Pokemon!" << std::endl
			  << "1. Start game" << std::endl
			  << "2. Exit game" << std::endl;

	char c = inputCharNoEnter();

	if (c == '2') exit(0);
}
