#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Map.h"

Map::Map(string file) : renderHeight(41) {
	width = 40;

	ifstream f(file);

	string temp;

	f >> height;
	f >> playerR >> playerC;

	renderTopBound = max(0, playerR - renderHeight / 2);
	renderBottomBound = min(height - 1, playerR + renderHeight / 2);

	while(getline(f, temp)) {
		vector<char> row(width);
		for (int i = 0; i < width; i++) cin >> row[i];
		map.push_back(row);
	}
}

std::vector<std::vector<char>> Map::getRenderableMap() {
	std::vector<std::vector<char>> renderableMap;

	for (int i = renderTopBound; i <= renderTopBound; i++) renderableMap.push_back(map[i]);

	return renderableMap;
}

int Map::getPlayerRow() { 
	return playerR;
}

int Map::getPlayerCol() {
	return playerC;
}

void Map::setPlayerRow(int row) {
	playerR = row;

	if (playerR >= height) playerR = height - 1;
	else if (playerR < 0) playerR = 0;
	
	renderTopBound = max(0, playerR - renderHeight / 2);
	renderBottomBound = min(height - 1, playerR + renderHeight / 2);
}

void Map::setPlayerCol(int col) {
	playerC = col;

	if (playerC >= width) playerC = width - 1;
	else if (playerC < 0) playerC = 0;
}

void Map::moveUp() {
	setPlayerRow(playerR - 1);
}

void Map::moveDown() {
	setPlayerRow(playerR + 1);
}

void Map::moveLeft() {
	setPlayerCol(playerC - 1);
}

void Map::moveRight() {
	setPlayerCol(playerC + 1);
}
