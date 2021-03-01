// Subject.cpp
/*
파일명칭 : Subject.cpp
기능 : 옵저버 패턴의 Subject 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.07
*/
#include "Subject.h"
#include "Observer.h"

Subject::Subject(Long capacity)
	: observers(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

Subject::Subject(const Subject& source)
	: observers(source.observers) {
	Observer *observer;
	Long i = 0;
	while (i < source.length) {
		observer = const_cast<Subject&>(source).observers.GetAt(i);
		this->observers.Modify(i, observer->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

Subject::~Subject() {
	Long i = 0;
	while (i < this->length) {
		delete this->observers.GetAt(i);
		i++;
	}
}

void Subject::Attach(Observer *o) {
	if (this->length < this->capacity) {
		this->observers.Store(this->length, o);
	}
	else {
		this->observers.AppendFromRear(o);
		this->capacity++;
	}
	this->length++;
}

void Subject::Detach(Observer *o) {
	Long index;
	index = this->observers.LinearSearchUnique(o, CompareObservers);

	if (index > -1) {
		delete o;
		this->observers.Delete(index);
		this->capacity--;
		this->length--;
	}
}

Subject& Subject::operator =(const Subject& source) {
	Long i = 0;
	while (i < this->length) {
		delete this->observers.GetAt(i);
		i++;
	}

	this->observers = source.observers;

	Observer *observer;
	i = 0;
	while (i < source.length) {
		observer = const_cast<Subject&>(source).observers.GetAt(i);
		this->observers.Modify(i, observer->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

void Subject::Notify() {
	Long i = 0;
	while (i < this->length) {
		this->observers.GetAt(i)->Update();
		i++;
	}
}
int CompareObservers(void *one, void *other) {
	Observer* *one_ = (Observer**)one;
	Observer *other_ = (Observer*)other;
	int ret;
	if (*one_ < other_) {
		ret = -1;
	}
	else if (*one_ == other_) {
		ret = 0;
	}
	else if (*one_ > other_) {
		ret = 1;
	}

	return ret;
}