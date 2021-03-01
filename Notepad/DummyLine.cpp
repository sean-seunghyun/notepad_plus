// DummyLine.cpp
/*
파일명칭 : DummyLine.cpp
기능 : 더미줄 클래스를 만든다.
작성자 : 정성원
작성일자 : 2020.06.18
*/
#include "DummyLine.h"

DummyLine::DummyLine(Long capacity, bool onIsLine)
	: Line(capacity, onIsLine) {
}

DummyLine::DummyLine(const DummyLine& source)
	: Line(source) {
}

DummyLine::~DummyLine() {
}

Glyph* DummyLine::Clone() {
	return new DummyLine(*this);
}

DummyLine& DummyLine::operator =(const DummyLine& source) {
	Line::operator =(source);

	return *this;
}