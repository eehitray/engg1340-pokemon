#ifndef MAP
#define MAP

#include <string>
#include <vector>

class Map {
	int playerR, playerC;
	int renderTopBound, renderBottomBound;

	int height;

	const int width;

	const int renderHeight;

	std::vector<std::vector<char>> map;
	public:

	Map(std::string);
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
};

#endif
