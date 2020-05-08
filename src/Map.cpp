#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Map.h"

/*
 * Constructor for Map. Initializes map width to 40 and the screen render height to 41.
 *
 * Parameters:
 * std::string - filename of the file containing the map
 * int r - the player's row
 * int c - the player's column
 */
Map::Map(std::string file, int r, int c) : width(40), renderHeight(41) {
	//Open the map file
	std::ifstream f(file);

	std::string temp;
	
	//Ensure the file exists
	if (f) {

		//Read in the number of rows in the map, and the number of trainers.
		f >> height;
		f >> numTrainers;

		//Dynamically allocate memory for the rows at which trainers are located.
		trainerRows = new int[numTrainers];

		//Read the rows of the trainers
		for (int i = 0; i < numTrainers; i++) f >> trainerRows[i];

		//Read the player's default coordinates
		f >> playerR >> playerC;

		//Read in the actual map's characters into the map vector
		while(getline(f, temp)) {
			std::vector<char> row(width);
			for (int i = 0; i < width; i++) f >> row[i];
			map.push_back(row);
		}
	}

	//If player coordinates have been specified in the constructor, set the player coordinates to them
	if (r != -1 && c != -1) {
		playerR = r;
		playerC = c;
	}

	//Close the file
	f.close();

	//Update the bounds for printing the map to the screen
	updateRenderBounds();
}

/*
 * Destructor for Map. Responsible for deallocating memory.
 */
Map::~Map() {
	delete[] trainerRows;
}

/*
 * Get the tile/map character at the player's position.
 *
 * Returns:
 * char - the character at the player's position.
 */
char Map::getTileAtPlayerPos() {
	return map[playerR][playerC];
}

/*
 * Get the renderable section of the map i.e. the section of the map that is printed to screen.
 *
 * Returns:
 * std::vector<std::vector<char>> - a 2D vector containing the section the map to be printed.
 */
std::vector<std::vector<char>> Map::getRenderableMap() {
	std::vector<std::vector<char>> renderableMap;

	//Loop from the top of the render boundary to the bottom of the render boundary
	for (int i = renderTopBound; i <= renderBottomBound; i++) {

		//Add the rows to the renderableMap
		renderableMap.push_back(map[i]);
	} 

	//Return the renderable map
	return renderableMap;
}

/*
 * Update the render boundaries.
 */
void Map::updateRenderBounds() {
	/*
	 * The render boundaries are calculated such that the player is (vertically) in the centre of the screen at all times
	 * (except when near the top or the bottom of the map).
	 *
	 * As the render height is 41, this means that there are 20 characterrs above and 20 character below the player.
	 */
	renderTopBound = playerR - renderHeight / 2;
	renderBottomBound = playerR + renderHeight / 2;

	//If the top render boundary exceeds the actual map boundary, update the boundaries to stay within valid values.
	if (renderTopBound < 0) {
		renderTopBound = 0;
		renderBottomBound = renderHeight - 1;
	}
	
	//If the bottom render boundary exceeds the actual map boundary, update the boundaries to stay within valid values.
	else if (renderBottomBound >= height) {
		renderBottomBound = height - 1;
		renderTopBound = height - renderHeight + 1;
	}
}

/*
 * Get the render width of the map.
 *
 * Returns:
 * int - render width of the map.
 */
int Map::getRenderWidth() {
	return width;
}

/*
 * Get the render height of the map.
 *
 * Returns:
 * int - render height of the map.
 */
int Map::getRenderHeight() {
	return renderHeight;
}

/*
 * Get the player's current row.
 *
 * Returns:
 * int - player's current row.
 */
int Map::getPlayerRow() { 
	return playerR;
}

/*
 * Get the player's current *render* row, which is the row on which he is printed.
 *
 * Returns:
 * int - player's current render row.
 */
int Map::getPlayerRenderRow() {
	return playerR - renderTopBound;
}

/*
 * Get the player's current column.
 *
 * Returns:
 * int - player's current column.
 */
int Map::getPlayerCol() {
	return playerC;
}

/*
 * Set the player's current row.
 *
 * Parameters:
 * int row - the row to set the player's row to.
 */
void Map::setPlayerRow(int row) {
	playerR = row;

	//If the player's row is outside the map bounds, place the player within the bounds.
	if (playerR >= height) playerR = height - 1;
	else if (playerR < 0) playerR = 0;
	
	//Update the render bounds.
	updateRenderBounds();
}

/*
 * Set the player's current column.
 *
 * Parameters:
 * int col - the row to set the player's column to.
 */
void Map::setPlayerCol(int col) {
	playerC = col;

	//If the player's row is outside the map bounds, place the player within the bounds.
	if (playerC >= width) playerC = width - 1;
	else if (playerC < 0) playerC = 0;
}

/*
 * Move the player up by one tile.
 */
void Map::moveUp() {
	setPlayerRow(playerR - 1);
}


/*
 * Move the player down by one tile.
 */
void Map::moveDown() {
	setPlayerRow(playerR + 1);
}

/*
 * Move the player left by one tile.
 */
void Map::moveLeft() {
	setPlayerCol(playerC - 1);
}

/*
 * Move the player right by one tile.
 */
void Map::moveRight() {
	setPlayerCol(playerC + 1);
}

/*
 * Check if the player is right before a trainer.
 *
 * Returns:
 * bool - true if the player is before a trainer, false otherwise.
 */
bool Map::isBeforeTrainer(int playerLevel) {
	/*
	 * Start iterating from the player's level till the number of trainers. We iterate from
	 * the number of trainers so that the player does not have to fight trainers he has already
	 * defeated earlier.
	 */
	for (int i = playerLevel; i < numTrainers; i++) {
		
		//If the player is right below a trainer, return true
		if (playerR - 1 == trainerRows[i]) return true;
	}

	return false;
}

/*
 * Get the row of the trainer corresponding to position "level".
 *
 * Returns:
 * int - the row of the trainer corresponding to position "level".
 */
int Map::getNthTrainer(int level) {
	return trainerRows[level];
}

/*
 * Get the base Pokemon level for a region.
 * The base Pokemon level is calculated according to the region as follows:
 * If the player is below the 1st trainer, base Pokemon level = 2 * (1 - 1) + 1 = 1
 * If the player is below the 2nd trainer, base Pokemon level = 2 * (2 - 1) + 1 = 3
 * If the player is below the 3rd trainer, base Pokemon level = 2 * (3 - 1) + 1 = 5
 * and so on.
 *
 * Returns:
 * int - base Pokemon level for the region.
 */
int Map::getBasePokemonLevel() {
	for (int i = 0; i < numTrainers; i++)
		if (playerR >= trainerRows[i] - 1) return 2 * i + 1;

	return 2 * numTrainers + 1;
}

/*
 * Get the number of trainers.
 *
 * Returns:
 * int - number of trainers.
 */
int Map::getNumTrainers() {
	return numTrainers;
}
