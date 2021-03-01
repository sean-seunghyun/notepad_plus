// ScrollActionFactory.h
#ifndef _SCROLLACTIONFACTORY_H
#define _SCROLLACTIONFACTORY_H
#include "NotepadForm.h"

class ScrollAction;
class ScrollActionFactory {
public:
	NotepadForm *notepadForm;

public:
	ScrollActionFactory(NotepadForm *notepadForm);
	~ScrollActionFactory();
	ScrollAction* Create(UINT nSBCode);
};

#endif // _SCROLLACTIONFACTORY_H