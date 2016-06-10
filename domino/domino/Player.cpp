#include "stdafx.h"
#include "Player.h"


Player::Player(const vector<Tile>& tiles, CString the_name)
{
	hand = new vector<Tile>(tiles);
	name = the_name;
}


Player::~Player()
{
	delete hand;
}

const vector<Tile>* Player::getTiles() const
{
	return hand;
}

void Player::removeTile(const Tile& tile)
{
	hand->erase(remove(hand->begin(), hand->end(), tile), hand->end());
}

CString Player::getName() const
{
	return name;
}

void Player::addTile(const Tile& tile)
{
	hand->push_back(tile);
}

CArchive& operator<<(CArchive& ar, const Player& player)
{
	ar << player.name;
	ar << player.hand->size();
	for (auto i = player.hand->begin(); i != player.hand->end(); ++i)
	{
		ar << *i;
	}
	return ar;
}

CArchive& operator>>(CArchive& ar, Player& player)
{
	ar >> player.name;
	player.hand->clear();
	int size;
	ar >> size;
	for (int i = 0; i < size; ++i)
	{
		Tile tile;
		ar >> tile;
		player.hand->push_back(tile);
	}
	return ar;
}
