// Note.cpp
/*
파일명칭 : Note.cpp
기능 : 메모지 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.20
*/
#include "Note.h"
#include "Glyph.h"
#include "GlyphFactory.h"

Note::Note(Long capacity)
	: Composite(capacity) {
}

Note::Note(const Note& source)
	: Composite(source) {
}

Note::~Note() {
}

Long Note::Add(Long current, Glyph *glyph) {
	Long index;
	index = this->glyphs.Insert(current, glyph);
	this->capacity++;
	this->length++;
	this->current = index;

	return this->current;
}

void Note::Paste(Glyph *dummyNote) {
	GlyphFactory glyphFactory;
	Glyph *dummyLine;
	Glyph *currentLine;
	Glyph *splitLine;
	Glyph *letter;
	Glyph *letterCopy;

	bool onIsSelected;
	
	Long i = 0;
	Long j;

	currentLine = this->glyphs.GetAt(this->current);
	splitLine = glyphFactory.Create((char*)"\r");
	currentLine->Split(splitLine, currentLine->GetCurrent());

	while (i < dummyNote->GetLength()) {
		dummyLine = dummyNote->GetAt(i);
		j = 0;
		while (j < dummyLine->GetLength()) {
			letter = dummyLine->GetAt(j);
			letterCopy = letter->Clone();
			currentLine->Add(currentLine->GetCurrent(), letterCopy);
			j++;
		}
		onIsSelected = dummyLine->GetOnIsSelected();
		currentLine->Select(onIsSelected);
		if (i + 1 < dummyNote->GetLength()) {
			currentLine = glyphFactory.Create((char*)"\r");
			this->glyphs.Insert(this->current + 1, currentLine);
			this->capacity++;
			this->length++;
			this->current++;
		}
		i++;
	}

	if (splitLine->GetLength() > 0) {
		currentLine->Combine(splitLine);
		currentLine->Select(false);
	}
	if (splitLine != 0) {
		delete splitLine;
	}
}

void Note::Paste(string text) {
	GlyphFactory glyphFactory;
	Glyph *currentLine = 0;
	Glyph *glyph;

	char character[2];

	Long lineCurrent;
	Long length = text.length();
	Long i = 0;

	currentLine = this->glyphs.GetAt(this->current);
	while (i < length) {
		character[0] = text[i];
		if (character[0] == '\r' || character[0] == '\n') {
			glyph = glyphFactory.Create(character);
			currentLine->Split(glyph, currentLine->GetCurrent());
			currentLine = glyph;
			this->current = this->glyphs.Insert(this->current + 1, glyph);
			this->capacity++;
			this->length++;
			if (i + 1 < length && text[i] == '\r' && text[i + 1] == '\n') {
				i++;
			}
		}
		else if (character[0] == 0x09 || character[0] >= 0x20 && character[0] < 0x7F) {
			glyph = glyphFactory.Create(character);
			lineCurrent = currentLine->GetCurrent();
			currentLine->Add(lineCurrent, glyph);
		}
		else if (character[0] & 0x80) {
			i++;
			character[1] = text[i];
			glyph = glyphFactory.Create(character);
			lineCurrent = currentLine->GetCurrent();
			currentLine->Add(lineCurrent, glyph);
		}
		i++;
	}
}

