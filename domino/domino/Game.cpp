#include "stdafx.h"
#include "Game.h"


void Game::changePlayer()
{
	current_player_index = (current_player_index + 1) % players.size();
}

bool Game::checkOver()
{
	bool gameOver = false;
	if (players[current_player_index].getTiles()->empty())
	{
		gameOver = true;
	}
	else
	{
		bool hasCompatible = false;
		for (auto i = players[current_player_index].getTiles()->begin(); i != players[current_player_index].getTiles()->end(); ++i)
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
	
}

void Game::newRound()
{
	static int roundnumber;
	roundnumber++;
	AfxMessageBox(L"Next Round");
	clear();
	init();
}

void Game::init()
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
	Player first_player(first, L"First");
	Player second_player(second, L"Second");

	players.push_back(first_player);
	players.push_back(second_player);
	current_player_index = 0;
	table = new deque<Tile>();
}

Game::Game()
{
	init();
}


void Game::clear()
{
	delete table;
	delete stock;
}

Game::~Game()
{
	clear();
}

const vector<Tile>* Game::getCurrentPlayerTiles() const
{
	return players[current_player_index].getTiles();
}

CString Game::getCurrentPlayerName() const
{
	return players[current_player_index].getName();
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
		players[current_player_index].removeTile(tile);
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
		players[current_player_index].removeTile(tile);
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
		players[current_player_index].addTile(tile);
	}
}

void Game::Serialize(CArchive& archive)
{
	archive << current_player_index;
	archive << players.size();
	for (auto player : players)
	{
		player.Serialize(archive);
	}
	//table
	archive << table->size();
	for (auto i = table->begin(); i != table->end(); ++i)
	{
		archive << *i;
	}
	//stock
	archive << stock->size();
	for (auto i = stock->begin(); i != stock->end(); ++i)
	{
		archive << *i;
	}
}

void Game::Deserialize(CArchive& archive)
{
	archive >> current_player_index;
	players.clear();
	size_t size;
	archive >> size;
	for (size_t i = 0; i < size; ++i)
	{
		Player player;
		player.Deserialize(archive);
		players.push_back(player);
	}
	//table
	table->clear();
	archive >> size;
	for (size_t i = 0; i < size; ++i)
	{
		Tile tile;
		archive >> tile;
		table->push_back(tile);
	}
	//stock
	stock->clear();
	archive >> size;
	for (int i = 0; i < size; ++i)
	{
		Tile tile;
		archive >> tile;
		stock->push_back(tile);
	}
}
