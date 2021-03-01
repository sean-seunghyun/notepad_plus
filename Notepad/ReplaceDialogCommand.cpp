// ReplaceDialogCommand.cpp
/*
파일명칭 : ReplaceDialogCommand.cpp
기능 : 바꾸기 대화상자 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.22
*/
#include "ReplaceDialogCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "FindReplaceDialog.h"
//#include <Findtext.dlg>

ReplaceDialogCommand::ReplaceDialogCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

ReplaceDialogCommand::~ReplaceDialogCommand() {
}

void ReplaceDialogCommand::Execute() {
	CString csFindString;
	CString csReplaceString;

	this->notepadForm->onIsOpeningFindReplace = TRUE;

	if (this->notepadForm->pFindReplaceDialog != 0) {
		this->notepadForm->pFindReplaceDialog->DestroyWindow();
	}

	csFindString = AfxGetApp()->GetProfileString("NotepadSection", "FindString", "");
	csReplaceString = AfxGetApp()->GetProfileString("NotepadSection", "ReplaceString", "");

	this->notepadForm->pFindReplaceDialog = new FindReplaceDialog;
	this->notepadForm->pFindReplaceDialog->Create(FALSE, csFindString, csReplaceString, 0, this->notepadForm);
	this->notepadForm->pFindReplaceDialog->ShowWindow(SW_SHOW);
}