// Letter.cpp
/*
파일명칭 : Letter.cpp
기능 : 글자 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.06
*/
#include "Letter.h"

Letter::Letter() {
	this->onIsSelected = false;
}

Letter::~Letter() {
}

void Letter::Select(bool select) {
	this->onIsSelected = select;
}