// FindNextCommand.cpp
/*
파일명칭 : FindNextCommand.cpp
기능 : 다음 찾기 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.20
*/
#include "FindNextCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include <afxdlgs.h>

FindNextCommand::FindNextCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

FindNextCommand::~FindNextCommand() {
}

void FindNextCommand::Execute() {
	CString findString = AfxGetApp()->GetProfileString("NotepadSection", "FindString", "");
	LONG onIsMatchCase = AfxGetApp()->GetProfileInt("NotepadSection", "MatchCase", -1);
	LONG onIsWrapAround = AfxGetApp()->GetProfileInt("NotepadSection", "WrapAround", -1);

	LONG findStringLen;
	LONG startLineCurrent;
	LONG startNoteCurrent;
	LONG endLineCurrent;
	LONG endNoteCurrent;
	LONG prevLineCurrent = 0;
	LONG prevNoteCurrent = 0;
	LONG lineCurrent = this->notepadForm->current->GetCurrent();
	LONG noteCurrent = this->notepadForm->note->GetCurrent();

	// 1. 선택 범위를 구한다.
	this->notepadForm->note->GetSelectRange(&startLineCurrent, &startNoteCurrent, &endLineCurrent, &endNoteCurrent);

	// 2. 선택된 범위의 시작 위치가 현재 위치와 같으면
	if (startLineCurrent == lineCurrent && startNoteCurrent == noteCurrent) {
		// 2.1. 현재 위치를 저장한다.
		prevLineCurrent = lineCurrent;
		prevNoteCurrent = noteCurrent;
		// 2.2. 범위의 시작 위치로 이동한다.
		this->notepadForm->note->Move(endNoteCurrent);
		this->notepadForm->current = this->notepadForm->note->GetAt(endNoteCurrent);
		this->notepadForm->current->Move(endLineCurrent);
	}

	// 3. 찾는 내용의 글자 개수를 구한다.
	findStringLen = this->notepadForm->matrix->GetStringCount((LPSTR)(LPCTSTR)findString);

	// 4. 메모지에서 다음으로 찾는다.
	this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext((LPCTSTR)findString, findStringLen, (bool)!onIsMatchCase);

	// 5. 찾지 못하고 주위의 배치 여부가 참이면
	if (this->notepadForm->onIsFound != TRUE && findString != "" && onIsWrapAround == 0) {
		// 5.1. 처음 위치의 첫 번째 칸으로 이동한다.
		noteCurrent = this->notepadForm->note->First();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
		this->notepadForm->current->First();
		// 5.2. 메모지에서 다음으로 찾는다.
		this->notepadForm->onIsFound = (BOOL)this->notepadForm->note->FindNext((LPCTSTR)findString, findStringLen, (bool)!onIsMatchCase);
	}
	// 6. 찾지 못하면 원래 위치로 돌아간다.
	if (this->notepadForm->onIsFound != TRUE && onIsWrapAround == 0) {
		this->notepadForm->note->Move(prevNoteCurrent);
		this->notepadForm->current = this->notepadForm->note->GetAt(prevNoteCurrent);
		this->notepadForm->current->Move(prevLineCurrent);
	}

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
}