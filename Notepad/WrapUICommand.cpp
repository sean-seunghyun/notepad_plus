// WrapUICommand.cpp
/*
파일명칭 : WrapUICommand.cpp
기능 : 자동개행 UI 명령 클래스를 만든다.
작성자 : 정성원
작성일자 : 2020.10.14
*/
#include "WrapUICommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "CommandHistory.h"
#include "Scroll.h"
#include "ScrollController.h"
#include "resource.h"

WrapUICommand::WrapUICommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

WrapUICommand::~WrapUICommand() {
}

void WrapUICommand::Execute() {
	CMenu *cMenu = this->notepadForm->GetMenu();

	if (cMenu->GetMenuState(IDM_FORMAT_WRAPUI, MF_BYCOMMAND) != MF_CHECKED) {
		this->notepadForm->onIsLineWrapping = TRUE;
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
		cMenu->CheckMenuItem(IDM_FORMAT_WRAPUI, MF_CHECKED | MF_BYCOMMAND);
		cMenu->GetSubMenu(1)->EnableMenuItem(IDM_EDIT_MOVE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	}
	else {
		this->notepadForm->note->CombineAll();
		this->notepadForm->onIsLineWrapping = FALSE;
		cMenu->CheckMenuItem(IDM_FORMAT_WRAPUI, MF_UNCHECKED | MF_BYCOMMAND);
		cMenu->GetSubMenu(1)->EnableMenuItem(IDM_EDIT_MOVE, MF_BYCOMMAND | MF_ENABLED);
	}

	if (this->notepadForm->commandHistory != NULL) {
		delete this->notepadForm->commandHistory;
	}
	this->notepadForm->commandHistory = new CommandHistory(this->notepadForm);

	this->notepadForm->note->First();
	this->notepadForm->current = this->notepadForm->note->GetAt(0);
	this->notepadForm->current->First();
	this->notepadForm->scrollController->GetVerticalScroll()->First();
	this->notepadForm->scrollController->GetHorizontalScroll()->First();

	this->notepadForm->onIsComposing = FALSE;
}