// Matrix.cpp
/*
ÆÄÀÏ¸íÄª : Matrix.cpp
±â´É : Çà·Ä Å¬·¡½º¸¦ ¸¸µç´Ù.
ÀÛ¼ºÀÚ : ±è½ÂÇö, Á¤¼º¿ø
ÀÛ¼ºÀÏÀÚ : 2021.01.07
*/
#include "Matrix.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Font.h"
#define ASCII 129

Matrix::Matrix() {
	this->notepadForm = 0;
	this->widths = 0;
	this->height = 0;
}

Matrix::Matrix(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;

	CDC *dc = this->notepadForm->GetDC();
	HFONT hFont;
	HFONT oldFont;
	hFont = CreateFontIndirect(&this->notepadForm->font->GetLogFont());
	oldFont = (HFONT)SelectObject(*dc, hFont);

	CSize cSize;
	this->widths = new Long[ASCII];

	Long i = 0;
	this->widths[0] = 0;
	i++;
	while (i < 9) {
		this->widths[i] = 0;
		i++;
	}

	cSize = dc->GetTextExtent(CString("        "));
	this->widths[i] = cSize.cx;
	i++;
	while (i < 32) {
		this->widths[i] = 0;
		i++;
	}
	while (i < ASCII - 2) {
		cSize = dc->GetTextExtent(CString((char)i));
		this->widths[i] = cSize.cx;
		i++;
	}
	this->widths[i] = 0;
	i++;

	cSize = dc->GetTextExtent(CString("¤¡"));
	this->widths[i] = cSize.cx;
	this->height = cSize.cy;

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->notepadForm->ReleaseDC(dc);
}

Matrix::Matrix(const Matrix& source) {
	this->notepadForm = source.notepadForm;
	this->widths = new Long[ASCII];
	Long i = 0;
	while (i < ASCII) {
		this->widths[i] = source.widths[i];
		i++;
	}
	this->height = source.height;
}

Matrix::~Matrix() {
	if (this->widths != 0) {
		delete this->widths;
	}
}

Long Matrix::GetWidth(Long index) {
	return this->widths[index];
}

Long Matrix::GetWidth(char(*text)) {
	CDC *dc = this->notepadForm->GetDC();
	HFONT hFont;
	HFONT oldFont;
	hFont = CreateFontIndirect(&this->notepadForm->font->GetLogFont());
	oldFont = (HFONT)SelectObject(*dc, hFont);

	CSize cSize = dc->GetTextExtent(text);

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->notepadForm->ReleaseDC(dc);

	return cSize.cx;
}

Long Matrix::GetX(Long current) { // ¹®Á¦ ÀÖÀ½ ¿µ¹®ÀÌ
	const char(*text);
	string str;

	CDC *dc = this->notepadForm->GetDC();
	HFONT hFont;
	HFONT oldFont;
	hFont = CreateFontIndirect(&this->notepadForm->font->GetLogFont());
	oldFont = (HFONT)SelectObject(*dc, hFont);

	CSize cSize;

	Long x = 0;
	Long width = 0;
	Long i = 0;
	while (i < this->notepadForm->current->GetCurrent()) {
		str = this->notepadForm->current->GetAt(i)->GetString();
		text = str.c_str();
		if (!(text[0] & 0x80)) {
			width = this->widths[(int)text[0]];
		}
		else if ((str >= "¤¡" && str <= "¤Ó") || (str >= "°¡" && str <= "ÆR")) {
			width = this->widths[ASCII - 1];
		}
		else {
			cSize = dc->GetTextExtent(text);
			width = cSize.cx;
		}
		x += width;
		i++;
	}

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->notepadForm->ReleaseDC(dc);

	return x;
}

Long Matrix::GetMaxX() {
	Long maxX;

	Glyph *line;// ¿©±â.

	CDC *dc = this->notepadForm->GetDC();
	HFONT hFont;
	HFONT oldFont;
	hFont = CreateFontIndirect(&this->notepadForm->font->GetLogFont());
	oldFont = (HFONT)SelectObject(*dc, hFont);

	CSize cSize;

	const char(*text);
	string str;

	Long currentMaxX = 0;
	Long width;
	Long i = 0;
	line = this->notepadForm->note->GetAt(i);

	Long j = 0;
	while (j < line->GetLength()) {
		str = line->GetAt(j)->GetString();
		text = str.c_str();
		if (!(text[0] & 0x80)) {
			width = this->widths[(int)text[0]];
		}
		else if ((str >= "¤¡" && str <= "¤Ó") || (str >= "°¡" && str <= "ÆR")) {
			width = this->widths[ASCII - 1];
		}
		else {
			cSize = dc->GetTextExtent(text);
			width = cSize.cx;
		}
		currentMaxX += width;
		j++;
	}
	maxX = currentMaxX;
	i++;
	while (i < this->notepadForm->note->GetLength()) {
		line = this->notepadForm->note->GetAt(i);
		currentMaxX = 0;
		j = 0;
		while (j < line->GetLength()) {
			str = line->GetAt(j)->GetString();
			text = str.c_str();
			if (!(text[0] & 0x80)) {
				width = this->widths[(int)text[0]];
			}
			else if ((str >= "¤¡" && str <= "¤Ó") || (str >= "°¡" && str <= "ÆR")) {
				width = this->widths[ASCII - 1];
			}
			else {
				cSize = dc->GetTextExtent(text);
				width = cSize.cx;
			}
			currentMaxX += width;
			j++;
		}
		if (maxX < currentMaxX) {
			maxX = currentMaxX;
		}

		i++;
	}

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->notepadForm->ReleaseDC(dc);

	return maxX;
}

