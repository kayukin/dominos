
// domino.h : ������� ���� ��������� ��� ���������� domino
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CdominoApp:
// � ���������� ������� ������ ��. domino.cpp
//

class CdominoApp : public CWinApp
{
public:
	CdominoApp();


// ���������������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����������
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CdominoApp theApp;
