// DownKeyAction.cpp
/*
파일명칭 : DownKeyAction.cpp
기능 : 아래쪽 키를 눌렀을 때 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.08
*/
#include "DownKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"

DownKeyAction::DownKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

DownKeyAction::~DownKeyAction() {
}

void DownKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long x = this->notepadForm->matrix->GetX(this->notepadForm->current->GetCurrent());

	Long noteCurrent;
	noteCurrent = this->notepadForm->note->Next();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	Long lineCurrent;
	lineCurrent = this->notepadForm->matrix->GetLineCurrent(x);
	this->notepadForm->current->Move(lineCurrent);
}