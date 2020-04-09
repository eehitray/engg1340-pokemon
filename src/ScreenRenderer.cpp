#include <string>
#include <map>
#include <cstdlib>
#include <iostream>

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
}

void ScreenRenderer::printToScreen(std::string s) {
	std::cout << s << std::endl;
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
