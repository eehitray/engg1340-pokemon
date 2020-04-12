//Player.cpp

#include "Pokemon.h"
#include "Move.h"
#include "Player.h"
#include "ScreenRenderer.h"
#include<vector>
#include<string>
#include <fstream>


Player::Player(std::string n, std::vector<Pokemon> pok)
{
	pname = n;
	roster = pok;
	r = -1;
	c = -1;
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

int Player::getRow() {
	return r;
}

int Player::getCol() {
	return c;
}

void Player::setRow(int newRow) {
	r = newRow;
}

void Player::setCol(int newCol) {
	c = newCol;
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

void Player::addXP(ScreenRenderer S, std::vector<int> pokxp)
{
	for(int i=0;i<pokxp.size();i++)
	{
		if(pokxp[i]!=0)
			roster[i].addXP(S, pokxp[i]);
	}
}

void Player::writeToFile(std::ofstream& f) {
	f << pname << std::endl
	  << r << std::endl
	  << c << std::endl;
	
	int rosterSize = (int) roster.size();

	f << rosterSize << std::endl;

	for (Pokemon p : roster) p.writeToFile(f);
}

void Player::readFromFile(std::ifstream& f) {
	f >> pname >> r >> c;

	int rosterSize;

	f >> rosterSize;

	roster.clear();

	for (int i = 0; i < rosterSize; i++) {
		roster.push_back(Pokemon(f));
	}
}