bool Note::RemoveSelect() {
	bool ret = false;
	bool onIsFound = false;
	bool onIsRemoved = false;
	bool onIsCurrentSelected = false;

	Long noteCurrent = 0;
	Long j;
	Long i = 0;

	Glyph *currentLine = 0;
	Glyph *line = 0;
	Glyph *character = 0;
	// 1. 종이의 마지막 줄보다 작고, 메모지 위치를 찾을 동안 반복한다.(메모지의 선택된 시작 위치를 찾는다)
	while (i < this->length && onIsFound != true) {
		// 1.1. 줄을 읽는다.
		line = this->glyphs.GetAt(i);
		j = 0;
		// 1.2. 줄의 마지막 칸보다 작고, 메모지 위치를 찾을 동안 반복한다.
		while (j < line->GetLength() && onIsFound != true) {
			// 1.2.1. 글자를 읽는다.
			character = line->GetAt(j);
			// 1.2.2. 글자가 선택되어 있으면 메모지 위치를 구한다.
			if (character->GetOnIsSelected() == true) {
				noteCurrent = i;
				onIsFound = true;
			}
			j++;
		}
		// 1.3. 줄의 마지막 칸이고 현재 줄이 선택되어 있고 찾지 못했으면 메모지 위치를 구한다.
		if (j >= line->GetLength() && line->GetOnIsSelected() == true && onIsFound != true) {
			noteCurrent = i;
			onIsFound = true;
		}
		i++;
	}
	// 2. 위치를 찾았으면 메모지에서 현재 위치로 이동하고, 현재 줄을 구한다.
	if (onIsFound == true) {
		ret = onIsFound;
		this->current = noteCurrent;
		currentLine = this->glyphs.GetAt(this->current);
		onIsCurrentSelected = currentLine->GetOnIsSelected();
	}
	// 3. 위치를 찾았으면 줄에서 선택된 글자들을 지운다.
	i = noteCurrent;
	if (i < this->length && onIsFound == true) {
		line = this->glyphs.GetAt(i);
		line->RemoveSelect();
		i++;
	}
	// 4. 마지막 줄보다 작고, 마지막 개행문자가 선택되어 있으면 반복한다.
	while (i < this->length && onIsCurrentSelected == true) {
		// 4.1. 줄을 읽는다.
		line = this->glyphs.GetAt(i);
		// 4.2. 줄에서 지운다.
		line->RemoveSelect();
		// 4.3. 현재줄의 개행문자가 선택되어 있지 않으면 선택 여부를 없음으로 한다.
		if (line->GetOnIsSelected() != true) {
			onIsCurrentSelected = false;
		}
		// 4.4. 현재 줄에서 줄을 합친다.
		currentLine->Combine(line);
		delete this->glyphs.GetAt(i);
		this->glyphs.Delete(i);
		this->capacity--;
		this->length--;
	}

	return ret;
}

void Note::Combine(Long current) { // 현재 줄의 자동개행된 줄들을 합치는 연산
	Glyph *line = this->glyphs.GetAt(current);
	Glyph *nextLine = 0;

	Long noteCurrent;
	Long lineCurrent = 0;
	Long i = 0;
	while (i <= current) {// 1. 현재 줄의 실제(onIsLine이 true인) 줄을 구한다.
		line = this->glyphs.GetAt(i);
		if (line->GetOnIsLine() == true) {
			noteCurrent = i;
		}
		i++;
	}

	i = noteCurrent;
	while (i < current) { // 2. 합치고 난 뒤 이동할 칸을 미리 구한다.
		line = this->glyphs.GetAt(i);
		lineCurrent += line->GetLength();
		i++;
	}
	if (i < this->length) {
		line = this->glyphs.GetAt(i);
		lineCurrent += line->GetCurrent();
	}

	i = noteCurrent; // 3. 현재 줄의 자동개행된 줄만 합쳐준다.
	if (this->length > i + 1) {
		line = this->glyphs.GetAt(i);
		nextLine = this->glyphs.GetAt(i + 1);
	}
	while (this->length > i + 1 && nextLine->GetOnIsLine() != true) {
		line->Combine(nextLine);
		line->Select(nextLine->GetOnIsSelected()); // 다음 줄의 선택여부를 확인하여 선택한다.(2021.01.18)
		delete nextLine;
		this->glyphs.Delete(i + 1);
		nextLine = this->glyphs.GetAt(i + 1);
		this->capacity--;
		this->length--;
	}
	// 4. 합치고 난 뒤 위치로 이동한다.
	this->current = noteCurrent;
	this->glyphs.GetAt(this->current)->Move(lineCurrent);
}

