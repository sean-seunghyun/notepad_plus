// RedoCommand.cpp
/*
파일명칭 : RedoCommand.cpp
기능 : 되돌리기 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.26
*/
#include "RedoCommand.h"
#include "NotepadForm.h"
#include "CommandHistory.h"

RedoCommand::RedoCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

RedoCommand::~RedoCommand() {
}

void RedoCommand::Execute() {
	this->notepadForm->commandHistory->Redo();
}