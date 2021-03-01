// Scroll.cpp
/*
파일명칭 : Scroll.cpp
기능 : 스크롤 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.11
*/
#include "Scroll.h"

Scroll::Scroll() {
	this->min = 0;
	this->max = 0;
	this->unit = 0;
	this->page = 0;
	this->current = -1;
}

Scroll::Scroll(Long min, Long max, Long unit, Long page, Long current) {
	this->min = min;
	this->max = max;
	this->unit = unit;
	this->page = page;
	this->current = current;
}

Scroll::Scroll(const Scroll& source) {
	this->min = source.min;
	this->max = source.max;
	this->unit = source.unit;
	this->page = source.page;
	this->current = source.current;
}

Scroll::~Scroll() {
}

void Scroll::First() {
	this->current = 0;
}

void Scroll::PreviousUnit() {
	this->current -= this->unit;
	if (this->current < 0) {
		this->current = 0;
	}
}

void Scroll::NextUnit() {
	this->current += this->unit;
	if (this->current >= this->max - this->page) {
		this->current = this->max - this->page + 2;
	}
}

void Scroll::PreviousPage() {
	this->current -= this->page;
	if (this->current < 0) {
		this->current = 0;
	}
}

void Scroll::NextPage() {
	this->current += this->page;
	if (this->current >= this->max - this->page) {
		this->current = this->max - this->page + 2;
	}
}

void Scroll::Last() {
	this->current = this->max - this->page + 2;
}

void Scroll::Move(Long amount) {
	this->current = amount;
	if (this->current < 0) {
		this->current = 0;
	}
	else if (this->current >= this->max - this->page) {
		this->current = this->max - this->page + 2;
	}
}

Scroll& Scroll::operator =(const Scroll& source) {
	this->min = source.min;
	this->max = source.max;
	this->unit = source.unit;
	this->page = source.page;
	this->current = source.current;

	return *this;
}