#ifndef MAP
#define MAP

#include <string>
#include <vector>

class Map {
	int numTrainers;

	int playerR, playerC;
	int renderTopBound, renderBottomBound;

	int height;

	const int width;

	const int renderHeight;

	std::vector<std::vector<char>> map;

	int* trainerRows;

	public:

	Map(std::string, int, int);
	~Map();
	char getTileAtPlayerPos();
	std::vector<std::vector<char>> getRenderableMap();
	void updateRenderBounds();
	int getRenderWidth();
	int getRenderHeight();
	int getPlayerRow();
	int getPlayerRenderRow();
	int getPlayerCol();
	void setPlayerRow(int);
	void setPlayerCol(int);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	bool isBeforeTrainer(int);
	int getNthTrainer(int);
	int getBasePokemonLevel();
	int getNumTrainers();
};

#endif
