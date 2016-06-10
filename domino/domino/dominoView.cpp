// dominoView.cpp : реализация класса CdominoView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "domino.h"
#endif

#include "dominoDoc.h"
#include "dominoView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_STOCK_BUTTON 9999
#define ID_PASS_BUTTON 9998

#define BETWEEN(x, a, b) (x >= a && x <= b)
#define WIDTH_OF_TILES(n) (64*n+6*(n-2))
#define INDEX_OF_TILE(x) (x/70)

// CdominoView

IMPLEMENT_DYNCREATE(CdominoView, CView)

BEGIN_MESSAGE_MAP(CdominoView, CView)
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(ID_STOCK_BUTTON, OnStockBtn)
	END_MESSAGE_MAP()

// создание/уничтожение CdominoView
CString toString(int a)
{
	CString str;
	str.Format(L"%d", a);
	return str;
}

CdominoView::CdominoView()
{
	// TODO: добавьте код создания
	for (int i = 0; i < 7; i++)
	{
		bitmaps[i].LoadBitmap(IDB_BITMAP1 + i);
	}
	
}

CdominoView::~CdominoView()
{
}

BOOL CdominoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CdominoView::drawBackground(CDC* pDC)
{
	RECT rect;
	GetClientRect(&rect);
	CBrush brush(RGB(0, 100, 0));
	pDC->FillRect(&rect, &brush);
	pDC->MoveTo(0, 90);
	pDC->LineTo(rect.right, 90);
	pDC->MoveTo(0, 140);
	pDC->LineTo(rect.right, 140);
}

// рисование CdominoView

void CdominoView::OnDraw(CDC* pDC)
{
	CdominoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	drawBackground(pDC);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255, 255, 100));
	CRect currentName(30, 10, 120, 50), rScore(140, 10, 300, 50);
	pDC->DrawText(pDoc->getCurrentPlayerName(), currentName, 0);
	
	CString score = L"f:" + toString(pDoc->first_score()) + L"       s:" + toString(pDoc->second_score());
	pDC->DrawText(score, rScore, 0);


	if (dcBmp.m_hDC == nullptr)
	{
		dcBmp.CreateCompatibleDC(pDC);
	}
	const deque<Tile>* table = pDoc->getTable();
	int x = 30;
	for (deque<Tile>::const_iterator i = table->begin(); i != table->end(); ++i)
	{
		dcBmp.SelectObject(&(bitmaps[i->getHeadValue()]));
		pDC->BitBlt(x, 100, 32, 32, &dcBmp, 0, 0, SRCCOPY);
		x += 32;
		dcBmp.SelectObject(&(bitmaps[i->getTailValue()]));
		pDC->BitBlt(x, 100, 32, 32, &dcBmp, 0, 0, SRCCOPY);
		x += 34;
	}
	const vector<Tile>* currentPlayerTiles = pDoc->getCurrentPlayerTiles();
	x = 10;
	for (vector<Tile>::const_iterator i = currentPlayerTiles->begin(); i != currentPlayerTiles->end(); ++i)
	{
		if (selectedTile != nullptr)
		{
			if (*i == *selectedTile)
			{
				pDC->Draw3dRect(x - 3, 297, 70, 38, RGB(255, 0, 0), RGB(255, 0, 0));
			}
		}
		dcBmp.SelectObject(&(bitmaps[i->getHeadValue()]));
		pDC->BitBlt(x, 300, 32, 32, &dcBmp, 0, 0, SRCCOPY);
		x += 32;
		dcBmp.SelectObject(&(bitmaps[i->getTailValue()]));
		pDC->BitBlt(x, 300, 32, 32, &dcBmp, 0, 0, SRCCOPY);
		x += 38;
	}
}


// диагностика CdominoView

#ifdef _DEBUG
void CdominoView::AssertValid() const
{
	CView::AssertValid();
}

void CdominoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CdominoDoc* CdominoView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CdominoDoc)));
	return (CdominoDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CdominoView


void CdominoView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CdominoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (BETWEEN(point.y, 300, 332))
	{
		int numberOfTiles = pDoc->getCurrentPlayerTiles()->size();
		if (BETWEEN(point.x, 30, 30 + WIDTH_OF_TILES(numberOfTiles)))
		{
			selectedTile = &pDoc->getCurrentPlayerTiles()->at(INDEX_OF_TILE(point.x));
			Invalidate();
		}
	}
	else if (BETWEEN(point.y, 100, 132) && selectedTile != nullptr)
	{
		if (pDoc->getTable()->empty())
		{
			pDoc->pushTileRight(*selectedTile);
		}
		else if (point.x < 30)
		{
			pDoc->pushTileLeft(*selectedTile);
		}
		else if (point.x > WIDTH_OF_TILES(pDoc->getTable()->size()))
		{
			pDoc->pushTileRight(*selectedTile);
		}
		//selectedTile = nullptr;
	}
	CView::OnLButtonDblClk(nFlags, point);
}


void CdominoView::OnInitialUpdate()
{
	int x = 500;
	int y = 350;
	m_button_Stock.Create(L"Stock", WS_CHILD | WS_VISIBLE, CRect(x, y, x + 50, y + 30), this, ID_STOCK_BUTTON);
	m_button_Pass.Create(L"Pass", WS_CHILD | WS_VISIBLE, CRect(x + 60, y, x + 50 + 60, y + 30), this, ID_PASS_BUTTON);
	CView::OnInitialUpdate();
}

void CdominoView::OnStockBtn()
{
	CdominoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->getFromStock();
}
