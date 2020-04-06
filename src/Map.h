#ifndef MAP
#define MAP

#include <string>
#include <vector>

class Map {
	int playerR, playerC;
	int renderTopBound, renderBottomBound;

	int height, width;

	const int renderHeight;

	std::vector<std::vector<char>> map;
	public:

	Map(string);
	std::vector<std::vector<char>> getRenderableMap();
	int getPlayerRow();
	int getPlayerCol();
	void setPlayerRow(int);
	void setPlayerCol(int);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
}

#endif
