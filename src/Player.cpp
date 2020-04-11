//Player.cpp

#include "Pokemon.h"
#include "Move.h"
#include "Player.h"
#include "ScreenRenderer.h"
#include<vector>
#include <iostream>
#include<string>
#include <fstream>


Player::Player(std::string n, std::vector<Pokemon> pok)
{
	pname = n;
	roster = pok;
}

Player::Player(std::ifstream& f) {
	readFromFile(f);
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

bool Player::hasAlivePokemon()
{
	for(int i=0;i<roster.size();i++)
	{
		if(roster[i].getHP() != 0)
			return true;
	}
	return false;
}

void Player::printDetails(ScreenRenderer S)
{
	S.printToScreen(pname);
	for(int i=0;i<roster.size();i++)
	{
		roster[i].printDetails(S, true);
	}
}

void Player::writeToFile(std::ofstream& f) {
	f << pname << std::endl;
	
	int rosterSize = (int) roster.size();

	f << rosterSize << std::endl;

	for (Pokemon p : roster) p.writeToFile(f);
}

void Player::readFromFile(std::ifstream& f) {
	f >> pname;

	int rosterSize;

	f >> rosterSize;

	roster.clear();

	for (int i = 0; i < rosterSize; i++) {
		roster.push_back(Pokemon(f));
	}
}

