// Observer.cpp
/*
파일명칭 : Observer.cpp
기능 : 옵저버 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.07
*/
#include "Observer.h"
#include "Subject.h"

Observer::Observer(Subject *subject) {
	this->subject = subject;
}

Observer::~Observer() {
}