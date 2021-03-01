// WrapLineCommand.cpp
/*
파일명칭 : WrapLineCommand.cpp
기능 : 한 줄 자동개행 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.08
*/
#include "WrapLineCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "GlyphFactory.h"
#include "Matrix.h"

WrapLineCommand::WrapLineCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

WrapLineCommand::~WrapLineCommand() {
}

void WrapLineCommand::Execute() {
	GlyphFactory glyphFactory;
	Glyph *line;
	Glyph *dummyLine;

	Long current = 0;
	Long noteIndex = 0;
	Long noteCurrent = this->notepadForm->note->GetCurrent();
	Long lineCurrent = this->notepadForm->current->GetCurrent();
	Long i = noteCurrent;

	bool onIsFirst = true;
	bool onIsLine = false; // 현재 줄은 당연히 실제(onIsLine이 true) 줄이고 자동개행이 완료 된 후 다음줄은 실제줄이니 그 전까지만 반복

	bool onIsGreaterThanScreen;
	// 1. 잘리는 줄의 개수를 구한다.(2020.01.22)
	onIsGreaterThanScreen = this->notepadForm->matrix->GetOnIsGreaterThanScreen();

	// 2. 잘리는 줄의 개수가 화면 크기보다 많으면 수직 스크롤바가 있는 것으로 지정한다.(2020.01.22)
	if (onIsGreaterThanScreen == true) {
		this->notepadForm->onIsVerticalScrollBar = TRUE;
	}

	// 1. 현재 줄을 자동개행한다.
	while (i < this->notepadForm->note->GetLength() && onIsLine != true) {
		line = this->notepadForm->note->GetAt(i);
		if (onIsFirst != true) {
			onIsLine = line->GetOnIsLine();
		}
		current = this->notepadForm->matrix->GetSplitCurrent(line);
		if (current > 0) {
			dummyLine = glyphFactory.Create((char*)"\n", false);
			line->Split(dummyLine, current);
			this->notepadForm->note->Add(i + 1, dummyLine);
		}
		onIsFirst = false;
		i++;
	}

	// 2. 종이의 현재 위치와 줄의 현재 위치를 계산한다.
	line = this->notepadForm->note->GetAt(noteCurrent);
	i = noteCurrent;
	while (i < this->notepadForm->note->GetLength() - 1 && lineCurrent > line->GetLength()) {
		noteCurrent++;
		lineCurrent -= line->GetLength();

		line = this->notepadForm->note->GetAt(i + 1);
		i++;
	}

	// 3. 계산된 위치로 이동한다.
	this->notepadForm->note->Move(noteCurrent);
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	this->notepadForm->current->Move(lineCurrent);
}