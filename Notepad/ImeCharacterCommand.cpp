// ImeCharacterCommand.cpp
/*
파일명칭 : ImeCharacterCommand.cpp
기능 : 1바이트 글자 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.26
*/
#include "ImeCharacterCommand.h"
#include "State.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include "GlyphFactory.h"
#include "resource.h"

ImeCharacterCommand::ImeCharacterCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->onIsCommandSaving = false;
}

ImeCharacterCommand::~ImeCharacterCommand() {
}

void ImeCharacterCommand::Execute() {
	// 1. 글자를 만든다.
	GlyphFactory glyphFactory;
	Glyph *glyph;
	TCHAR letter[3];

	string text;

	Long lineCurrent;
	Long noteCurrent;

	// 2. 선택된 내용이 있는지 확인한다.
	this->onIsSelected = this->notepadForm->note->GetOnIsSelected();

	// 3. 자동개행모드이면 선택여부를 확인한다.
	noteCurrent = this->notepadForm->note->GetCurrent();
	if (this->notepadForm->onIsLineWrapping == TRUE && this->onIsSelected == true) {
		// 3.1. 선택되어 있으면 선택된 줄들을 합친다.
		this->notepadForm->note->CombineSelectedLines();
	}
	else if (this->notepadForm->onIsLineWrapping == TRUE) {
		// 3.2. 선택되어 있지 않으면 현재 줄을 합친다.
		this->notepadForm->note->Combine(noteCurrent);
	}
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 4. 선택된 내용이 있으면
	if (this->onIsSelected == true) {
		this->onIsCommandSaving = true;
		// 4.1. 선택된 내용을 읽는다.
		text = this->notepadForm->note->GetSelectString();

		// 4.2. 선택된 내용을 지운다.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);

		this->previousState = new State(lineCurrent, noteCurrent, text);
		this->onIsMore = false;
	}

	letter[0] = this->notepadForm->GetLetter()[0];
	letter[1] = this->notepadForm->GetLetter()[1];
	letter[2] = '\0';
	if (letter[0] != '\0') {
		this->onIsCommandSaving = true;

		glyph = glyphFactory.Create(letter);

		// 5. 메모지의 줄에서 없앤다.
		this->notepadForm->current->Remove(this->notepadForm->current->GetCurrent() - 1);

		// 6. 메모지의 줄에서 추가한다.
		if (this->notepadForm->current->GetCurrent() == this->notepadForm->current->GetLength()) {
			this->notepadForm->current->Add(glyph);
		}
		else {
			this->notepadForm->current->Add(this->notepadForm->current->GetCurrent(), glyph);
		}

		// 7. 상태를 만든다.
		this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);

		this->state = new State(lineCurrent - 1, noteCurrent, letter);
	}
	// 8. 자동개행모드이면 자동개행한다.
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}

	this->notepadForm->onIsComposing = FALSE;
}

void ImeCharacterCommand::UnExecute() {
	Glyph *previousNote;
	Glyph *currentNote;

	string text;

	Long textCount;
	Long lineCurrent;
	Long noteCurrent;
	Long i = 0;

	// 1. 현재 상태 정보가 있으면
	if (this->state != 0) {
		// 1.1. 현재 상태 정보를 읽어온다.
		currentNote = this->state->GetNote();
		text = currentNote->GetString();
		lineCurrent = this->state->GetLineCurrent();
		noteCurrent = this->state->GetNoteCurrent();

		// 1.2. 위치로 이동하고, 선택한다.
		this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		lineCurrent = this->notepadForm->current->GetCurrent();

		textCount = this->notepadForm->matrix->GetStringCount((char*)text.c_str());
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

		// + 자동개행모드이면 선택여부를 확인한다.
		noteCurrent = this->notepadForm->note->GetCurrent();
		if (this->notepadForm->onIsLineWrapping == TRUE && this->onIsSelected == true) {
			this->notepadForm->note->CombineSelectedLines();
		}
		else if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
		}
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 1.3. 선택된 내용을 지운다.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	// 2. 이전 상태의 정보가 있으면
	if (this->previousState != 0) {
		// 2.1. 이전 상태 정보를 읽어온다.
		previousNote = this->previousState->GetNote();
		lineCurrent = this->previousState->GetLineCurrent();
		noteCurrent = this->previousState->GetNoteCurrent();

		this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 자동개행모드이면 한 줄을 합친다.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		}

		// 2.2. 이전 상태의 내용을 추가한다.
		previousNote->SelectAll(true);
		this->notepadForm->note->Paste(previousNote);

		// 2.3. 메모지에서 현재 줄을 구한다.
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

void ImeCharacterCommand::ReExecute() {
	Glyph *previousNote;
	Glyph *currentNote;

	string text;

	Long textCount;
	Long lineCurrent;
	Long noteCurrent;
	Long i = 0;
	// 1. 이전 상태 정보가 있으면
	if (this->previousState != 0) {
		// 1.1.  이전 상태 정보를 읽어온다.
		previousNote = this->previousState->GetNote();
		text = previousNote->GetString();
		lineCurrent = this->previousState->GetLineCurrent();
		noteCurrent = this->previousState->GetNoteCurrent();

		this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		lineCurrent = this->notepadForm->current->GetCurrent();

		// 1.2. 매칭되는 글자를 선택한다.
		textCount = this->notepadForm->matrix->GetStringCount((char*)text.c_str());
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

		// + 자동개행모드이면 선택여부를 확인한다.
		noteCurrent = this->notepadForm->note->GetCurrent();
		if (this->notepadForm->onIsLineWrapping == TRUE && this->onIsSelected == true) {
			this->notepadForm->note->CombineSelectedLines();
		}
		else if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
		}
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 1.3. 선택된 내용을 지운다.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	// 2. 현재 상태 정보가 있으면
	if (this->state != 0) {
		// 2.1. 현재 상태 정보를 읽어온다.
		currentNote = this->state->GetNote();
		lineCurrent = this->state->GetLineCurrent();
		noteCurrent = this->state->GetNoteCurrent();

		this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 2.2. 자동개행모드이면 한 줄을 합친다.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		}

		// 2.3. 상태의 내용을 추가한다.
		currentNote->SelectAll(true);
		this->notepadForm->note->Paste(currentNote);

		// 2.4. 메모지에서 현재 줄을 구한다.
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

Long ImeCharacterCommand::GetLineCurrent() {
	Long ret = -1;
	if (this->state != 0) {
		ret = this->state->GetLineCurrent();
	}

	return ret;
}

Long ImeCharacterCommand::GetNoteCurrent() {
	Long ret = -1;
	if (this->state != 0) {
		ret = this->state->GetNoteCurrent();
	}

	return ret;
}