void Note::CombineSelectedLines() {
	Glyph *line;
	Glyph *nextLine;
	Glyph *glyph;

	bool onIsStop = false;
	bool onIsSelected = false;
	bool onIsCurrentLineSelected = false;

	Long startSelectedtNoteCurrent = -1;
	Long noteCurrentForLineCurrent;
	Long noteCurrent = -1;
	Long lineCurrent = 0;
	Long j;
	Long i = 0;
	// 1. 선택된 줄의 시작 위치를 찾는다.
	while (i < this->length && onIsStop != true) {
		line = this->glyphs.GetAt(i);
		j = 0;
		while (j < line->GetLength() && onIsStop != true) {
			glyph = line->GetAt(j);
			if (glyph->GetOnIsSelected() == true) {
				startSelectedtNoteCurrent = i;
				onIsStop = true;
			}
			j++;
		}
		if (line->GetOnIsSelected() == true) {
			startSelectedtNoteCurrent = i;
			onIsStop = true;
		}
		i++;
	}

	// 2. 합치고 난 뒤의 칸을 구하기 위한 줄의 위치와 / 합치고 난뒤의 줄 위치를 / 미리 구한다.
	i = 0;
	while (i <= this->current) {
		line = this->glyphs.GetAt(i);
		if (line->GetOnIsLine() == true) {
			noteCurrentForLineCurrent = i;
			noteCurrent++;
		}
		i++;
	}

	// 3. 합치고 난 뒤의 칸을 구한다.
	i = noteCurrentForLineCurrent;
	while (i < this->current) {
		line = this->glyphs.GetAt(i);
		lineCurrent += line->GetLength();
		i++;
	}
	if (i < this->length) {
		line = this->glyphs.GetAt(i);
		lineCurrent += line->GetCurrent();
	}

	// 4. 선택된 자동개행된 줄들을 합친다.
	// ===================================
	// 1. 선택된 첫 번째 줄이 있으면
	i = startSelectedtNoteCurrent;
	if (startSelectedtNoteCurrent >= 0 && i < this->length) {
		// 1.1. 선택된 줄과 다음줄을 구한다.
		line = this->glyphs.GetAt(i);
		nextLine = this->glyphs.GetAt(i + 1);

		// 1.2. 다음줄을 합친다.
		while (this->length > i + 1 && nextLine->GetOnIsLine() != true) {
			line->Combine(nextLine);
			onIsSelected = nextLine->GetOnIsSelected();
			line->Select(onIsSelected);
			delete nextLine;
			this->glyphs.Delete(i + 1);
			nextLine = this->glyphs.GetAt(i + 1);
			this->capacity--;
			this->length--;
		}
		// 1.3. 합쳐진 줄의 선택 여부를 구한다.
		onIsCurrentLineSelected = line->GetOnIsSelected();
	}

	// 2. 선택된 줄이 있을동안 줄을 합친다.
	while (i < this->length - 1 && onIsCurrentLineSelected == true) {
		line = this->glyphs.GetAt(i);
		nextLine = this->glyphs.GetAt(i + 1);
		while (this->length > i + 1 && nextLine->GetOnIsLine() != true) {
			line->Combine(nextLine);
			onIsSelected = nextLine->GetOnIsSelected();
			line->Select(onIsSelected);
			delete nextLine;
			this->glyphs.Delete(i + 1);
			nextLine = this->glyphs.GetAt(i + 1);
			this->capacity--;
			this->length--;
		}
		onIsCurrentLineSelected = line->GetOnIsSelected();
		i++;
	}
	// ===================================
	// 5. 구한 위치로 이동한다.
	this->current = noteCurrent;
	line = this->glyphs.GetAt(this->current);
	line->Move(lineCurrent);
}

void Note::CombineAll() { // 모든 줄의 자동개행된 줄들을 합친다.
	Glyph *line;
	Glyph *nextLine;

	Long noteCurrentForLineCurrent;
	Long noteCurrent = -1;
	Long lineCurrent = 0;
	Long i = 0;
	while (i <= this->current) {// 1. 합치고 난 뒤의 칸을 구하기 위한 줄의 위치와 / 합치고 난뒤의 줄 위치를 / 미리 구한다.
		line = this->glyphs.GetAt(i);
		if (line->GetOnIsLine() == true) {
			noteCurrentForLineCurrent = i;
			noteCurrent++;
		}
		i++;
	}

	i = noteCurrentForLineCurrent;// 2. 합치고 난 뒤의 칸을 구한다.
	while (i < this->current) {
		line = this->glyphs.GetAt(i);
		lineCurrent += line->GetLength();
		i++;
	}
	if (i < this->length) {
		line = this->glyphs.GetAt(i);
		lineCurrent += line->GetCurrent();
	}

	i = 0;
	while (i < this->length - 1) {// 3. 모든 자동개행된 줄을 합친다.
		line = this->glyphs.GetAt(i);
		nextLine = this->glyphs.GetAt(i + 1);
		while (this->length > i + 1 && nextLine->GetOnIsLine() != true) {
			line->Combine(nextLine); // 알아서 할당해제 해준다.
			line->Select(nextLine->GetOnIsSelected()); // 다음 줄의 선택여부를 확인하여 선택한다.(2021.01.18)
			delete nextLine;
			this->glyphs.Delete(i + 1);
			nextLine = this->glyphs.GetAt(i + 1);
			this->capacity--;
			this->length--;
		}
		i++;
	}
	// 4. 합치고 난 뒤 위치로 이동한다.
	this->current = noteCurrent;
	this->glyphs.GetAt(this->current)->Move(lineCurrent);
}

