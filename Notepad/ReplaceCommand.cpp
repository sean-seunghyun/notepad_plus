// ReplaceCommand.cpp
/*
파일명칭 : ReplaceCommand.cpp
기능 : 바꾸기 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.22
*/
#include "ReplaceCommand.h"
#include "State.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include "GlyphFactory.h"
#include "FindReplaceDialog.h"
//#include <FindreplaceString.dlg>

ReplaceCommand::ReplaceCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->state = 0;
}

ReplaceCommand::~ReplaceCommand() {
}

void ReplaceCommand::Execute() {
	CString findString = AfxGetApp()->GetProfileString("NotepadSection", "FindString", "");
	CString replaceString = AfxGetApp()->GetProfileString("NotepadSection", "ReplaceString", "");
	CString findMessage;
	CString previousreplaceString;
	CString title;

	LONG findStringLen = this->notepadForm->matrix->GetStringCount((LPSTR)(LPCTSTR)findString);
	LONG replaceStringLen = this->notepadForm->matrix->GetStringCount((LPSTR)(LPCTSTR)replaceString);
	LONG prevLineCurrent = 0;
	LONG prevNoteCurrent = 0;
	LONG stateLineCurrent = 0;
	LONG stateNoteCurrent = 0;
	LONG startLineCurrent = 0;
	LONG startNoteCurrent = 0;
	LONG lineCurrent = 0;
	LONG noteCurrent = 0;

	Glyph *line = 0;

	this->onIsMatchCase = AfxGetApp()->GetProfileInt("NotepadSection", "MatchCase", -1);
	this->onIsWrapAround = AfxGetApp()->GetProfileInt("NotepadSection", "WrapAround", -1);

	bool onIsReplaced = false;
	bool onIsFindingNext = true; // 다음 찾을지 여부.

	// 1. 현재 선택된 것을 바꾸는지, 모두 바꾸는지 여부를 확인한다.
	if (this->notepadForm->pFindReplaceDialog != NULL) {
		this->onIsReplacedCurrent = true;
		if (this->notepadForm->pFindReplaceDialog->ReplaceAll() != 0) {
			this->onIsReplacedCurrent = false;
		}
		this->onIsMatchCase = ((FindReplaceDialog*)this->notepadForm->pFindReplaceDialog)->MatchCase();
		this->onIsWrapAround = !((FindReplaceDialog*)this->notepadForm->pFindReplaceDialog)->WrapAround();
	}

	// 2. 선택된 내용을 읽는다.
	previousreplaceString = this->notepadForm->note->GetSelectString().c_str();

	// 3. 찾는 내용과 선택된 내용이 같고, 현재 선택된 것을 바꿔야하면
	if (findString == previousreplaceString && findString != "" && this->onIsReplacedCurrent == true) {
		onIsReplaced = true; // 바뀐 여부를 참으로 한다.

		// 3.1. 선택된 내용을 지운다.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 3.2. 자동개행모드이면 메모지에서 현재 줄을 자동개행 푼다.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		}

		// 3.3. 찾는 내용을 추가한다.
		// + 상태의 위치를 구한다 (2021.01.28)
		startNoteCurrent = noteCurrent;
		startLineCurrent = this->notepadForm->current->GetCurrent();
		this->notepadForm->note->Paste((LPCTSTR)replaceString);
		this->notepadForm->note->SelectCount(startLineCurrent, startNoteCurrent, replaceStringLen);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 3.4. 자동개행모드이면 한 줄 자동개행 한다.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAPLINE);
		}
	}
	// 4. 전체 바꾸기이면
	if (this->onIsReplacedCurrent != true) {
		// 4.1. 처음 위치로 이동한다.
		this->notepadForm->note->First();
		this->notepadForm->current = this->notepadForm->note->GetAt(0);
		this->notepadForm->current->First();

		// 4.2. 메모지에서 다음으로 찾는다.
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext((LPCTSTR)findString, findStringLen, (bool)!this->onIsMatchCase);
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 4.3. 찾은 내용이 있을 동안 반복한다.
		while (this->notepadForm->onIsFound == TRUE) {
			onIsReplaced = true;
			onIsFindingNext = false;

			// 4.3.1. 선택된 내용을 지운다.
			this->notepadForm->note->RemoveSelect();
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

			lineCurrent = this->notepadForm->current->GetCurrent();

			// 4.3.2. 자동개행모드이면 메모지에서 현재 줄을 자동개행 푼다.
			if (this->notepadForm->onIsLineWrapping == TRUE) {
				this->notepadForm->note->Combine(noteCurrent);
				noteCurrent = this->notepadForm->note->GetCurrent();
				this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
			}

			// 4.3.3. 찾는 내용을 추가한다.
			this->notepadForm->note->Paste((LPCTSTR)replaceString);
			this->notepadForm->current->Move(lineCurrent);
			this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, replaceStringLen);

			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

			// 4.3.4. 메모지에서 다음으로 찾는다.
			this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext((LPCTSTR)findString, findStringLen, (bool)!this->onIsMatchCase);
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		}
		// 4.4. 바꾼 여부가 있으면
		if (onIsReplaced == true) {
			// 4.4.1. 자동개행 모드이면 전체 자동개행 한다.
			if (this->notepadForm->onIsLineWrapping == TRUE) {
				this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
			}
			// 4.4.2. 전체 선택 해제한다.
			this->notepadForm->note->SelectAll(false);
			// 4.4.3. 찾은 여부를 참으로 한다.
			this->notepadForm->onIsFound = TRUE;
		}
		// 4.5. 처음 위치로 이동한다.
		this->notepadForm->note->First();
		this->notepadForm->current = this->notepadForm->note->GetAt(0);
		this->notepadForm->current->First();
	}

	// 5. 다음으로 찾을지 여부가 참이면 메모지에서 다음으로 찾는다.
	if (findString != "" && onIsFindingNext == true) {
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext((LPCTSTR)findString, findStringLen, (bool)!this->onIsMatchCase);
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}
	// 6. 현재 위치를 저장한다.
	prevLineCurrent = this->notepadForm->current->GetCurrent();
	prevNoteCurrent = this->notepadForm->note->GetCurrent();
	// 7. 찾지 못하고 (전체 바꾸기가 아니고) 주위의 배치 여부가 참이면 (2021.02.18)
	if (findString != "" && this->notepadForm->onIsFound != TRUE && this->onIsReplacedCurrent == true && this->onIsWrapAround == 0) {
		// 7.1. 처음 위치의 첫 번째 칸으로 이동한다.
		noteCurrent = this->notepadForm->note->First();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->First();
		// 7.2. 메모지에서 다음으로 찾는다.
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext((LPCTSTR)findString, findStringLen, (bool)!this->onIsMatchCase);
	}
	// 8. 찾지 못하면 원래 위치로 돌아간다.
	if (this->notepadForm->onIsFound != TRUE) {
		this->notepadForm->note->Move(prevNoteCurrent);
		this->notepadForm->current = this->notepadForm->note->GetAt(prevNoteCurrent);
		this->notepadForm->current->Move(prevLineCurrent);
	}

	// 9. 바뀐 여부가 있으면 이전 상태와 현재 상태를 만든다.
	if (onIsReplaced == true) {
		stateLineCurrent = 0;
		stateNoteCurrent = 0;
		if (this->onIsReplacedCurrent == true) {
			prevLineCurrent = this->notepadForm->current->GetCurrent();
			prevNoteCurrent = this->notepadForm->note->GetCurrent();

			this->notepadForm->note->Move(startNoteCurrent);
			line = this->notepadForm->note->GetAt(startNoteCurrent);
			line->Move(startLineCurrent);

			this->notepadForm->note->GetCombineCurrent(&stateLineCurrent, &stateNoteCurrent);

			this->notepadForm->note->Move(prevNoteCurrent);
			this->notepadForm->current = this->notepadForm->note->GetAt(prevNoteCurrent);
			this->notepadForm->current->Move(prevLineCurrent);
		}

		this->previousState = new State(stateLineCurrent, stateNoteCurrent, (LPCTSTR)findString);
		this->state = new State(stateLineCurrent, stateNoteCurrent, (LPCTSTR)replaceString);
		this->onIsCommandSaving = true;

		this->notepadForm->GetWindowText(title);
		if (title.GetAt(0) != '*') {
			title = "*" + title;
		}
		this->notepadForm->SetWindowTextA(title);
	}
}

