//Player.cpp

#include "Pokemon.h"
#include "Move.h"
#include "Player.h"
#include<vector>
#include<string>

Player::Player(std::string n, std::vector<Pokemon> pok)
{
	pname = n;
	roster = pok;
}

std::string getPname()
{
	return pname;
}

std::vector<Pokemon> getRoster()
{
	return roster;
}

void setPname(std::string n)
{
	panme = n;
}

void addtoRoster(Pokemon pok)
{
	roster.push_back(pok);
}
