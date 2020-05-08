#ifndef MAP
#define MAP

#include <string>
#include <vector>

//Class to store map details and functionality.
class Map {
	//Number of trainers
	int numTrainers;

	//Coordinates of player
	int playerR, playerC;

	//Top and bottom render boundaries i.e. top-most and bottom-most rows to print
	int renderTopBound, renderBottomBound;

	//Number of rows in the map
	int height;

	//Number of columns in the map
	const int width;

	//Render height (number of rows to print at any given time)
	const int renderHeight;

	//The map - a vector of vector of characters containing the map itself
	std::vector<std::vector<char>> map;

	//Pointer to dynamically initialized array containing the rows of the trainers
	int* trainerRows;

	public:

	//Constructor for Map. Initializes map width to 40 and the screen render height to 41.
	Map(std::string, int, int);

	//Destructor for Map. Responsible for deallocating memory.
	~Map();

	//Get the tile/map character at the player's position.
	char getTileAtPlayerPos();

	//Get the renderable section of the map i.e. the section of the map that is printed to screen.
	std::vector<std::vector<char>> getRenderableMap();

	//Update the render boundaries.
	void updateRenderBounds();

	//Get the render width of the map.
	int getRenderWidth();

	//Get the render height of the map.
	int getRenderHeight();

	//Get the player's current row.
	int getPlayerRow();

	//Get the player's current *render* row, which is the row on which he is printed.
	int getPlayerRenderRow();
	
	//Get the player's current column.
	int getPlayerCol();

	//Set the player's current row.
	void setPlayerRow(int);

	//Set the player's current column.
	void setPlayerCol(int);

	//Move the player up by one tile.
	void moveUp();

	//Move the player down by one tile.
	void moveDown();
	
	//Move the player left by one tile.
	void moveLeft();
	
	//Move the player right by one tile.
	void moveRight();

	//Check if the player is right before a trainer.
	bool isBeforeTrainer(int);
	
	//Get the row of the trainer corresponding to position "level".
	int getNthTrainer(int);

	//Get the base Pokemon level for a region.
	int getBasePokemonLevel();

	//Get the number of trainers.
	int getNumTrainers();
};

#endif