void Note::Select(Long startLineCurrent, Long startNoteCurrent, Long endLineCurrent, Long endNoteCurrent, bool onIsSelect) {
	Long tempLineCurrent = startLineCurrent;
	Long tempNoteCurrent = startNoteCurrent;

	Glyph *line;

	if (startNoteCurrent > endNoteCurrent || (startNoteCurrent == endNoteCurrent && startLineCurrent > endLineCurrent)) {
		startLineCurrent = endLineCurrent; //lLeft = lRight;
		startNoteCurrent = endNoteCurrent; //lTop = lBottom;
		endLineCurrent = tempLineCurrent; //lRight = left;
		endNoteCurrent = tempNoteCurrent; //lBottom = top;
	}

	line = this->glyphs.GetAt(startNoteCurrent);
	if (startNoteCurrent != endNoteCurrent) {
		line->Select(startLineCurrent, line->GetLength(), onIsSelect);
		line->Select();
	}
	else {
		line->Select(startLineCurrent, endLineCurrent, onIsSelect);
	}

	Long i = startNoteCurrent + 1;
	while (i < endNoteCurrent) {
		line = this->glyphs.GetAt(i);
		line->Select(0, line->GetLength(), onIsSelect);
		line->Select();
		i++;
	}

	if (startNoteCurrent != endNoteCurrent && i <= endNoteCurrent) {
		line = this->glyphs.GetAt(i);
		line->Select(0, endLineCurrent, onIsSelect);
	}
}

void Note::SelectCount(Long startLineCurrent, Long startNoteCurrent, Long textCount) {
	Glyph *line;
	Glyph *nextLine;
	Glyph *glyph;

	bool onIsFirst;
	
	Long endLineCurrent = startLineCurrent;
	Long endNoteCurrent = startNoteCurrent;
	Long i;

	// 2.1. 이전에 선택된 글자들을 모두 선택 해제 한다.
	i = 0;
	while (i < this->length) {
		line = this->glyphs.GetAt(i);
		line->SelectAll(false);
		i++;
	}

	// 2.2. 시작 위치부터 글자 개수만큼 선택한다.
	onIsFirst = true;
	i = startNoteCurrent;
	while (i < this->length && textCount > 0) {
		line = this->glyphs.GetAt(i);
		nextLine = this->glyphs.GetAt(i + 1);
		endLineCurrent = 0;
		if (onIsFirst == true) {
			endLineCurrent = startLineCurrent;
			onIsFirst = false;
		}
		while (endLineCurrent < line->GetLength() && textCount > 0) {
			glyph = line->GetAt(endLineCurrent);
			glyph->Select(true);
			textCount--;
			endLineCurrent++;
		}
		if (endLineCurrent >= line->GetLength() && i < this->length - 1 && textCount > 0) {
			line->Select(true);
		}
		if (i < this->length - 1 && nextLine->GetOnIsLine() == true) {
			textCount--;
		}
		endNoteCurrent = i;
		i++;
	}
	// 2.3. 마지막 위치로 이동한다.
	this->current = endNoteCurrent;
	line = this->glyphs.GetAt(this->current);
	line->Move(endLineCurrent);
}

void Note::SelectAll(bool onIsSelect) {
	Glyph *line;

	Long i = 0;
	while (i < this->length - 1) {
		line = this->glyphs.GetAt(i);
		line->SelectAll(onIsSelect);
		i++;
	}
	if (i < this->length) {
		line = this->glyphs.GetAt(i);
		line->Select(0, line->GetLength(), onIsSelect);
	}
}