void ReplaceCommand::UnExecute() {
	string previousString;
	string currentString;

	LONG textCount;
	LONG noteCurrent;
	LONG lineCurrent;

	// 1. 현재 상태를 읽는다.
	currentString = this->state->GetNote()->GetString();
	noteCurrent = this->state->GetNoteCurrent();
	lineCurrent = this->state->GetLineCurrent();

	// 2. 이전 상태를 읽는다.
	previousString = this->previousState->GetNote()->GetString();

	// + 위치로 이동한다.
	this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 3. 한 단어를 바꿨으면
	if (this->onIsReplacedCurrent == true) {
		// 3.1. 자동개행 모드이면 한 줄을 합친다.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		}

		// 3.2. 현재 내용의 글자 수를 구한다.
		textCount = this->notepadForm->matrix->GetStringCount((char*)currentString.c_str());

		// 3.3. 글자만큼 선택한다.
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

		// 3.4. 선택한 내용을 지운다.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		lineCurrent = this->notepadForm->current->GetCurrent();
		
		// 3.5. 메모지에 추가한다.
		this->notepadForm->note->Paste(previousString);

		// 3.6. 글자만큼 선택한다.
		textCount = this->notepadForm->matrix->GetStringCount((char*)previousString.c_str());
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 3.7. 자동개행모드이면 한줄자동개행한다.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
		}
	}

	// 4. 전체 바꾸기이면
	if (this->onIsReplacedCurrent != true) {
		// 4.2. 메모지에서 다음으로 찾는다.
		textCount = this->notepadForm->matrix->GetStringCount((char*)currentString.c_str());
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext(currentString, textCount, (bool)!this->onIsMatchCase);

		// 4.3. 찾은 내용이 있을 동안 반복한다.
		while (this->notepadForm->onIsFound == TRUE) {
			// 4.3.1. 선택된 내용을 지운다.
			this->notepadForm->note->RemoveSelect();
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

			// 4.3.2. 자동개행모드이면 메모지에서 현재 줄을 자동개행 푼다.
			if (this->notepadForm->onIsLineWrapping == TRUE) {
				this->notepadForm->note->Combine(noteCurrent);
				noteCurrent = this->notepadForm->note->GetCurrent();
				this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
			}

			// 4.3.3. 찾는 내용을 추가한다.
			this->notepadForm->note->Paste(previousString);

			// 4.3.4. 메모지에서 다음으로 찾는다.
			this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext(currentString, textCount, (bool)!this->onIsMatchCase);
		}
		
		// 4.4. 자동개행 모드이면 전체 자동개행 한다.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
		}
		// 4.5. 전체 선택 해제한다.
		this->notepadForm->note->SelectAll(false);
		
		// 4.6. 처음 위치로 이동한다.
		this->notepadForm->note->First();
		this->notepadForm->current = this->notepadForm->note->GetAt(0);
		this->notepadForm->current->First();
	}
}

