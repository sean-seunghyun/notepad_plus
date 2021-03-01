// PagePreviousScrollAction.cpp
/*
파일명칭 : PagePreviousScrollAction.cpp
기능 : 종이 이전으로 이동 스크롤 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.13
*/
#include "PagePreviousScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

PagePreviousScrollAction::PagePreviousScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

PagePreviousScrollAction::~PagePreviousScrollAction() {
}

void PagePreviousScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->PreviousPage();
}

void PagePreviousScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->PreviousPage();
}