bool Note::FindPrevious(string strFindWhat, Long strFindWhatLen, bool onIsMatchCase) {
	bool ret = false;
	bool onIsFirst = true;
	bool onIsPrevious = false;
	bool onIsMatching = false;

	Glyph *line = 0;
	Glyph *nextLine;
	Glyph *glyph;
	string character;
	char findText[3];

	Long findTextLength = (Long)strFindWhat.length();
	Long matchCount = 0;
	Long textCount = strFindWhatLen;
	Long startLineCurrent;
	Long startNoteCurrent;
	Long endLineCurrent;
	Long endNoteCurrent;
	Long k = (Long)strFindWhat.length() - 1;
	Long j;
	Long i = this->current;

	// 1. 현재 위치의 줄부터 마지막 줄보다 작고, 매칭되는 개수와 찾는 글자의 개수가 같지 않을 동안 반복한다.
	while (i >= 0 && matchCount != strFindWhatLen) {
		// 1.1. 줄을 읽는다.
		line = this->glyphs.GetAt(i);
		j = line->GetLength() - 1;
		// 1.2. 처음이면 현재 위치의 줄의 현재 칸부터 시작한다.
		if (onIsFirst == true) {
			j = line->GetCurrent() - 1;
			onIsFirst = false;
		}
		// 1.3. 줄의 마지막 칸보다 작고, 매칭되는 개수와 찾는 글자의 개수가 같지 않을 동안 반복한다.
		while (j >= 0 && line->GetLength() > 0 && matchCount != strFindWhatLen) {
			// 1.3.1. 글자를 읽는다.
			character = line->GetAt(j)->GetString();
			onIsMatching = false;
			// 1.3.2. 찾는 글자의 한 글자를 따온다.
			if (strFindWhat[k] & 0x80) {
				findText[0] = strFindWhat[k - 1];
				findText[1] = strFindWhat[k];
				findText[2] = '\0';
				k -= 2;
			}
			else {
				findText[0] = strFindWhat[k];
				findText[1] = '\0';
				k--;
			}
			// 1.3.3. 찾는 한 글자와 현재 글자가 같으면 매칭 여부를 참으로 한다.
			if ((character[0] & 0x80 && character.compare(findText) == 0) ||
				(onIsMatchCase == true && character.compare(findText) == 0)) {
				onIsMatching = true;
			}
			// 1.3.4. 대/소문자 구분여부가 체크되어 있지 않고 찾는 한 글자와 현재 글자를 대/소문자 구분없이 비교해서 같으면
			// 매칭 여부를 참으로 한다.
			else if (onIsMatchCase != true && _stricmp(character.c_str(), findText) == 0) {
				onIsMatching = true;
			}
			// 1.3.5. 매칭 여부가 참이면 매칭 개수를 증가시킨다.
			if (onIsMatching == true) {
				matchCount++;
				onIsPrevious = true;
			}
			// 1.3.6. 매칭 여부가 거짓이면 매칭개수를 원위치 시킨다.
			else {
				matchCount = 0;
				k = (Long)strFindWhat.length() - 1;
				onIsPrevious = false;
			}
			j--;
		}
		// 1.4. 찾는 글자를 읽는다.
		if (k > 0) {
			findText[0] = strFindWhat[k];
			findText[1] = '\0';
		}

		// 1.5. 글자가 개행문자이면 매칭개수를 증가한다.
		if (findText[0] == '\n') {
			k--;
			matchCount++;
			onIsPrevious = true;
		}
		// 1.6. 현재 줄이 실제 줄이고, 이전으로 이동한 적이 있고, 매칭 개수가 찾는 글자 개수와 같지 않으면 매칭개수를 원위치 시킨다.
		// 자동개행을 풀지 않고 찾을 수 있게 해 놓음.
		else if (line->GetOnIsLine() == true && onIsPrevious == true && matchCount != strFindWhatLen) {
			matchCount = 0;
			k = (Long)strFindWhat.length() - 1;
			onIsPrevious = false;
		}
		
		i--;
	}
	// 2. 매칭개수와 찾는 글자 개수가 같으면(찾았으면)
	if (matchCount == strFindWhatLen && onIsFirst != true) {
		// 2.1. 시작 위치를 구한다.
		startLineCurrent = j + 1;
		startNoteCurrent = i + 1;

		// 2.2. 이전에 선택된 글자들을 모두 선택 해제 한다.
		i = 0;
		while (i < this->length) {
			line = this->glyphs.GetAt(i);
			line->SelectAll(false);
			i++;
		}

		// 2.3. 시작 위치부터 글자 개수만큼 선택한다.
		onIsFirst = true;
		i = startNoteCurrent;
		while (i < this->length && textCount > 0) {
			line = this->glyphs.GetAt(i);
			nextLine = this->glyphs.GetAt(i + 1);
			endLineCurrent = 0;
			if (onIsFirst == true) {
				endLineCurrent = startLineCurrent;
				onIsFirst = false;
			}
			while (endLineCurrent < line->GetLength() && textCount > 0) {
				glyph = line->GetAt(endLineCurrent);
				glyph->Select(true);
				textCount--;
				endLineCurrent++;
			}
			if (endLineCurrent >= line->GetLength() && i < this->length - 1 && textCount > 0) {
				line->Select(true);
			}
			if (i < this->length - 1 && nextLine->GetOnIsLine() == true) {
				textCount--;
			}
			endNoteCurrent = i;
			i++;
		}
		// 2.4. 마지막 위치로 이동한다.
		this->current = endNoteCurrent;
		line = this->glyphs.GetAt(this->current);
		line->Move(endLineCurrent);

		ret = true;
	}

	return ret;
}

