// CtrlHomeKeyAction.h
#ifndef _CTRLHOMEKEYACTION_H
#define _CTRLHOMEKEYACTION_H
#include "KeyAction.h"

class CtrlHomeKeyAction : public KeyAction {
public:
	CtrlHomeKeyAction(NotepadForm *notepadForm);
	virtual ~CtrlHomeKeyAction();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _CTRLHOMEKEYACTION_H