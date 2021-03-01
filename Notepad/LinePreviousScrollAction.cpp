// LinePreviousScrollAction.cpp
/*
파일명칭 : LinePreviousScrollAction.cpp
기능 : 줄 이전으로 이동 스크롤 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.13
*/
#include "LinePreviousScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

LinePreviousScrollAction::LinePreviousScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

LinePreviousScrollAction::~LinePreviousScrollAction() {
}

void LinePreviousScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->PreviousUnit();
}

void LinePreviousScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->PreviousUnit();
}