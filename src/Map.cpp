#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Map.h"

Map::Map(std::string file) : width(40), renderHeight(41) {
	std::ifstream f(file);

	std::string temp;
	
	if (f) {
		f >> height;
		f >> playerR >> playerC;

		updateRenderBounds();

		while(getline(f, temp)) {
			std::vector<char> row(width);
			for (int i = 0; i < width; i++) f >> row[i];
			map.push_back(row);
		}
	}

	f.close();
}

std::vector<std::vector<char>> Map::getRenderableMap() {
	std::vector<std::vector<char>> renderableMap;

	for (int i = renderTopBound; i <= renderBottomBound; i++) {
		renderableMap.push_back(map[i]);
	} 

	return renderableMap;
}

void Map::updateRenderBounds() {
	renderTopBound = playerR - renderHeight / 2;
	renderBottomBound = playerR + renderHeight / 2;

	if (renderTopBound < 0) {
		renderTopBound = 0;
		renderBottomBound = renderHeight - 1;
	}
	else if (renderBottomBound >= height) {
		renderBottomBound = height - 1;
		renderTopBound = height - renderHeight + 1;
	}
}
int Map::getRenderWidth() {
	return width;
}

int Map::getRenderHeight() {
	return renderHeight;
}

int Map::getPlayerRow() { 
	return playerR;
}

int Map::getPlayerRenderRow() {
	return playerR - renderTopBound;
}

int Map::getPlayerCol() {
	return playerC;
}

void Map::setPlayerRow(int row) {
	playerR = row;

	if (playerR >= height) playerR = height - 1;
	else if (playerR < 0) playerR = 0;
	
	updateRenderBounds();
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
