
// domino.h : главный файл заголовка для приложения domino
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CdominoApp:
// О реализации данного класса см. domino.cpp
//

class CdominoApp : public CWinApp
{
public:
	CdominoApp();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CdominoApp theApp;