bool Note::FindNext(string strFindWhat, Long strFindWhatLen, bool onIsMatchCase) {
	bool ret = false;

	Glyph *previous = 0;
	Glyph *line = 0;
	Glyph *nextLine;
	Glyph *glyph;
	string character;
	char findText[3];

	bool onIsFirst = true;
	bool onIsNext = false;
	bool onIsMatching = false;

	Long findTextLength = (Long)strFindWhat.length();
	Long textCount = strFindWhatLen;
	Long endLineCurrent;
	Long endNoteCurrent;
	Long matchCount = 0;
	Long k = 0;
	Long j;
	Long i = this->current;

	// 1. 현재 위치의 줄부터 마지막 줄보다 작고, 매칭되는 개수와 찾는 글자의 개수가 같지 않을 동안 반복한다.
	while (i < this->length && matchCount != strFindWhatLen) {
		// 2. 줄과 다음줄을 읽는다.
		line = this->glyphs.GetAt(i);
		nextLine = this->glyphs.GetAt(i + 1);

		j = 0;
		// 1.2. 처음이면 현재 위치의 줄의 현재 칸부터 시작한다.
		if (onIsFirst == true) {
			j = line->GetCurrent();
			onIsFirst = false;
		}
		// 1.3. 줄의 마지막 칸보다 작고, 매칭되는 개수와 찾는 글자의 개수가 같지 않을 동안 반복한다.
		while (j < line->GetLength() && matchCount != strFindWhatLen) {
			// 1.3.1. 글자를 읽는다.
			glyph = line->GetAt(j);
			character = glyph->GetString();
			onIsMatching = false;
			// 1.3.2. 찾는 글자의 한 글자를 따온다.
			if (strFindWhat[k] & 0x80) {
				findText[0] = strFindWhat[k];
				findText[1] = strFindWhat[k + 1];
				findText[2] = '\0';
				k += 2;
			}
			else {
				findText[0] = strFindWhat[k];
				findText[1] = '\0';
				k++;
			}
			// 1.3.3. 찾는 한 글자와 현재 글자가 같으면 매칭 여부를 참으로 한다.
			if ((character[0] & 0x80 && character.compare(findText) == 0) ||
				(onIsMatchCase == true && character.compare(findText) == 0)) {
				onIsMatching = true;
			}
			// 1.3.4. 대/소문자 구분여부가 체크되어 있지 않고 찾는 한 글자와 현재 글자를 대/소문자 구분없이 비교해서 같으면
			// 매칭 여부를 참으로 한다.
			else if (onIsMatchCase != true && _stricmp(character.c_str(), findText) == 0) {
				onIsMatching = true;
			}
			// 1.3.5. 매칭 여부가 참이면 매칭 개수를 증가시킨다.
			if (onIsMatching == true) {
				matchCount++;
				onIsNext = true;
			}
			// 1.3.6. 매칭 여부가 거짓이면 매칭개수를 원위치 시킨다.
			else {
				matchCount = 0;
				k = 0;
				onIsNext = false;
			}
			j++;
		}
		// 1.4. 찾는 글자를 읽는다.
		if (k < findTextLength) {
			findText[0] = strFindWhat[k];
			findText[1] = '\0';
		}
		
		// 1.5. 글자가 개행문자이면 매칭개수를 증가한다.
		if (findText[0] == '\n') {
			k++;
			matchCount++;
			onIsNext = true;
		}
		// 1.6. 찾는 글자가 개행문자가 아니고, 이전줄이 있고, 이전줄이 실제 줄이고, 다음이동 여부가 참이고,  
		// 매칭개수와 찾는 글자개수가 같지 않으면
		// 자동개행을 풀지 않고 찾을 수 있게 해 놓음.
		else if (i < this->length - 1 && nextLine->GetOnIsLine() == true && onIsNext == true && matchCount != strFindWhatLen) {
			matchCount = 0;
			k = 0;
			onIsNext = false;
		}
		i++;
	}

	// 2. 매칭개수와 찾는 글자 개수가 같으면(찾았으면)
	if (matchCount == strFindWhatLen) {
		// 2.1. 마지막 위치를 구한다. 거꾸로 가야됨
		endLineCurrent = j;
		endNoteCurrent = i - 1;

		// 2.2. 이전에 선택된 글자들을 모두 선택 해제 한다.
		i = 0;
		while (i < this->length) {
			line = this->glyphs.GetAt(i);
			line->SelectAll(false);
			i++;
		}

		// 2.3. 마지막 위치부터 글자 개수만큼 선택한다.
		onIsFirst = true;
		i = endNoteCurrent;
		while (i >= 0 && textCount > 0) {
			previous = this->glyphs.GetAt(i - 1);
			line = this->glyphs.GetAt(i);
			j = line->GetLength() - 1;
			if (onIsFirst == true) {
				j = endLineCurrent - 1;
				onIsFirst = false;
			}
			while (j >= 0 && textCount > 0) {
				glyph = line->GetAt(j);
				glyph->Select(true);
				textCount--;
				j--;
			}
			if (j < 0 && i > 0 && textCount > 0) {
				previous->Select(true);
			}
			if (line->GetOnIsLine() == true) {
				textCount--;
			}
			i--;
		}

		// 2.4. 마지막 위치로 이동한다.
		this->current = endNoteCurrent;
		line = this->glyphs.GetAt(this->current);
		line->Move(endLineCurrent);

		ret = true;
	}

	return ret;
}

