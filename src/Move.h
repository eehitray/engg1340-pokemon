//Move.h

#ifndef MOVE
#define MOVE
#include<string>

struct Move 
{
	std::string name;
	int damage;	//loss of health the move causes to opponent
	double hit;	//probability of move being successful
};

#endif
