// LastScrollAction.cpp
/*
파일명칭 : LastScrollAction.cpp
기능 : 마지막으로 이동 스크롤 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.13
*/
#include "LastScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

LastScrollAction::LastScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

LastScrollAction::~LastScrollAction() {
}

void LastScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->Last();
}

void LastScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->Last();
}