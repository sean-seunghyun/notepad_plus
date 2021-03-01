// CtrlLeftKeyAction.h
#ifndef _CTRLLEFTKEYACTION_H
#define _CTRLLEFTKEYACTION_H
#include "KeyAction.h"

class CtrlLeftKeyAction : public KeyAction {
public:
	CtrlLeftKeyAction(NotepadForm *notepadForm);
	virtual ~CtrlLeftKeyAction();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _CTRLLEFTKEYACTION_H