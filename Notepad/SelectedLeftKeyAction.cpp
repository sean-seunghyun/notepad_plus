// SelectedLeftKeyAction.cpp
/*
파일명칭 : SelectedLeftKeyAction.cpp
기능 : 선택되어 있을 때 왼쪽 키를 눌렀을 때 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.02.05
*/
#include "SelectedLeftKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

SelectedLeftKeyAction::SelectedLeftKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

SelectedLeftKeyAction::~SelectedLeftKeyAction() {
}

void SelectedLeftKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent;

	this->notepadForm->note->MoveToFirstSelectedCurrent();
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
}