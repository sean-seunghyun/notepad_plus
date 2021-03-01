// StatusBarCommand.cpp
/*
파일명칭 : StatusBarCommand.cpp
기능 : 상태표시줄 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.02.01
*/
#include "StatusBarCommand.h"
#include "NotepadForm.h"
#include <afxext.h>
#include "resource.h"

StatusBarCommand::StatusBarCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

StatusBarCommand::StatusBarCommand(const StatusBarCommand& source) {
	this->notepadForm = source.notepadForm;
}

StatusBarCommand::~StatusBarCommand() {
}

void StatusBarCommand::Execute() {
	CMenu *cMenu = this->notepadForm->GetMenu();
	
	if (cMenu->GetMenuState(IDM_VIEW_STATUSBAR, MF_BYCOMMAND) != MF_CHECKED) {
		this->notepadForm->statusBar->SetWindowPos(&this->notepadForm->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_DRAWFRAME);
		this->notepadForm->ShowControlBar(this->notepadForm->statusBar, TRUE, FALSE);
		this->notepadForm->onIsStatusBar = TRUE;
		this->notepadForm->onIsComposing = FALSE;
		cMenu->CheckMenuItem(IDM_VIEW_STATUSBAR, MF_CHECKED | MF_BYCOMMAND);
	}
	else {
		this->notepadForm->ShowControlBar(this->notepadForm->statusBar, FALSE, FALSE);
		this->notepadForm->onIsStatusBar = FALSE;
		this->notepadForm->onIsComposing = FALSE;
		cMenu->CheckMenuItem(IDM_VIEW_STATUSBAR, MF_UNCHECKED | MF_BYCOMMAND);
	}
	RECT rect;
	this->notepadForm->GetClientRect(&rect);
	this->notepadForm->SendMessage(WM_SIZE, (WPARAM)SIZE_RESTORED, (LPARAM)MAKELPARAM(rect.right, rect.bottom));
}

StatusBarCommand& StatusBarCommand::operator =(const StatusBarCommand& source) {
	this->notepadForm = source.notepadForm;

	return *this;
}