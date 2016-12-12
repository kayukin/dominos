#include "stdafx.h"
#include "Tile.h"
#include <random>


Tile::Tile(int headValue, int tailValue)
{
	head = headValue;
	tail = tailValue;
}

int Tile::getHeadValue() const
{
	return head;
}

int Tile::getTailValue() const
{
	return tail;
}

int Tile::getWeight() const
{
	return head + tail;
}

bool Tile::isDouble() const
{
	return head == tail;
}

vector<Tile> Tile::createTiles()
{
	std::random_device rd;
	std::mt19937 g(rd());
	vector<Tile> tiles;
	for (int i = 0; i <= 6; i++)
	{
		for (int j = i; j <= 6; j++)
		{
			tiles.push_back(Tile(i, j));
		}
	}
	shuffle(tiles.begin(), tiles.end(), g);
	return tiles;
}

bool Tile::operator==(const Tile & second) const
{
	return head == second.head && tail == second.tail;
}

void Tile::rotate()
{
	int temp = head;
	head = tail;
	tail = temp;
}

CArchive& operator<<(CArchive& ar, const Tile& tile)
{
	ar << tile.head;
	ar << tile.tail;
	return ar;
}

CArchive& operator>>(CArchive& ar, Tile& tile)
{
	ar >> tile.head;
	ar >> tile.tail;
	return ar;
}