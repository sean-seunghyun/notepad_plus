// CopyCommand.cpp
/*
파일명칭 : CopyCommand.cpp
기능 : 복사한다 명령 클래스를 만든다.
작성자 : 정성원
작성일자 : 2020.07.03
*/
#include "CopyCommand.h"
#include "NotepadForm.h"
#include "Clipboard.h"
#include "Glyph.h"

CopyCommand::CopyCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CopyCommand::~CopyCommand() {
}

void CopyCommand::Execute() {
	CString copyString;

	copyString = this->notepadForm->note->GetSelectString().c_str();
	this->notepadForm->clipboard->Write(copyString);
}