// Caret.cpp
/*
파일명칭 : Caret.cpp
기능 : 캐럿 클래스를 만든다.
작성자: 정성원
작성일자 : 2020.04.29
*/
#include "Caret.h"
#include "NotepadForm.h"
#include "CaretController.h"

Caret::Caret(CaretController *caretController) {
	this->caretController = caretController;
}

Caret::Caret(const Caret& source) {
	this->caretController = source.caretController;
}

Caret::~Caret() {
	// 1. 캐럿을 숨긴다.
	this->caretController->notepadForm->HideCaret();

	// 2. 캐럿을 없앤다.
	DestroyCaret();
}

void Caret::Create(Long width, Long height) {
	this->caretController->notepadForm->CreateSolidCaret(width, height);
}

void Caret::Move(Long x, Long y) {
	this->caretController->notepadForm->SetCaretPos(CPoint(x, y));
	this->caretController->notepadForm->ShowCaret();
}

void Caret::Hide() {
	this->caretController->notepadForm->HideCaret();
}

Caret& Caret::operator =(const Caret& source) {
	this->caretController = source.caretController;

	return *this;
}