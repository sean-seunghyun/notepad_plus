// HomeKeyAction.h
#ifndef _HOMEKEYACTION_H
#define _HOMEKEYACTION_H
#include "KeyAction.h"

class HomeKeyAction : public KeyAction {
public:
	HomeKeyAction(NotepadForm *notepadForm);
	virtual ~HomeKeyAction();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _HOMEKEYACTION_H