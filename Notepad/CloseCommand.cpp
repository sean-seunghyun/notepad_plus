// CloseCommand.cpp
/*
파일명칭 : CloseCommand.cpp
기능 : 닫기 메뉴를 눌렀을 때 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.08
*/
#include "CloseCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"

CloseCommand::CloseCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CloseCommand::~CloseCommand() {
}

void CloseCommand::Execute() {
	this->notepadForm->PostMessage(WM_CLOSE);
}