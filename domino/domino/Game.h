#pragma once
#include "Player.h"
#include <deque>

class Game : public CObject
{
	int firstScore = 0;
	int secondScore = 0;
	vector<Player> players;
	deque<Tile>* table;
	vector<Tile>* stock;
	size_t current_player_index;
	void changePlayer();
	bool gameOver = false;
	bool checkOver();
	void countScores();
	void newRound();
	void init();
public:
	Game();
	void clear();
	~Game();
	const vector<Tile>* getCurrentPlayerTiles() const;
	CString getCurrentPlayerName() const;
	void pushTileLeft(Tile tile);
	void pushTileRight(Tile tile);
	const deque<Tile>* getTable() const;
	void getFromStock();


	int first_score() const
	{
		return firstScore;
	}

	int second_score() const
	{
		return secondScore;
	}

	void Serialize(CArchive& ar);
	void Deserialize(CArchive& ar);
};
