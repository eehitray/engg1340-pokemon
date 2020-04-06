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

std::string Player::getPname()
{
	return pname;
}

std::vector<Pokemon> Player::getRoster()
{
	return roster;
}

void Player::setPname(std::string n)
{
	pname = n;
}

void Player::addtoRoster(Pokemon pok)
{
	roster.push_back(pok);
}

void Player::setRoster(std::vector<Pokemon> ros)
{
	roster = ros;
}

int Player::pokHealth()
{
	for(int i=0;i<3;i++)
	{
		if(roster[i].getHP() != 0)
			return 1;
	}
	return 0;
}
