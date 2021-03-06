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

/* 
 * Constructor for ScreenRenderer.
 * 
 * Maps the various tiles to their ANSI colour codes.
 */
ScreenRenderer::ScreenRenderer() {
	colorCharMap.insert(std::pair<char, std::string> ('G', "\033[3;42;30m \033[0m"));
	colorCharMap.insert(std::pair<char, std::string> ('R', "\033[3;43;30m \033[0m"));
	colorCharMap.insert(std::pair<char, std::string> ('P', "\033[3;46;30m \033[0m"));
	colorCharMap.insert(std::pair<char, std::string> ('C', "\033[3;41;30m \033[0m"));
	colorCharMap.insert(std::pair<char, std::string> ('T', "\033[3;45;30m \033[0m"));
}

/*
 * Clears the screen.
 * Code courtesy of: https://stackoverflow.com/a/1348624
 */
void ScreenRenderer::clearScreen() {
	std::cout << "\033[2J\033[1;1H";
	std::cout << "\033[2J\033[1;1H";
}

/*
 * Prints a line to the screen.
 *
 * Parameters:
 * std::string s - string to print on screen.
 */
void ScreenRenderer::printToScreen(std::string s) {
	std::cout << s << std::endl;
}

/*
   To regulatetted printing on Battle Screen

   Parameters:
   string s1 - string to be printed on left side of screen
   string s2 - string to be printed on right side of screen
   int spaceWidth - integer storing the number of spaces between s1 and s2
   bool longBorder - true if extra spaces need to be printed before printing vertical border, false if extra spaces don't have to be printed for vertical border
*/
void ScreenRenderer::printLineOnBattleScreen(std::string s1, std::string s2, int spaceWidth, bool longBorder) {
	std::cout<<std::left<<std::setw(80)<< s1;
	for(int i=0;i< spaceWidth; i++)
		std::cout<<" ";
	std::cout<< std::left << std::setw(80) << s2;
	//in case string of image file is printed, then extra spaces need to be printed
	if(longBorder == true)
		std::cout<< std::right << std::setw(21) << "|" << std::endl;
	
	else
		std::cout<< std::right << "|" << std::endl;
}

/*
 * Inputs a character from the user in a non-blocking way.
 * Code courtesy of: https://stackoverflow.com/a/912184
 *
 * Parameters:
 * std::string s - Optional string to print while prompting for input.
 *
 * Returns:
 * char - key pressed by user.
 */
char ScreenRenderer::inputCharNoEnter(std::string s) {
	//Print specified string
	std::cout << s;

	//Set terminal to raw mode
	system("stty raw");

	//Get character from user
	char c = getchar();

	//Set terminal to normal mode
	system("stty cooked");
	
	std::cout << std::endl; 

	//Return the user's pressed character
	return c;
}

/*
 * Inputs a string from the user.
 *
 * Parameters:
 * std::string s - Optional string to print while prompting for input.
 *
 * Returns:
 * std::string - string entered by user.
 */
std::string ScreenRenderer::inputString(std::string s) {
	std::string input;

	//Print specified string
	std::cout << s;

	//Get user input and return it
	getline(std::cin, input);
	return input;
}

/*
 * Inputs an int from the user.
 *
 * Parameters:
 * std::string s - Optional string to print while prompting for input.
 *
 * Returns:
 * int - integer entered by user.
 */
int ScreenRenderer::inputInt(std::string s) {
	int input;

	std::cout << s;
	std::cin >> input;
    return input;	
}

/*
   Print horizontal border of '-'
*/
void ScreenRenderer::printHorizontalBorder() {
	for(int i=0;i<171;i++)
		std::cout<<"-";
	std::cout<<std::endl;
}


/*
   To print battle details and pokemon artwork during battle

   Parameters:
   Pokemon playerPokemon - Pokemon instance of player's current pokemon
   Pokemon opponentPokemon - Pokemon instance of opponent's current Pokemon
*/
void ScreenRenderer::printBattleScreen(Pokemon playerPokemon, Pokemon opponentPokemon)
{
	//spaces to be printed between strings when pokemon information is being printed
	int spaceWidthInfo = 10;
	//spaces to be printed between strings when string from pokemon artowrk file is being printed
	int spaceWidthImage = 30;

	//Number of lines in artwork files of player and opponent's pokemon
	int playerPokemonFileLines = 0, opponentPokemonFileLines = 0;

	std::ifstream playerPokemonImage, opponentPokemonImage;
	std::string tempPlayer, tempOpponent;

	std::string playerPokemonFile = playerPokemon.getName() + ".txt";
	std::string opponentPokemonFile = opponentPokemon.getName() + ".txt";

	//linking input streams to pokemon artwork files
	playerPokemonImage.open(playerPokemonFile);
	opponentPokemonImage.open(opponentPokemonFile);

	//printing basic details for player's reference
	printLineOnBattleScreen(playerPokemon.getName(), opponentPokemon.getName(), spaceWidthInfo);
	printLineOnBattleScreen("Level: " + std::to_string(playerPokemon.getLevel()), "Level: " + std::to_string(opponentPokemon.getLevel()), spaceWidthInfo);
	printLineOnBattleScreen("Type: " + std::string(1,playerPokemon.getType()),"Type: " + std::string(1,opponentPokemon.getType()), spaceWidthInfo);
	printLineOnBattleScreen("HP: " + std::to_string(playerPokemon.getHP()), "HP: " + std::to_string(opponentPokemon.getHP()), spaceWidthInfo);

	printLineOnBattleScreen();

	//printing player's pokemon's moves
	printLineOnBattleScreen("Moves: ");
	std::vector<Move> mvset = playerPokemon.getMoveset();
	printLineOnBattleScreen();
	for(int i=0; i< playerPokemon.getNumMoves(); i++)
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

	//if one artwork file has more number of lines, then print extra lines of bigger image first
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

	//print both images completely
	while(getline(playerPokemonImage,tempPlayer) && getline(opponentPokemonImage,tempOpponent))
	{
		printLineOnBattleScreen(tempPlayer, tempOpponent, spaceWidthImage, true);
	}

	playerPokemonImage.close();
	opponentPokemonImage.close();

	printLineOnBattleScreen();
	printLineOnBattleScreen();
}

/*
 * Prints the renderable section of the map (see Map.cpp for details).
 *
 * Parameters:
 * Map& m - Map to print the renderable section of the map from.
 */
void ScreenRenderer::printRenderableMap(Map& m) {
	//Get the renderable section of the map from the given Map instance
	std::vector<std::vector<char>> renderableMap = m.getRenderableMap();

	//Get the player's render row and column
	int playerR = m.getPlayerRenderRow();
	int playerC = m.getPlayerCol();

	//Loop through the renderable section of the map
	for (int i = 0; i < renderableMap.size(); i++) {
		for (int j = 0; j < renderableMap[i].size(); j++) {

			//If the current character is the player character, print the colour corresponding to P
			if (i == playerR && j == playerC) {
				std::cout << colorCharMap['P'];
			}

			//Else, print the correct colour from the colour map
			else {
				std::cout << colorCharMap[renderableMap[i][j]];
			}
		}
		std::cout << std::endl;
	}
}

/*
   Print screen to start game for user
*/
void ScreenRenderer::printLoadingScreen() {

	std::ifstream pokemonLogo("pokemon_logo.ans");
	std::string logoLine;

	//printing each line of Pokemon logo
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
