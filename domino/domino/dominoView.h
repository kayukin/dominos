
// dominoView.h : интерфейс класса CdominoView
//

#pragma once


class CdominoView : public CView
{
protected: // создать только из сериализации
	CdominoView();
	DECLARE_DYNCREATE(CdominoView)

// Атрибуты
public:
	CdominoDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	CBitmap bitmaps[7];
	CDC dcBmp;
	const Tile* selectedTile = nullptr;
	void drawBackground(CDC* pDC);
	CButton m_button_Stock;
	CButton m_button_Pass;

// Реализация
public:
	virtual ~CdominoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
	void OnStockBtn();
};

#ifndef _DEBUG  // отладочная версия в dominoView.cpp
inline CdominoDoc* CdominoView::GetDocument() const
   { return reinterpret_cast<CdominoDoc*>(m_pDocument); }
#endif