Long Note::Previous() {
	this->current--;
	if (this->current < 0) {
		this->current = 0;
	}

	return this->current;
}

Long Note::Next() {
	this->current++;
	if (this->current >= this->length) {
		this->current = this->length - 1;
	}

	return this->current;
}

Long Note::Last() {
	this->current = this->length - 1;

	return this->current;
}

void Note::MoveActualCurrent(Long lineCurrent, Long noteCurrent) {
	Glyph *line;

	Long lineCount = 0;
	Long findNoteCurrent = 0;
	Long i = 0;

	while (i < this->length && lineCount <= noteCurrent) {// 1. 현재 줄의 실제(onIsLine이 true인) 줄을 구한다.
		line = this->glyphs.GetAt(i);
		if (line->GetOnIsLine() == true) {
			findNoteCurrent = i;
			lineCount++;
		}
		i++;
	}

	line = this->glyphs.GetAt(findNoteCurrent);
	i = findNoteCurrent;
	while (i < this->glyphs.GetLength() - 1 && lineCurrent > line->GetLength()) {
		findNoteCurrent++;
		lineCurrent -= line->GetLength();

		line = this->glyphs.GetAt(i + 1);
		i++;
	}

	this->current = findNoteCurrent;
	line = this->glyphs.GetAt(this->current);
	line->Move(lineCurrent);
}

Long Note::MoveToFirstSelectedCurrent() {
	Glyph *line;

	Long noteCurrent = -1;
	Long lineCurrent = -1;
	Long i = 0;
	while (i < this->length && lineCurrent == -1) {
		line = this->glyphs.GetAt(i);
		lineCurrent = line->MoveToFirstSelectedCurrent();
		i++;
	}
	if (lineCurrent != -1) {
		noteCurrent = i - 1;
		this->current = noteCurrent;
	}

	return noteCurrent;
}

Long Note::MoveToLastSelectedCurrent() {
	Glyph *line;

	bool onIsSelected;

	Long noteCurrent = 0;
	Long lineCurrent = -1;
	Long i = this->length;
	while (i > 0 && lineCurrent == -1) {
		line = this->glyphs.GetAt(i - 1);
		lineCurrent = line->MoveToLastSelectedCurrent();
		onIsSelected = line->GetOnIsSelected();
		i--;
	}
	if (lineCurrent != -1) {
		noteCurrent = i;
		if (onIsSelected == true) {
			noteCurrent++;
		}
		this->current = noteCurrent;
	}

	return noteCurrent;
}

void Note::GetCombineCurrent(Long *lineCurrent, Long *noteCurrent) {
	Glyph *line;

	Long noteCurrentForLineCurrent;
	Long findNoteCurrent = -1;
	Long findLineCurrent = 0;
	Long i = 0;
	while (i <= this->current) {// 1. 합치고 난 뒤의 칸을 구하기 위한 줄의 위치와 / 합치고 난뒤의 줄 위치를 / 미리 구한다.
		line = this->glyphs.GetAt(i);
		if (line->GetOnIsLine() == true) {
			noteCurrentForLineCurrent = i;
			findNoteCurrent++;
		}
		i++;
	}

	i = noteCurrentForLineCurrent;// 2. 합치고 난 뒤의 칸을 구한다.
	while (i < this->current) {
		line = this->glyphs.GetAt(i);
		findLineCurrent += line->GetLength();
		i++;
	}
	if (i < this->length) {
		line = this->glyphs.GetAt(i);
		findLineCurrent += line->GetCurrent();
	}

	// 3. 미리 구한 위치를 출력한다.
	*noteCurrent = findNoteCurrent;
	*lineCurrent = findLineCurrent;
}

