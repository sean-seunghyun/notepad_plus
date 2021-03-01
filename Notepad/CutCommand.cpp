// CutCommand.cpp
/*
파일명칭 : CutCommand.cpp
기능 : 잘라낸다 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.25
*/
#include "CutCommand.h"
#include "State.h"
#include "NotepadForm.h"
#include "Clipboard.h"
#include "Glyph.h"
#include "Matrix.h"
#include "resource.h"

CutCommand::CutCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CutCommand::~CutCommand() {
}

void CutCommand::Execute() {
	LONG lineCurrent;
	LONG noteCurrent;

	CString title;
	CString copyString;
	copyString = this->notepadForm->note->GetSelectString().c_str();

	noteCurrent = this->notepadForm->note->GetCurrent();
	if (copyString != "" && this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->note->CombineSelectedLines();
	}

	if (copyString != "") {
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);// 선택된 영역이 있어야 삭제하게끔 수정(2021.02.09)
		lineCurrent = this->notepadForm->current->GetCurrent(); // 지우고 난뒤 현재 위치를 읽게끔 수정(2021.02.09)

		this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);
		this->previousState = new State(lineCurrent, noteCurrent, (LPCTSTR)copyString);
		this->notepadForm->clipboard->Write(copyString);
		this->onIsCommandSaving = true;
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAPLINE);
	}

	this->notepadForm->GetWindowText(title);
	if (title.GetAt(0) != '*' && copyString != "") {
		title = "*" + title;
	}
	this->notepadForm->SetWindowTextA(title);
}

void CutCommand::UnExecute() {
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

void CutCommand::ReExecute() {
	Glyph *previousNote;

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

	// 3. 내용을 선택한다.
	textCount = this->notepadForm->matrix->GetStringCount((char*)text.c_str());
	this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

	// 4. 자동개행모드이고 선택되어 있으면 선택된 줄들을 합쳐준다.
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->note->CombineSelectedLines();
	}
	
	this->notepadForm->note->RemoveSelect();

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}