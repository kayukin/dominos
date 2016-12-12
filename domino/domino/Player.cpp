#include "stdafx.h"
#include "Player.h"


Player::Player(const vector<Tile>& tiles, CString the_name)
{
	name = the_name;
	hand = tiles;
}


Player::~Player()
{
}

const vector<Tile>* Player::getTiles() const
{
	return &hand;
}

void Player::removeTile(const Tile& tile)
{
	hand.erase(remove(hand.begin(), hand.end(), tile), hand.end());
}

CString Player::getName() const
{
	return name;
}

void Player::addTile(const Tile& tile)
{
	hand.push_back(tile);
}

void Player::Serialize(CArchive& archive)
{
	archive << name;
	archive << hand.size();
	for (auto i = hand.begin(); i != hand.end(); ++i)
	{
		archive << *i;
	}
}

void Player::Deserialize(CArchive& archive)
{
	archive >> name;
	hand.clear();
	size_t size;
	archive >> size;
	for (int i = 0; i < size; ++i)
	{
		Tile tile;
		archive >> tile;
		hand.push_back(tile);
	}
}