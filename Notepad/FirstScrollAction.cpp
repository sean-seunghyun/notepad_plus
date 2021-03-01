// FirstScrollAction.cpp
/*
파일명칭 : FirstScrollAction.cpp
기능 : 처음으로 이동 스크롤 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.13
*/
#include "FirstScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

FirstScrollAction::FirstScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

FirstScrollAction::~FirstScrollAction() {
}

void FirstScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->First();
}

void FirstScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->First();
}