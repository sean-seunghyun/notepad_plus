// CtrlEndKeyAction.h
#ifndef _CTRLENDKEYACTION_H
#define _CTRLENDKEYACTION_H
#include "KeyAction.h"

class CtrlEndKeyAction : public KeyAction {
public:
	CtrlEndKeyAction(NotepadForm *notepadForm);
	virtual ~CtrlEndKeyAction();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _CTRLENDKEYACTION_H