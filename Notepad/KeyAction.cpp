// KeyAction.cpp
/*
파일명칭 : KeyAction.cpp
기능 : 키 입력 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.08
*/
#include "KeyAction.h"
#include "NotepadForm.h"

KeyAction::KeyAction() {
	this->notepadForm = 0;
}

KeyAction::KeyAction(const KeyAction& source) {
	this->notepadForm = source.notepadForm;
}

KeyAction::~KeyAction() {
}

KeyAction& KeyAction::operator =(const KeyAction& source) {
	this->notepadForm = source.notepadForm;

	return *this;
}