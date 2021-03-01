// CtrlEndKeyAction.cpp
/*
파일명칭 : CtrlEndKeyAction.cpp
기능 : 컨트롤 엔드 키를 눌렀을 때 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.08
*/
#include "CtrlEndKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

CtrlEndKeyAction::CtrlEndKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CtrlEndKeyAction::~CtrlEndKeyAction() {
}

void CtrlEndKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Long index = this->notepadForm->note->Last();
	this->notepadForm->current = this->notepadForm->note->GetAt(index);
	this->notepadForm->current->Last();
}