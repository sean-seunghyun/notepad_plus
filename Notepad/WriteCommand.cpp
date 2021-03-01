// WriteCommand.cpp
/*
파일명칭 : WriteCommand.cpp
기능 : 적기 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.26
*/
#include "WriteCommand.h"
#include "State.h"

WriteCommand::WriteCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->state = 0;
	this->id = EditCommand::WRITECOMMAND;
	this->onIsNew = true;
	this->onIsMore = true;
	this->onIsCommandSaving = true;
	this->onIsSelected = false;
}

WriteCommand::~WriteCommand() {
	if (this->state != 0) {
		delete this->state;
	}
}

void WriteCommand::SetOnIsNew(bool onIsNew) {
	this->onIsNew = onIsNew;
}