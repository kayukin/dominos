#include "stdafx.h"
#include "Game.h"


void Game::changePlayer()
{
	if (currentPlayer == firstPlayer)
	{
		currentPlayer = secondPlayer;
	}
	else
	{
		currentPlayer = firstPlayer;
	}
}

bool Game::checkOver()
{
	bool gameOver = false;
	if (currentPlayer->getTiles()->empty())
	{
		gameOver = true;
	}
	else
	{
		bool hasCompatible = false;
		for (auto i = currentPlayer->getTiles()->begin(); i != currentPlayer->getTiles()->end(); ++i)
		{
			hasCompatible = hasCompatible || i->getHeadValue() == table->back().getTailValue() || i->getTailValue() == table->back().getTailValue();
			hasCompatible = hasCompatible || i->getHeadValue() == table->front().getHeadValue() || i->getTailValue() == table->front().getHeadValue();
		}
		if (!hasCompatible)
		{
			gameOver = true;
		}
	}
	if (gameOver)
	{
		countScores();
		newRound();
	}
	return gameOver;
}

void Game::countScores()
{
	if (currentPlayer == firstPlayer)
	{
		while (!stock->empty())
		{
			secondPlayer->addTile(stock->back());
			stock->pop_back();
		}
		for (auto i = secondPlayer->getTiles()->begin(); i != secondPlayer->getTiles()->end(); ++i)
		{
			firstScore += i->getWeight();
		}
	}
	else
	{
		while (!stock->empty())
		{
			firstPlayer->addTile(stock->back());
			stock->pop_back();
		}
		for (auto i = firstPlayer->getTiles()->begin(); i != firstPlayer->getTiles()->end(); ++i)
		{
			secondScore += i->getWeight();
		}
	}
}

void Game::newRound()
{
	static int roundnumber;
	roundnumber++;
	AfxMessageBox(L"Next Round");
	table->clear();
	vector<Tile> tiles = Tile::createTiles();
	vector<Tile> first, second;
	for (int i = 0; i < 6; i++)
	{
		first.push_back(tiles.back());
		tiles.pop_back();
		second.push_back(tiles.back());
		tiles.pop_back();
	}
	stock = new vector<Tile>(tiles);
	delete firstPlayer;
	delete secondPlayer;
	firstPlayer = new Player(first, L"First");
	secondPlayer = new Player(second, L"Second");
	currentPlayer = firstPlayer;
}

Game::Game()
{
	vector<Tile> tiles = Tile::createTiles();
	vector<Tile> first, second;
	for (int i = 0; i < 6; i++)
	{
		first.push_back(tiles.back());
		tiles.pop_back();
		second.push_back(tiles.back());
		tiles.pop_back();
	}
	stock = new vector<Tile>(tiles);
	firstPlayer = new Player(first, L"First");
	secondPlayer = new Player(second, L"Second");
	currentPlayer = firstPlayer;
	table = new deque<Tile>();
}


Game::~Game()
{
	delete firstPlayer;
	delete secondPlayer;
	delete table;
	delete stock;
}

const vector<Tile>* Game::getCurrentPlayerTiles() const
{
	return currentPlayer->getTiles();
}

CString Game::getCurrentPlayerName() const
{
	return currentPlayer->getName();
}

void Game::pushTileLeft(Tile tile)
{
	if (table->empty() || table->front().getHeadValue() == tile.getTailValue() || table->front().getHeadValue() == tile.getHeadValue())
	{
		if (!table->empty() && table->front().getHeadValue() == tile.getHeadValue())
		{
			tile.rotate();
		}
		table->push_front(tile);
		currentPlayer->removeTile(tile);
		if (!checkOver())
		{
			changePlayer();
		}
	}
}

void Game::pushTileRight(Tile tile)
{
	if (table->empty() || table->back().getTailValue() == tile.getHeadValue() || table->back().getTailValue() == tile.getTailValue())
	{
		if (!table->empty() && table->back().getTailValue() == tile.getTailValue())
		{
			tile.rotate();
		}
		table->push_back(tile);
		currentPlayer->removeTile(tile);
		if (!checkOver())
		{
			changePlayer();
		}
	}
}

const deque<Tile>* Game::getTable() const
{
	return table;
}

void Game::getFromStock()
{
	if (!stock->empty())
	{
		Tile tile = stock->back();
		stock->pop_back();
		currentPlayer->addTile(tile);
	}
}

CArchive& operator<<(CArchive& ar, const Game& game)
{
	ar << *game.firstPlayer;
	ar << *game.secondPlayer;
	ar << game.currentPlayer->getName();
	//table
	ar << game.table->size();
	for (auto i = game.table->begin(); i != game.table->end(); ++i)
	{
		ar << *i;
	}
	//stock
	ar << game.stock->size();
	for (auto i = game.stock->begin(); i != game.stock->end(); ++i)
	{
		ar << *i;
	}
	return ar;
}

CArchive& operator>>(CArchive& ar, Game& game)
{
	ar >> *game.firstPlayer;
	ar >> *game.secondPlayer;
	CString currentPlayerName;
	ar >> currentPlayerName;
	if (!game.firstPlayer->getName().Compare(currentPlayerName))
	{
		game.currentPlayer = game.firstPlayer;
	}
	else
	{
		game.currentPlayer = game.secondPlayer;
	}
	//table
	game.table->clear();
	int size;
	ar >> size;
	for (int i = 0; i < size; ++i)
	{
		Tile tile;
		ar >> tile;
		game.table->push_back(tile);
	}
	//stock
	game.stock->clear();
	ar >> size;
	for (int i = 0; i < size; ++i)
	{
		Tile tile;
		ar >> tile;
		game.stock->push_back(tile);
	}
	return ar;
}
