// LeftKeyAction.cpp
/*
파일명칭 : LeftKeyAction.cpp
기능 : 왼쪽 키를 눌렀을 때 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.08
*/
#include "LeftKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

LeftKeyAction::LeftKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

LeftKeyAction::~LeftKeyAction() {
}

void LeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();

	if (lineCurrent > 0 || noteCurrent == 0) {
		this->notepadForm->current->Previous();
	}
	else if (this->notepadForm->current->GetOnIsLine() == true) {
		noteCurrent = this->notepadForm->note->Previous();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->Last();
	}
	else {
		noteCurrent = this->notepadForm->note->Previous();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->Last();
		this->notepadForm->current->Previous();
	}
}