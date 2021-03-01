// VerticalScroll.cpp
/*
파일명칭 : VerticalScroll.cpp
기능 : 수평 스크롤 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.11
*/
#include "VerticalScroll.h"

VerticalScroll::VerticalScroll() {
}

VerticalScroll::VerticalScroll(Long min, Long max, Long unit, Long page, Long current)
	: Scroll(min, max, unit, page, current) {
}

VerticalScroll::VerticalScroll(const VerticalScroll& source)
	: Scroll(source.min, source.max, source.unit, source.page, source.current) {
}

VerticalScroll::~VerticalScroll() {
}

Scroll* VerticalScroll::Clone(Long min, Long max, Long unit, Long page, Long current) {
	return new VerticalScroll(min, max, unit, page, current);
}

VerticalScroll& VerticalScroll::operator =(const VerticalScroll& source) {
	*static_cast<Scroll*>(this) = source;

	return *this;
}