// DragBox.cpp
/*
파일명칭 : DragBox.cpp
기능 : 선택된 영역을 출력하는 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.18
*/
#include "DragBox.h"
#include "NotepadForm.h"
#include "Scroll.h"
#include "ScrollController.h"
#include "Matrix.h"
#include "Glyph.h"

DragBox::DragBox(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

DragBox::~DragBox() {
}

void DragBox::DragingOut(CDC *dc) {
	Long startLineCurrent;
	Long startNoteCurrent;
	Long prevStartNoteCurrent;
	Long endLineCurrent;
	Long endNoteCurrent;

	this->notepadForm->note->GetSelectRange(&startLineCurrent, &startNoteCurrent, &endLineCurrent, &endNoteCurrent);

	prevStartNoteCurrent = startNoteCurrent;
	if (startLineCurrent != endLineCurrent || startNoteCurrent != endNoteCurrent) {
		dc->SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
		dc->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

		CString text;
		Long criticalPoint = startNoteCurrent * this->notepadForm->matrix->GetHeight() + this->notepadForm->matrix->GetHeight();

		Glyph *line = this->notepadForm->note->GetAt(startNoteCurrent);
		if (startNoteCurrent != endNoteCurrent && criticalPoint >= this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent()) {
			text = CString(line->GetString(startLineCurrent, line->GetLength()).c_str());
		}
		else if (criticalPoint >= this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent()) {
			text = CString(line->GetString(startLineCurrent, endLineCurrent).c_str());
		}

		dc->TextOut(this->notepadForm->matrix->GetDistance(line, 0, startLineCurrent) - this->notepadForm->scrollController->GetHorizontalScroll()->GetCurrent(),
			(startNoteCurrent * this->notepadForm->matrix->GetHeight()) - this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent(), text);

		startNoteCurrent++;
		while (startNoteCurrent < endNoteCurrent &&
			criticalPoint < this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent() + this->notepadForm->scrollController->GetVerticalScroll()->GetPage()) {
			criticalPoint = startNoteCurrent * this->notepadForm->matrix->GetHeight() + this->notepadForm->matrix->GetHeight();
			if (criticalPoint >= this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent()) {
				line = this->notepadForm->note->GetAt(startNoteCurrent);
				text = CString(line->GetString(0, line->GetLength()).c_str());
				dc->TextOut(0 - this->notepadForm->scrollController->GetHorizontalScroll()->GetCurrent(),
					(startNoteCurrent * this->notepadForm->matrix->GetHeight()) - this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent(), text);
			}
			startNoteCurrent++;
		}

		if (prevStartNoteCurrent != endNoteCurrent && startNoteCurrent <= endNoteCurrent &&
			criticalPoint < this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent() + this->notepadForm->scrollController->GetVerticalScroll()->GetPage()) {
			line = this->notepadForm->note->GetAt(startNoteCurrent);
			text = CString(line->GetString(0, endLineCurrent).c_str());
			dc->TextOut(0 - this->notepadForm->scrollController->GetHorizontalScroll()->GetCurrent(),
				(startNoteCurrent * this->notepadForm->matrix->GetHeight()) - this->notepadForm->scrollController->GetVerticalScroll()->GetCurrent(), text);
		}
	}
}