// Observer.h
#ifndef _OBSERVER_H
#define _OBSERVER_H

class Subject;
class Observer {
public:
	Subject *subject;

public:
	Observer(Subject *subject = 0);
	virtual ~Observer() = 0;
	virtual void Update() = 0;
	virtual Observer* Clone() { return 0; }
};

#endif // _OBSERVER_H