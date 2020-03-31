#include <string>
#include <iostream>

#include "ScreenRenderer.h"

void ScreenRenderer::printToScreen(std::string s) {
	std::cout << s << std::endl;
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
