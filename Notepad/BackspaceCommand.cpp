// BackspaceCommand.cpp
/*
파일명칭 : BackspaceCommand.cpp
기능 : 왼쪽 문자 삭제 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.25
*/
#include "BackspaceCommand.h"
#include "State.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include "resource.h"

BackspaceCommand::BackspaceCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->id = EditCommand::BACKSPACECOMMAND;
	this->onIsNew = true;
	this->onIsSelected = false;
	this->onIsEnter = false;
}

BackspaceCommand::~BackspaceCommand() {
}

void BackspaceCommand::Execute() {
	LONG noteCurrent;
	LONG noteLength;
	LONG lineCurrent;
	LONG lineLength;

	string text;

	Glyph *previousLine;
	Glyph *currentLine;
	Glyph *glyph;
	// + 선택된 곳이 있는지 확인한다.
	this->onIsSelected = this->notepadForm->note->GetOnIsSelected();

	//1. 자동개행모드이고, 선택되어 있는지 확인한다.
	noteCurrent = this->notepadForm->note->GetCurrent();
	if (this->notepadForm->onIsLineWrapping == TRUE && this->onIsSelected == true) {
		// 1.1. 선택된 줄들을 합친다.
		this->notepadForm->note->CombineSelectedLines();
	}
	else if (this->notepadForm->onIsLineWrapping == TRUE) {
		// 1.2. 현재 줄을 합친다.
		this->notepadForm->note->Combine(noteCurrent);
	}

	//2. 현재줄의 lineCurrent 값을 구한다.
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	lineCurrent = this->notepadForm->current->GetCurrent();

	// + 선택된 곳이 있으면 선택된 부분을 지운다.
	if (this->onIsSelected == true) {
		// 선택된 내용을 읽는다.
		text = this->notepadForm->note->GetSelectString();

		// 선택된 내용을 지운다.
		this->notepadForm->note->RemoveSelect();
	}
	//3. lineCurrent 값이 0보다 작거나 같으면
	else if (lineCurrent <= 0 && noteCurrent > 0) {
		this->onIsEnter = true;
		text = "\n";
		//3.1. 현재줄을 가져온다.
		currentLine = this->notepadForm->note->GetAt(noteCurrent);
		//3.2 이전줄을 가져온다.
		previousLine = this->notepadForm->note->GetAt(noteCurrent - 1);
		//3.3. 이전줄에서 현재줄을 합친다.
		previousLine->Combine(currentLine);

		//3.4. 노트에서 noteCurrent번째 줄을 없앤다.
		this->notepadForm->note->Remove(noteCurrent);
		noteCurrent = this->notepadForm->note->Previous();
	}
	//4. lineCurrent 값이 0보다 크면
	else if (lineCurrent > 0) {
		glyph = this->notepadForm->current->GetAt(lineCurrent - 1);
		text = glyph->GetString();
		this->notepadForm->current->Remove(lineCurrent - 1);
	}

	// 현재 위치를 읽고 위치로 이동한다.
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 이전 상태를 만든다.
	if (text != "") {
		this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);
		this->previousState = new State(lineCurrent, noteCurrent, text);
		this->onIsCommandSaving = true;
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}

	CString title;
	this->notepadForm->GetWindowText(title);
	if (title.GetAt(0) != '*') {
		title = "*" + title;
	}
	noteLength = this->notepadForm->note->GetLength();
	lineLength = this->notepadForm->current->GetLength();
	if ((noteLength > 1 || (noteLength <= 1 && lineLength > 0)) || this->onIsCommandSaving == true) {
		this->notepadForm->SetWindowTextA(title);
	}
}

void BackspaceCommand::UnExecute() {
	Glyph *previousNote;

	Long lineCurrent;
	Long noteCurrent;

	if (this->previousState != 0) {
		// 2.1. 이전 상태 정보를 읽어온다.
		previousNote = this->previousState->GetNote();
		lineCurrent = this->previousState->GetLineCurrent();
		noteCurrent = this->previousState->GetNoteCurrent();

		this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

		if (this->notepadForm->onIsLineWrapping == TRUE) {// 자동개행모드이면 한 줄 자동개행한다.(2021.02.09)
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->note->Combine(noteCurrent);
		}

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 2.2. 이전 상태의 내용을 추가한다.
		previousNote->SelectAll(true);
		this->notepadForm->note->Paste(previousNote);

		// 2.3. 메모지에서 현재 줄을 구한다.
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	if (this->previousState != 0 && this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

void BackspaceCommand::ReExecute() {
	Glyph *previousNote;
	Glyph *currentLine;
	Glyph *nextLine;

	string text;

	Long lineCurrent;
	Long noteCurrent;
	Long textCount;

	// 1. 이전 상태 정보를 읽어온다.
	previousNote = this->previousState->GetNote();
	text = previousNote->GetString();
	lineCurrent = this->previousState->GetLineCurrent();
	noteCurrent = this->previousState->GetNoteCurrent();

	// 2. 읽어온 위치로 이동한다.
	this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	lineCurrent = this->notepadForm->current->GetCurrent();

	// 3. 선택되어 있으면 내용을 선택한다.
	if (this->onIsSelected == true) {
		textCount = this->notepadForm->matrix->GetStringCount((char*)text.c_str());
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);
	}

	// 4. 자동개행모드이고 선택되어 있는지 확인한다.
	noteCurrent = this->notepadForm->note->GetCurrent();
	if (this->notepadForm->onIsLineWrapping == TRUE && this->onIsSelected == true) {
		// 4.1. 선택된 줄들을 합쳐준다.
		this->notepadForm->note->CombineSelectedLines();
	}
	else if (this->notepadForm->onIsLineWrapping == TRUE) {
		// 4.2. 현재 줄을 합친다.
		this->notepadForm->note->Combine(noteCurrent);
	}

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	lineCurrent = this->notepadForm->current->GetCurrent();

	// 5. 선택되어 있으면 선택된 내용을 지운다.
	if (this->onIsSelected == true) {
		this->notepadForm->note->RemoveSelect();
	}
	// 6. 개행문자이면 줄을 합친다.
	else if (text == "\n") {
		//6.1. 현재줄을 가져온다.
		currentLine = this->notepadForm->note->GetAt(noteCurrent);

		//6.2 다음줄을 가져온다.
		nextLine = this->notepadForm->note->GetAt(noteCurrent + 1);

		//6.3. 현재줄에서 다음줄을 합친다.
		currentLine->Combine(nextLine);

		//6.4. 노트에서 noteCurrent번째 줄을 없앤다.
		this->notepadForm->note->Remove(noteCurrent + 1);
		this->notepadForm->note->Previous();
	}
	// 7. 개행문자가 아니면 위치의 글자를 지운다.
	else {
		// 7.2 lineCurrent번째 글자를 지운다.
		this->notepadForm->current->Remove(lineCurrent);
	}

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 8. 자동개행모드이면 자동개행한다.
	if (this->previousState != 0 && this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

Long BackspaceCommand::GetLineCurrent() {
	Long ret = -1;
	if (this->previousState != 0) {
		ret = this->previousState->GetLineCurrent();
	}

	return ret;
}

Long BackspaceCommand::GetNoteCurrent() {
	Long ret = -1;
	if (this->previousState != 0) {
		ret = this->previousState->GetNoteCurrent();
	}

	return ret;
}

void BackspaceCommand::SetOnIsNew(bool onIsNew) {
	this->onIsNew = onIsNew;
}