// dominoDoc.h : ��������� ������ CdominoDoc
//
#include "Game.h"


#pragma once


class CdominoDoc : public CDocument
{
protected: // ������� ������ �� ������������
	CdominoDoc();
	DECLARE_DYNCREATE(CdominoDoc)

private:
	Game* game;
	// ��������
public:
	// ��������
public:
	const vector<Tile>* getCurrentPlayerTiles() const;
	CString getCurrentPlayerName() const;
	void pushTileLeft(const Tile& tile);
	void pushTileRight(const Tile& tile);
	const deque<Tile>* getTable() const;
	void getFromStock();
	int first_score() const
	{
		return game->first_score();
	}
	int second_score() const
	{
		return game->second_score();
	}
	// ���������������
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// ����������
public:
	virtual ~CdominoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ��������� ������� ����� ���������
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ��������������� �������, �������� ���������� ������ ��� ����������� ������
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
