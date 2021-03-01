// Font.cpp
/*
파일명칭 : Font.cpp
기능 : 글꼴 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.07
*/
#include "Font.h"

Font::Font() {
	memset(&this->logFont, 0, sizeof(LOGFONT));
	memset(&this->color, 0, sizeof(COLORREF));
}

Font::Font(LOGFONT logFont, COLORREF color) {
	this->logFont = logFont;
	this->color = color;
}

Font::Font(const Font& source) {
	this->logFont = source.logFont;
	this->color = source.color;
}

Font::~Font() {
}

Font& Font::operator =(const Font& source) {
	this->logFont = source.logFont;
	this->color = source.color;

	return *this;
}