void ReplaceCommand::ReExecute() {
	string previousString;
	string currentString;

	LONG textCount;
	LONG noteCurrent;
	LONG lineCurrent;

	// 1. 현재 상태를 읽는다.
	currentString = this->previousState->GetNote()->GetString();
	noteCurrent = this->previousState->GetNoteCurrent();
	lineCurrent = this->previousState->GetLineCurrent();

	// 2. 이전 상태를 읽는다.
	previousString = this->state->GetNote()->GetString();

	// + 위치로 이동한다.
	this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 3. 한 단어를 바꿨으면
	if (this->onIsReplacedCurrent == true) {
		// 3.1. 자동개행 모드이면 한 줄을 합친다.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->note->Combine(noteCurrent);
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		}

		// 3.2. 현재 내용의 글자 수를 구한다.
		textCount = this->notepadForm->matrix->GetStringCount((char*)currentString.c_str());

		// 3.3. 글자만큼 선택한다.
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

		// 3.4. 선택한 내용을 지운다.
		this->notepadForm->note->RemoveSelect();
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		lineCurrent = this->notepadForm->current->GetCurrent();

		// 3.5. 메모지에 추가한다.
		textCount = this->notepadForm->matrix->GetStringCount((char*)previousString.c_str());
		this->notepadForm->note->Paste(previousString);

		// 3.6. 글자만큼 선택한다.
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);

		// 3.7. 자동개행모드이면 한줄자동개행한다.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
		}
	}

	// 4. 전체 바꾸기이면
	if (this->onIsReplacedCurrent != true) {
		// 4.2. 메모지에서 다음으로 찾는다.
		textCount = this->notepadForm->matrix->GetStringCount((char*)currentString.c_str());
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext(currentString, textCount, (bool)!this->onIsMatchCase);

		// 4.3. 찾은 내용이 있을 동안 반복한다.
		while (this->notepadForm->onIsFound == TRUE) {
			// 4.3.1. 선택된 내용을 지운다.
			this->notepadForm->note->RemoveSelect();
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

			// 4.3.2. 자동개행모드이면 메모지에서 현재 줄을 자동개행 푼다.
			if (this->notepadForm->onIsLineWrapping == TRUE) {
				this->notepadForm->note->Combine(noteCurrent);
				noteCurrent = this->notepadForm->note->GetCurrent();
				this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
			}

			// 4.3.3. 찾는 내용을 추가한다.
			this->notepadForm->note->Paste(previousString);

			// 4.3.4. 메모지에서 다음으로 찾는다.
			this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext(currentString, textCount, (bool)!this->onIsMatchCase);
		}

		// 4.4. 자동개행 모드이면 전체 자동개행 한다.
		if (this->notepadForm->onIsLineWrapping == TRUE) {
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
		}
		// 4.5. 전체 선택 해제한다.
		this->notepadForm->note->SelectAll(false);

		// 4.6. 처음 위치로 이동한다.
		this->notepadForm->note->First();
		this->notepadForm->current = this->notepadForm->note->GetAt(0);
		this->notepadForm->current->First();
	}
}