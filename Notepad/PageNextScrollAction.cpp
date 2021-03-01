// PageNextScrollAction.cpp
/*
파일명칭 : PageNextScrollAction.cpp
기능 : 종이 다음으로 이동 스크롤 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.13
*/
#include "PageNextScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

PageNextScrollAction::PageNextScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

PageNextScrollAction::~PageNextScrollAction() {
}

void PageNextScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->NextPage();
}

void PageNextScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->NextPage();
}