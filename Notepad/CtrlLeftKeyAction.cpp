// CtrlLeftKeyAction.cpp
/*
파일명칭 : CtrlLeftKeyAction.cpp
기능 : 컨트롤 왼쪽 키를 눌렀을 때 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.08
*/
#include "CtrlLeftKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "resource.h"

CtrlLeftKeyAction::CtrlLeftKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CtrlLeftKeyAction::~CtrlLeftKeyAction() {
}

void CtrlLeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();;
	Long lineLength = this->notepadForm->current->GetLength();
	
	string text = "\0";
	bool onIsFirst = false;
	bool onIsSpaceOrTab = false;
	if (lineCurrent == 0 && noteCurrent > 0) {
		onIsFirst = true;
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->note->Combine(noteCurrent);
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	this->notepadForm->current->PreviousWord();

	lineCurrent = this->notepadForm->current->GetCurrent();
	if (lineCurrent < lineLength) {
		text = this->notepadForm->current->GetAt(lineCurrent)->GetString();
	}

	if (text == " " || text == "\t") {
		onIsSpaceOrTab = true;
	}

	noteCurrent = this->notepadForm->note->GetCurrent();
	if ((onIsSpaceOrTab == true && noteCurrent > 0) || onIsFirst == true) {
		noteCurrent = this->notepadForm->note->Previous();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->Last();
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}