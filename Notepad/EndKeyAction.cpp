// EndKeyAction.cpp
/*
파일명칭 : EndKeyAction.cpp
기능 : 엔드 키를 눌렀을 때 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.08
*/
#include "EndKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

EndKeyAction::EndKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

EndKeyAction::~EndKeyAction() {
}

void EndKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	Long noteLength = this->notepadForm->note->GetLength();
	Long lineLength = this->notepadForm->current->GetLength();

	Glyph *nextLine = this->notepadForm->note->GetAt(noteCurrent + 1);

	if (this->notepadForm->onIsLineWrapping == TRUE && noteCurrent + 1 < noteLength && lineCurrent >= lineLength &&
		nextLine->GetOnIsLine() != true) {
		noteCurrent = this->notepadForm->note->Next();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}
	this->notepadForm->current->Last();
}