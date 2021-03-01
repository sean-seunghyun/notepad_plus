// EditCommand.cpp
/*
파일명칭 : EditCommand.cpp
기능 : 편집 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.18
*/
#include "EditCommand.h"
#include "State.h"

EditCommand::EditCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->previousState = 0;
	this->id = ETCCOMMAND;
	this->onIsCommandSaving = false;
}

EditCommand::~EditCommand() {
	if (this->previousState != 0) {
		delete this->previousState;
	}
}