Long Matrix::GetY(Long current) {
	return this->height * current;
}

Long Matrix::GetMaxY() {
	return this->height * this->notepadForm->note->GetLength();
}

Long Matrix::GetDistance(Glyph *line, Long startXPos, Long endXPos) {
	const char(*text);
	string str;

	CDC *dc = this->notepadForm->GetDC();
	HFONT hFont;
	HFONT oldFont;
	hFont = CreateFontIndirect(&this->notepadForm->font->GetLogFont());
	oldFont = (HFONT)SelectObject(*dc, hFont);

	CSize cSize;

	Long width;
	Long distance = 0;
	Long i = startXPos;
	while (i < endXPos && i < line->GetLength()) {
		str = line->GetAt(i)->GetString();
		text = str.c_str();
		if (!(text[0] & 0x80)) {
			width = this->widths[(int)text[0]];
		}
		else if ((str >= "¤¡" && str <= "¤Ó") || (str >= "°¡" && str <= "ÆR")) {
			width = this->widths[ASCII - 1];
		}
		else {
			cSize = dc->GetTextExtent(text);
			width = cSize.cx;
		}
		distance += width;
		i++;
	}

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->notepadForm->ReleaseDC(dc);

	return distance;
}

Long Matrix::GetLineCurrent(Long x) {
	Long lineCurrent = 0;
	Long width;
	Long totalWidth = 0;
	Long criticalPoint = 0;
	Long i = 0;

	CSize cSize;

	string str;
	const char(*text);

	CDC *dc = this->notepadForm->GetDC();
	HFONT hFont;
	HFONT oldFont;
	hFont = CreateFontIndirect(&this->notepadForm->font->GetLogFont());
	oldFont = (HFONT)SelectObject(*dc, hFont);

	if (this->notepadForm->current->GetLength() > 0) {
		str = this->notepadForm->current->GetAt(i)->GetString();
		text = str.c_str();
		if (!(text[0] & 0x80)) {
			width = this->widths[(int)text[0]];
		}
		else if ((str >= "¤¡" && str <= "¤Ó") || (str >= "°¡" && str <= "ÆR")) {
			width = this->widths[ASCII - 1];
		}
		else {
			cSize = dc->GetTextExtent(text);
			width = cSize.cx;
		}
		criticalPoint = totalWidth + width / 2 + 1;
		i++;
	}
	while (i < this->notepadForm->current->GetLength() && criticalPoint < x) {
		lineCurrent++;
		totalWidth += width;
		str = this->notepadForm->current->GetAt(i)->GetString();
		text = str.c_str();
		if (!(text[0] & 0x80)) {
			width = this->widths[(int)text[0]];
		}
		else if ((str >= "¤¡" && str <= "¤Ó") || (str >= "°¡" && str <= "ÆR")) {
			width = this->widths[ASCII - 1];
		}
		else {
			cSize = dc->GetTextExtent(text);
			width = cSize.cx;
		}
		criticalPoint = totalWidth + width / 2 + 1;
		i++;
	}
	if (i > 0 && criticalPoint < x) {
		lineCurrent++;
	}

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->notepadForm->ReleaseDC(dc);

	return lineCurrent;
}

Long Matrix::GetNoteCurrent(Long y) {
	Long noteCurrent = 0;
	Long i = 0;
	Long cirticalPoint = this->height;
	i++;
	while (i < this->notepadForm->note->GetLength() && cirticalPoint < y) {
		noteCurrent++;
		cirticalPoint += this->height;
		i++;
	}
	
	return noteCurrent;
}

Long Matrix::GetSplitCurrent(Glyph *line) {
	Long index = 0;
	RECT rect;
	this->notepadForm->GetClientRect(&rect);
	if (this->notepadForm->onIsVerticalScrollBar == TRUE) {
		rect.right -= GetSystemMetrics(SM_CXVSCROLL);
	}

	CSize cSize;

	string str;
	const char(*text);

	CDC *dc = this->notepadForm->GetDC();
	HFONT hFont;
	HFONT oldFont;
	hFont = CreateFontIndirect(&this->notepadForm->font->GetLogFont());
	oldFont = (HFONT)SelectObject(*dc, hFont);

	Long width = 0;
	Long i = 0;
	while (i < line->GetLength() && width <= rect.right) {
		str = line->GetAt(i)->GetString();
		text = str.c_str();
		if (!(text[0] & 0x80)) {
			width += this->widths[(int)text[0]];
		}
		else if ((str >= "¤¡" && str <= "¤Ó") || (str >= "°¡" && str <= "ÆR")) {
			width += this->widths[ASCII - 1];
		}
		else {
			cSize = dc->GetTextExtent(text);
			width += cSize.cx;
		}
		index = i;
		i++;
	}
	if (width <= rect.right) {
		index = -1;
	}

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->notepadForm->ReleaseDC(dc);

	return index;
}

