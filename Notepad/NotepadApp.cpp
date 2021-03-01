// NotepadApp.cpp
/*
파일명칭 : NotepadApp.cpp
기능 : 메모지철 앱 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2020.04.14
*/
#include "NotepadApp.h"
#include "NotepadForm.h"
#include <afxdisp.h>

NotepadApp notepadApp;

BOOL NotepadApp::InitInstance() {
	// Remainder of function definition omitted.
	CWinApp::InitInstance();
	
	NotepadForm *notepadForm;
	notepadForm = new NotepadForm;

	this->m_pMainWnd = notepadForm;

	SetRegistryKey("NotepadForm");
	LoadStdProfileSettings(8);

	notepadForm->Create(NULL, "제목 없음 - 메모장");
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CoInitialize(NULL);
	AfxEnableControlContainer();
	notepadForm->MoveWindow(400, 100, 900, 500);
	notepadForm->ShowWindow(SW_SHOW);
	notepadForm->UpdateWindow();

	return TRUE;
}