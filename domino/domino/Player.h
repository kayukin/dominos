#pragma once
#include "Tile.h"

class Player
{
	CString name;
	vector<Tile>* hand;
public:
	Player(const vector<Tile>& tiles, CString name);
	Player() :Player(vector<Tile>(), L"") {}
	~Player();
	const vector<Tile>* getTiles() const;
	void removeTile(const Tile& tile);
	CString getName() const;
	void addTile(const Tile& tile);
	friend CArchive& operator<<(CArchive& ar, const Player& player);
	friend CArchive& operator>>(CArchive& ar, Player& player);
};
