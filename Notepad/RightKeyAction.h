// RightKeyAction.h
#ifndef _RIGHTKEYACTION_H
#define _RIGHTKEYACTION_H
#include "KeyAction.h"

class RightKeyAction : public KeyAction {
public:
	RightKeyAction(NotepadForm *notepadForm);
	virtual ~RightKeyAction();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _RIGHTKEYACTION_H