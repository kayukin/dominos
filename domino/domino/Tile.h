#pragma once
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

class Tile
{
	int head;
	int tail;
public:
	Tile(int headValue, int tailValue);
	Tile() : Tile(0, 0){}
	int getHeadValue() const;
	int getTailValue() const;
	int getWeight() const;
	bool isDouble() const;
	static vector<Tile> createTiles();
	bool operator==(const Tile& second) const;
	void rotate();
	friend CArchive& operator<<(CArchive& ar, const Tile& tile);
	friend CArchive& operator>>(CArchive& ar, Tile& tile);
};
