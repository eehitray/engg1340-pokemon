//Move.h

#ifndef MOVE
#define MOVE
#include<string>

//Structure to store all details of a Pokemon's move
struct Move 
{
	//string storing name of Move
	std::string name;

	//integer storing damage (loss of HP) the Move causes to opponent on hit
	int damage;

	//double storing probability of Move being successful
	double hit;
};

#endif