void Note::GetSelectRange(Long *startLineCurrent, Long *startNoteCurrent, Long *endLineCurrent, Long *endNoteCurrent) {
	Long j;
	Long i = 0;

	Glyph *currentLine = this->glyphs.GetAt(this->current);
	Glyph *line;
	Glyph *character = 0;

	bool onIsFound = false; // 시작 선택된 위치를 찾기 위한 플래그
	bool onIsFirst = true; // 마지막 선택된 위치를 찾기 위한 플래그

	*startLineCurrent = 0;
	*startNoteCurrent = 0;
	*endLineCurrent = 0;
	*endNoteCurrent = 0;

	// 1. 시작 선택된 위치를 구한다.
	while (i < this->length && onIsFound != true) {
		line = this->glyphs.GetAt(i);
		j = 0;
		while (j < line->GetLength() && onIsFound != true) {
			character = line->GetAt(j);
			if (character->GetOnIsSelected() == true) {
				*startLineCurrent = j;
				*startNoteCurrent = i;
				onIsFound = true;
			}
			j++;
		}
		if (j >= line->GetLength() && line->GetOnIsSelected() == true && onIsFound != true) {
			*startLineCurrent = j;
			*startNoteCurrent = i;
			onIsFound = true;
		}
		i++;
	}

	if (onIsFound != true) {
		*startLineCurrent = currentLine->GetCurrent();
		*startNoteCurrent = this->current;
	}
	
	bool onIsStop = false;
	// 2. 마지막 선택된 위치를 구한다.
	i = *startNoteCurrent;
	while (i < this->length && onIsStop != true) {
		line = this->glyphs.GetAt(i);
		j = 0;
		if (onIsFirst == true) {
			j = *startLineCurrent;
			onIsFirst = false;
		}
		while (j < line->GetLength() && onIsStop != true) {
			character = line->GetAt(j);
			if (character->GetOnIsSelected() == true) {
				*endLineCurrent = j + 1;
				*endNoteCurrent = i;
			}
			else {
				onIsStop = true;
			}
			j++;
		}
		if (j >= line->GetLength() && line->GetOnIsSelected() == true) {
			*endLineCurrent = 0;
			*endNoteCurrent = i + 1;
		}
		i++;
	}

	if (onIsFound != true) {
		*endLineCurrent = currentLine->GetCurrent();
		*endNoteCurrent = this->current;
	}
}

Glyph* Note::Clone() {
	return new Note(*this);
}

string Note::GetString() {
	string str;
	string text;

	Glyph *line;
	Glyph *nextLine;
	
	Long j;
	Long i = 0;
	while (i < this->length - 1) {
		line = this->glyphs.GetAt(i);
		nextLine = this->glyphs.GetAt(i + 1);
		j = 0;
		while (j < line->GetLength()) {
			text = line->GetAt(j)->GetString();
			str += text;

			j++;
		}
		if (nextLine->GetOnIsLine() == true) {
			str += "\n";
		}

		i++;
	}
	if (i < this->length) {
		line = this->glyphs.GetAt(i);
		j = 0;
		while (j < line->GetLength()) {
			text = line->GetAt(j)->GetString();
			str += text;

			j++;
		}
	}

	return str;
}

string Note::GetSelectString() {
	string str;

	Glyph *line;
	Glyph *nextLine;

	Long i = 0;
	// 1. 마지막 줄 전까지 반복한다.
	while (i < this->length - 1) {
		// 1.1. 줄을 읽는다.
		line = this->glyphs.GetAt(i);
		// 1.2. 다음 줄을 읽는다.
		nextLine = this->glyphs.GetAt(i + 1);

		// 1.3. 줄에서 선택된 글자들을 누적한다.
		str += line->GetSelectString();
		// 1.4. 현재 줄이 선택되어 있고, 다음 줄이 실제 줄이면 개행문자를 누적한다.
		if (line->GetOnIsSelected() == true && nextLine->GetOnIsLine() == true) {
			str += "\n";
		}

		i++;
	}
	// 2. 마지막 줄의 선택된 글자들을 누적한다.
	if (i < this->length) {
		line = this->glyphs.GetAt(i);
		str += line->GetSelectString();
	}
	// 3. 누적된 글자들을 출력한다.
	return str;
}

bool Note::GetOnIsSelected() const {
	bool onIsSelect = false;

	Glyph *line;
	Glyph *character;

	Long j;
	Long i = 0;
	while (i < this->length && onIsSelect != true) {
		line = const_cast<Note*>(this)->glyphs.GetAt(i);
		j = 0;
		while (j < line->GetLength() && onIsSelect != true) {
			character = line->GetAt(j);
			onIsSelect = character->GetOnIsSelected();
			j++;
		}
		if (line->GetOnIsSelected() == true) {
			onIsSelect = line->GetOnIsSelected();
		}
		i++;
	}

	return onIsSelect;
}

Note& Note::operator =(const Note& source) {
	Composite::operator =(source);

	return *this;
}