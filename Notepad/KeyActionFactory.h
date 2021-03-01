// KeyActionFactory.h
#ifndef _KEYACTIONFACTORY_H
#define _KEYACTIONFACTORY_H
#include "NotepadForm.h"

class KeyAction;
class KeyActionFactory {
public:
	KeyActionFactory();
	KeyActionFactory(NotepadForm *notepadForm);
	~KeyActionFactory();
	KeyAction* Create(UINT nChar);

private:
	NotepadForm *notepadForm;
};

#endif // _KEYACTIONFACTORY_H