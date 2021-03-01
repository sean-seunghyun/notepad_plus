// SelectAllCommand.cpp
/*
파일명칭 : SelectAllCommand.cpp
기능 : 전체 선택 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.26
*/
#include "SelectAllCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"

SelectAllCommand::SelectAllCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

SelectAllCommand::~SelectAllCommand() {
}

void SelectAllCommand::Execute() {
	Long noteCurrent;
	this->notepadForm->note->SelectAll(true);
	noteCurrent = this->notepadForm->note->Last();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	this->notepadForm->current->Last();
}