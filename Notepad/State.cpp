// State.cpp
/*
파일명칭 : State.cpp
기능 : 상태 정보 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.26
*/
#include "State.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "GlyphFactory.h"

State::State() {
	this->note = 0;
}

State::State(Long lineCurrent, Long noteCurrent, string text) {
	this->lineCurrent = lineCurrent;
	this->noteCurrent = noteCurrent;

	GlyphFactory glyphFactory;
	Glyph *line = 0;
	Long length = (Long)text.length();
	char character[2];

	this->note = glyphFactory.Create(NULL);
	if (length > 0) {
		line = glyphFactory.Create((char*)"\n");
		this->note->Add(line);
		this->note->First();
	}

	Glyph *glyph;
	Long i = 0;
	while (i < length) {
		character[0] = text[i];
		if (character[0] == '\r' || character[0] == '\n') {
			glyph = glyphFactory.Create(character);
			line->Split(glyph, line->GetCurrent());
			line = glyph;
			noteCurrent = this->note->GetCurrent();
			this->note->Add(noteCurrent + 1, glyph);
			if (i + 1 < length && text[i] == '\r' && text[i + 1] == '\n') {
				i++;
			}
		}
		else if (character[0] == 0x09 || character[0] >= 0x20 && character[0] < 0x7F) {
			glyph = glyphFactory.Create(character);
			line->Add(line->GetCurrent(), glyph);
		}
		else if (character[0] & 0x80) {
			i++;
			character[1] = text[i];
			glyph = glyphFactory.Create(character);
			line->Add(line->GetCurrent(), glyph);
		}
		i++;
	}
}

State::State(const State& source) {
	this->lineCurrent = source.lineCurrent;
	this->noteCurrent = source.noteCurrent;
	this->note = source.note->Clone();
}

State::~State() {
	if (this->note != 0) {
		delete this->note;
	}
}

State& State::operator =(const State& source) {
	this->lineCurrent = source.lineCurrent;
	this->noteCurrent = source.noteCurrent;
	if (this->note != 0) {
		delete this->note;
	}
	this->note = source.note->Clone();

	return *this;
}