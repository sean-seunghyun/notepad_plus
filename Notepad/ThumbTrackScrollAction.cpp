// ThumbTrackScrollAction.cpp
/*
파일명칭 : ThumbTrackScrollAction.cpp
기능 : 위치로 이동 스크롤 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.13
*/
#include "ThumbTrackScrollAction.h"
#include "ScrollController.h"
#include "Scroll.h"

ThumbTrackScrollAction::ThumbTrackScrollAction(NotepadForm *notepadForm)
	: ScrollAction(notepadForm) {
}

ThumbTrackScrollAction::~ThumbTrackScrollAction() {
}

void ThumbTrackScrollAction::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetVerticalScroll()->Move(nPos);
}

void ThumbTrackScrollAction::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	this->notepadForm->scrollController->GetHorizontalScroll()->Move(nPos);
}