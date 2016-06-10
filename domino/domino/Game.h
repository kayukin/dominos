#pragma once
#include "Player.h"
#include <deque>

class Game : public CObject
{
	Player* firstPlayer;
	int firstScore = 0;
	int secondScore = 0;
	Player* secondPlayer;
	deque<Tile>* table;
	vector<Tile>* stock;
	Player* currentPlayer;
	void changePlayer();
	bool gameOver = false;
	bool checkOver();
	void countScores();
	void newRound();
public:
	Game();
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

	friend CArchive& operator<<(CArchive& ar, const Game& game);
	friend CArchive& operator>>(CArchive& ar, Game& game);
};
