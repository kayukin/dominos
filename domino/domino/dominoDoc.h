// dominoDoc.h : интерфейс класса CdominoDoc
//
#include "Game.h"


#pragma once


class CdominoDoc : public CDocument
{
protected: // создать только из сериализации
	CdominoDoc();
	DECLARE_DYNCREATE(CdominoDoc)

private:
	Game* game;
	// Атрибуты
public:
	// Операции
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
	// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Реализация
public:
	virtual ~CdominoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
