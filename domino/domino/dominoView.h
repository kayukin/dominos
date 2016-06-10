
// dominoView.h : ��������� ������ CdominoView
//

#pragma once


class CdominoView : public CView
{
protected: // ������� ������ �� ������������
	CdominoView();
	DECLARE_DYNCREATE(CdominoView)

// ��������
public:
	CdominoDoc* GetDocument() const;

// ��������
public:

// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	CBitmap bitmaps[7];
	CDC dcBmp;
	const Tile* selectedTile = nullptr;
	void drawBackground(CDC* pDC);
	CButton m_button_Stock;
	CButton m_button_Pass;

// ����������
public:
	virtual ~CdominoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
	void OnStockBtn();
};

#ifndef _DEBUG  // ���������� ������ � dominoView.cpp
inline CdominoDoc* CdominoView::GetDocument() const
   { return reinterpret_cast<CdominoDoc*>(m_pDocument); }
#endif

