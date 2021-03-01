// HorizontalScroll.cpp
/*
파일명칭 : HorizontalScroll.cpp
기능 : 수평 스크롤 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.11
*/
#include "HorizontalScroll.h"

HorizontalScroll::HorizontalScroll() {
}

HorizontalScroll::HorizontalScroll(Long min, Long max, Long unit, Long page, Long current)
	: Scroll(min, max, unit, page, current) {
}

HorizontalScroll::HorizontalScroll(const HorizontalScroll& source)
	: Scroll(source.min, source.max, source.unit, source.page, source.current) {
}

HorizontalScroll::~HorizontalScroll() {
}

Scroll* HorizontalScroll::Clone(Long min, Long max, Long unit, Long page, Long current) {
	return new HorizontalScroll(min, max, unit, page, current);
}

HorizontalScroll& HorizontalScroll::operator =(const HorizontalScroll& source) {
	*static_cast<Scroll*>(this) = source;

	return *this;
}