// DateCommand.cpp
/*
파일명칭 : DateCommand.cpp
기능 : 날짜 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.02.01
*/
#include"DateCommand.h"
#include"State.h"
#include"NotepadForm.h"
#include"Glyph.h"
#include"Matrix.h"
#include"resource.h"

DateCommand::DateCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

DateCommand::~DateCommand() {
}
void DateCommand::Execute() { //삭제할 때
	LONG noteCurrent;
	LONG lineCurrent;

	char *charData = 0;

	CString dateTime;
	CString title;

	CTime time;

	//자동개행부분 수정!
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->note->Combine(noteCurrent);
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}


	noteCurrent = this->notepadForm->note->GetCurrent();
	lineCurrent = this->notepadForm->current->GetCurrent();

	time = CTime::GetCurrentTime();
	dateTime = time.Format("[%Y-%m-%d, %H:%M]");
	charData = dateTime.GetBuffer();

	//불러온 문자열 데이터를 이제 current 위치에 집어넣는다.
	if (charData[0] != '\0') {
		this->previousState = new State(lineCurrent, noteCurrent, charData);
		this->notepadForm->note->Paste(charData);
		this->onIsCommandSaving = true;
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}

	this->notepadForm->GetWindowText(title);
	if (title.GetAt(0) != '*') {
		title = "*" + title;
	}
	this->notepadForm->SetWindowTextA(title);
}

void DateCommand::UnExecute() {//삭제한 것을 실행취소할 때
	Glyph *previousNote;

	LONG noteCurrent;
	LONG lineCurrent;
	LONG textCount;

	CString text;

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->note->Combine(noteCurrent);
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	if (this->previousState != 0) {
		noteCurrent = this->previousState->GetNoteCurrent();
		lineCurrent = this->previousState->GetLineCurrent();
		previousNote = this->previousState->GetNote();
		text = CString(previousNote->GetString().c_str());

		this->notepadForm->note->Move(noteCurrent);
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->Move(lineCurrent);

		textCount = this->notepadForm->matrix->GetStringCount((LPSTR)(LPCTSTR)text);

		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);
		this->notepadForm->note->RemoveSelect();

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->Move(lineCurrent);
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

void DateCommand::ReExecute() {//되돌리기 할 때
	Glyph *previousNote;
	Long noteCurrent;
	Long lineCurrent;

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->note->Combine(noteCurrent);
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}


	if (this->previousState != 0) {
		noteCurrent = this->previousState->GetNoteCurrent();
		lineCurrent = this->previousState->GetLineCurrent();
		previousNote = this->previousState->GetNote();

		this->notepadForm->note->Move(noteCurrent);
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->Move(lineCurrent);

		previousNote->SelectAll(true);
		this->notepadForm->note->Paste(previousNote);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}