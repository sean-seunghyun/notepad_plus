// CtrlHomeKeyAction.cpp
/*
파일명칭 : CtrlHomeKeyAction.cpp
기능 : 컨트롤 홈 키를 눌렀을 때 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.08
*/
#include "CtrlHomeKeyAction.h"
#include "NotepadForm.h"
#include "Glyph.h"

CtrlHomeKeyAction::CtrlHomeKeyAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CtrlHomeKeyAction::~CtrlHomeKeyAction() {
}

void CtrlHomeKeyAction::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->notepadForm->note->First();
	this->notepadForm->current = this->notepadForm->note->GetAt(0);
;	this->notepadForm->current->First();
}