Long Matrix::GetSplitCount(Glyph *line) {
	Long count = 0;

	bool onIsStop = false;

	RECT rect;
	this->notepadForm->GetClientRect(&rect);
	if (this->notepadForm->onIsVerticalScrollBar == TRUE) {
		rect.right -= GetSystemMetrics(SM_CXVSCROLL);
	}

	CSize cSize;

	string str;
	const char(*text);

	CDC *dc = this->notepadForm->GetDC();
	HFONT hFont;
	HFONT oldFont;
	hFont = CreateFontIndirect(&this->notepadForm->font->GetLogFont());
	oldFont = (HFONT)SelectObject(*dc, hFont);

	Long width;
	Long j;
	Long i = 0;
	while (i < line->GetLength() && onIsStop != true) {
		width = 0;
		j = i;
		while (j < line->GetLength() && width <= rect.right) {
			str = line->GetAt(j)->GetString();
			text = str.c_str();
			if (!(text[0] & 0x80)) {
				width += this->widths[(int)text[0]];
			}
			else if ((str >= "¤¡" && str <= "¤Ó") || (str >= "°¡" && str <= "ÆR")) {
				width += this->widths[ASCII - 1];
			}
			else {
				cSize = dc->GetTextExtent(text);
				width += cSize.cx;
			}
			j++;
		}
		if (width > rect.right) {
			count++;
			i = j - 2;
		}
		else {
			onIsStop = true;
		}
		i++;
	}

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->notepadForm->ReleaseDC(dc);

	return count;
}

Long Matrix::GetStringCount(char(*text)) {
	string tempText = text;
	Long length = (Long)tempText.length();
	Long textCount = 0;
	Long i = 0;
	while (i < length) {
		if (text[i] == '\r' || text[i] == '\n') {
			textCount++;
			if (i + 1 < length && text[i] == '\r' && text[i + 1] == '\n') {
				i++;
			}
		}
		else if (text[i] == 0x09 || text[i] >= 0x20 && text[i] < 0x7F) {
			textCount++;
		}
		else if (text[i] & 0x80) {
			textCount++;
			i++;
		}
		i++;
	}

	return textCount;
}

bool Matrix::GetOnIsGreaterThanScreen() {// (2020.01.22)
	bool ret = false;

	Long count = 0;

	Glyph *line;

	RECT rect;
	this->notepadForm->GetClientRect(&rect);
	if (this->notepadForm->onIsStatusBar == TRUE) {
		rect.bottom -= GetSystemMetrics(SM_CYHSCROLL);
	}

	CSize cSize;

	string str;
	const char(*text);

	CDC *dc = this->notepadForm->GetDC();
	HFONT hFont;
	HFONT oldFont;
	hFont = CreateFontIndirect(&this->notepadForm->font->GetLogFont());
	oldFont = (HFONT)SelectObject(*dc, hFont);

	Long width;
	Long k;
	Long j;
	Long i = 0;
	while (i < this->notepadForm->note->GetLength() && this->height * count < rect.bottom) {
		line = this->notepadForm->note->GetAt(i);
		j = 0;
		while (j < line->GetLength()) {
			width = 0;
			k = j;
			while (k < line->GetLength() && width <= rect.right) {
				str = line->GetAt(k)->GetString();
				text = str.c_str();
				if (!(text[0] & 0x80)) {
					width += this->widths[(int)text[0]];
				}
				else if ((str >= "¤¡" && str <= "¤Ó") || (str >= "°¡" && str <= "ÆR")) {
					width += this->widths[ASCII - 1];
				}
				else {
					cSize = dc->GetTextExtent(text);
					width += cSize.cx;
				}
				k++;
			}
			if (width > rect.right) {
				count++;
				j = k - 2;
			}
			j++;
		}
		count++;
		i++;
	}
	if (this->height * count > rect.bottom) {
		ret = true;
	}

	SelectObject(*dc, oldFont);
	DeleteObject(hFont);

	this->notepadForm->ReleaseDC(dc);

	return ret;
}

Matrix& Matrix::operator =(const Matrix& source) {
	this->notepadForm = source.notepadForm;

	if (this->widths != 0) {
		delete this->widths;
	}

	this->widths = new Long[ASCII];
	Long i = 0;
	while (i < ASCII) {
		this->widths[i] = source.widths[i];
		i++;
	}
	this->height = source.height;

	return *this;
}