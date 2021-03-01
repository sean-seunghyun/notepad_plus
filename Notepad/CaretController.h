// CaretController.h
#ifndef _CARETCONTROLLER_H
#define _CARETCONTROLLER_H
#include "Observer.h"

class NotepadForm;
class Caret;
class CaretController : public Observer {
public:
	NotepadForm *notepadForm;
	bool onIsCaret;

public:
	CaretController();
	CaretController(NotepadForm *notepadForm);
	virtual ~CaretController();
	virtual void Update();
	virtual Observer* Clone();

private:
	Caret *caret;
};

#endif // _CARETCONTROLLER_H