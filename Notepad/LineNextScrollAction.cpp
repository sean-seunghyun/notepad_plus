// LineNextScrollAction.cpp
/*
파일명칭 : LineNextScrollAction.cpp
기능 : 줄 다음으로 이동 스크롤 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.13
*/
#include "LineNextScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

LineNextScrollAction::LineNextScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

LineNextScrollAction::~LineNextScrollAction() {
}

void LineNextScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->NextUnit();
}

void LineNextScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->NextUnit();
}