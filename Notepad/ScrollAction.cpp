// ScrollAction.cpp
/*
파일명칭 : ScrollAction.cpp
기능 : 이동 스크롤 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.13
*/
#include "ScrollAction.h"

ScrollAction::ScrollAction(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

ScrollAction::~ScrollAction() {
}