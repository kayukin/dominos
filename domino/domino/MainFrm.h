
// MainFrm.h : ��������� ������ CMainFrame
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // ������� ������ �� ������������
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ��������
public:

// ��������
public:

// ���������������
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����������
public:
	virtual ~CMainFrame();
	CStatusBar* getStatusbar() { return &m_wndStatusBar; }
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ���������� ����� ������ ��������� ����������
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ��������� ������� ����� ���������
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


