
//ScrollController.h
#ifndef _SCROLLCONTROLLER_H
#define _SCROLLCONTROLLER_H
#include"Observer.h"

class NotepadForm;
class Scroll;
class ScrollController : public Observer {
public:
	Scroll *horizontalScroll;
	Scroll *verticalScroll;
	NotepadForm *notepadForm;

public:
	ScrollController(NotepadForm *notepadForm = 0);
	virtual ~ScrollController();
	virtual void Update();
	virtual Observer* Clone();
	Scroll* GetHorizontalScroll();
	Scroll* GetVerticalScroll();
};

#endif // !_SCROLLCONTROLLER_H
