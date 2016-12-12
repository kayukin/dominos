// dominoDoc.cpp : реализация класса CdominoDoc
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "domino.h"
#endif

#include "dominoDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CdominoDoc

IMPLEMENT_DYNCREATE(CdominoDoc, CDocument)

BEGIN_MESSAGE_MAP(CdominoDoc, CDocument)
	END_MESSAGE_MAP()


// создание/уничтожение CdominoDoc

CdominoDoc::CdominoDoc(): game(nullptr)
{
	// TODO: добавьте код для одноразового вызова конструктора
}

CdominoDoc::~CdominoDoc()
{
	if (game != nullptr)
	{
		delete game;
	}
}

const vector<Tile>* CdominoDoc::getCurrentPlayerTiles() const
{
	return game->getCurrentPlayerTiles();
}

CString CdominoDoc::getCurrentPlayerName() const
{
	return game->getCurrentPlayerName();
}

void CdominoDoc::pushTileLeft(const Tile& tile)
{
	game->pushTileLeft(tile);
	UpdateAllViews(nullptr);
}

void CdominoDoc::pushTileRight(const Tile& tile)
{
	game->pushTileRight(tile);
	UpdateAllViews(nullptr);
}

const deque<Tile>* CdominoDoc::getTable() const
{
	return game->getTable();
}

void CdominoDoc::getFromStock()
{
	game->getFromStock();
	UpdateAllViews(nullptr);
}

BOOL CdominoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	if (game != nullptr)
	{
		delete game;
	}
	game = new Game();
	UpdateAllViews(nullptr);
	return TRUE;
}


// сериализация CdominoDoc

void CdominoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << *game;
	}
	else
	{
		ar >> *game;
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CdominoDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CdominoDoc::InitializeSearchContent()
{
	CString strSearchContent;
// Задайте содержимое поиска из данных документа. 
// Части содержимого должны разделяться точкой с запятой ";"

// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CdominoDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// диагностика CdominoDoc

#ifdef _DEBUG
void CdominoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CdominoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// команды CdominoDoc
