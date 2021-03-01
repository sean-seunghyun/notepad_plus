// Composite.cpp
/*
파일명칭 : Composite.cpp
기능 : 컴포지트 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.06
*/
#include "Composite.h"

Composite::Composite(Long capacity)
	:glyphs(capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->current = 0;;
}

Composite::Composite(const Composite& source)
	: glyphs(source.glyphs) {
	Glyph *glyphLink;
	Long i = 0;
	while (i < source.length) {
		glyphLink = this->glyphs.GetAt(i)->Clone();
		this->glyphs.Modify(i, glyphLink);
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;
}

Composite::~Composite() {
	Long i = 0;
	while (i < this->length) {
		delete this->glyphs.GetAt(i);
		i++;
	}
}

Long Composite::Add(Glyph *glyph) {
	Long index;
	if (this->length < this->capacity) {
		index = this->glyphs.Store(this->length, glyph);
	}
	else {
		index = this->glyphs.AppendFromRear(glyph);
		this->capacity++;
	}
	this->current++;
	this->length++;

	return index;
}

Long Composite::Remove(Long index) {
	if (this->glyphs.GetAt(index) != 0) {
		delete this->glyphs.GetAt(index);
	}
	this->glyphs.Delete(index);

	this->capacity--;
	this->length--;
	this->current = index;

	return -1;
}

Long Composite::First() {
	this->current = 0;
	
	return this->current;
}

Long Composite::Move(Long index) {
	this->current = index;

	return this->current;
}

Glyph* Composite::GetAt(Long index) {
	return this->glyphs.GetAt(index);
}

Composite& Composite::operator =(const Composite& source) {
	Long i = 0;
	while (i < this->length) {
		delete this->glyphs.GetAt(i);
		i++;
	}

	this->glyphs = source.glyphs;

	Glyph *glyphLink;
	i = 0;
	while (i < source.length) {
		glyphLink = this->glyphs.GetAt(i)->Clone();
		this->glyphs.Modify(i, glyphLink);
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
	this->current = source.current;

	return *this;
}