// CharacterCommand.cpp
/*
파일명칭 : CharacterCommand.cpp
기능 : 1바이트 글자 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.26
*/
#include "CharacterCommand.h"
#include "State.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include "GlyphFactory.h"
#include "resource.h"

CharacterCommand::CharacterCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->onIsEnter = false;
}

CharacterCommand::~CharacterCommand() {
}

void CharacterCommand::Execute() {
	GlyphFactory glyphFactory;
	Glyph *line;
	Glyph *glyph;

	CString title;
	string text;

	Long lineCurrent;
	Long noteCurrent;
	Long lineLength;
	//Long prevLineCurrent;// 현재 줄의 current는 변한적이 없으므로 구할 필요 없음
	Long prevNoteCurrent;

	// 1. 글자를 읽는다.
	TCHAR *letter = this->notepadForm->GetLetter();

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

	// 5 개행 문자이면
	if (letter[0] == '\n' || letter[0] == '\r') {
		this->onIsEnter = true;
		// 5.1. 줄을 만든다.
		line = glyphFactory.Create((char*)&letter[0]);
		// 5.2. 현재 줄의 length와 current가 다르면 줄을 나눠준다.
		lineCurrent = this->notepadForm->current->GetCurrent();
		lineLength = this->notepadForm->current->GetLength();
		if (lineCurrent != lineLength) {
			this->notepadForm->current->Split(line, lineCurrent);
		}
		// 5.3. 노트에서 새 줄을 끼워넣는다.
		noteCurrent = this->notepadForm->note->GetCurrent();
		noteCurrent = this->notepadForm->note->Add(noteCurrent + 1, line);

		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}
	// 6. 개행 문자가 아니면
	else if ((letter[0] >= 32 && letter[0] < 127) || letter[0] == 9) {
		// 6.1. 글자를 만든다.
		glyph = glyphFactory.Create((char*)&letter[0]);
		// 6.2. 현재줄의 current와 current의 length가 같으면 현재 줄에서 추가한다.
		if (this->notepadForm->current->GetCurrent() == this->notepadForm->current->GetLength()) {
			this->notepadForm->current->Add(glyph);
		}
		else {
			//6.3.다르면 글자를 current번째에 끼워준다.
			this->notepadForm->current->Add(this->notepadForm->current->GetCurrent(), glyph);
		}
	}

	// 7. 현재 상태를 만든다.
	this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);
	if (this->onIsEnter == true) {
		// 8. 개행문자이면
		// 8.1. 현재 위치를 저장한다.
		// prevLineCurrent = this->notepadForm->current->GetCurrent();// 현재 줄의 current는 변한 적이 없으므로 구할 필요 없음
		prevNoteCurrent = this->notepadForm->note->GetCurrent();

		// 8.2. 노트에서 이전으로 이동한다.
		noteCurrent = prevNoteCurrent - 1;
		this->notepadForm->note->Move(noteCurrent);

		// 8.3. 줄에서 마지막 위치로 이동한다.
		line = this->notepadForm->note->GetAt(noteCurrent);
		line->Last();

		// 8.4. 합쳐진 위치를 미리 구한다.
		this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);

		// 8.5. 다시 원래 위치로 돌아온다.
		this->notepadForm->note->Move(prevNoteCurrent);
		this->notepadForm->current = this->notepadForm->note->GetAt(prevNoteCurrent);
		// this->notepadForm->current->Move(prevLineCurrent); // 현재 줄의 current는 변한 적이 없음.
	}
	else {
		lineCurrent--;
	}

	if ((letter[0] == '\n' || letter[0] == '\r') || ((letter[0] >= 32 && letter[0] < 127) || letter[0] == 9)) {
		this->state = new State(lineCurrent, noteCurrent, letter);
	}

	// 8. 자동개행모드이면 자동개행 해준다.
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}

	this->notepadForm->onIsComposing = FALSE;

	this->notepadForm->GetWindowText(title);
	if (this->state != 0 && title.GetAt(0) != '*') {
		title = "*" + title;
	}
	this->notepadForm->SetWindowTextA(title);
}

void CharacterCommand::UnExecute() {
	// 1. 현재 상태 정보를 읽어온다.
	Glyph *previousNote;
	Glyph *currentNote = this->state->GetNote();

	string text = currentNote->GetString();

	Long textCount;
	Long lineCurrent = this->state->GetLineCurrent();
	Long noteCurrent = this->state->GetNoteCurrent();
	Long i = 0;

	// 2. 위치로 이동하고, 선택한다.
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

	// 3. 선택된 내용을 지운다.
	this->notepadForm->note->RemoveSelect();
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 4. 이전 상태의 정보가 있으면
	if (this->previousState != 0) {
		// 4.1. 이전 상태 정보를 읽어온다.
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

		// 4.2. 이전 상태의 내용을 추가한다.
		previousNote->SelectAll(true);
		this->notepadForm->note->Paste(previousNote);

		// 4.3. 메모지에서 현재 줄을 구한다.
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

void CharacterCommand::ReExecute() {
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

	// 2. 현재 상태 정보를 읽어온다.
	currentNote = this->state->GetNote();
	lineCurrent = this->state->GetLineCurrent();
	noteCurrent = this->state->GetNoteCurrent();

	this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 5.4. 자동개행모드이면 한 줄을 합친다.
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->note->Combine(noteCurrent);
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	// 3. 상태의 내용을 추가한다.
	currentNote->SelectAll(true);
	this->notepadForm->note->Paste(currentNote);

	// 4. 메모지에서 현재 줄을 구한다.
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

Long CharacterCommand::GetLineCurrent() {
	Long ret = -1;
	if (this->state != 0) {
		ret = this->state->GetLineCurrent();
	}

	return ret;
}

Long CharacterCommand::GetNoteCurrent() {
	Long ret = -1;
	if (this->state != 0) {
		ret = this->state->GetNoteCurrent();
	}

	return ret;
}