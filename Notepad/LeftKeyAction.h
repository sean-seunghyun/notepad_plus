// LeftKeyAction.h
#ifndef _LEFTKEYACTION_H
#define _LEFTKEYACTION_H
#include "KeyAction.h"

class LeftKeyAction : public KeyAction {
public:
	LeftKeyAction(NotepadForm *notepadForm);
	virtual ~LeftKeyAction();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _LEFTKEYACTION_H