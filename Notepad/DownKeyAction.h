// DownKeyAction.h
#ifndef _DOWNKEYACTION_H
#define _DOWNKEYACTION_H
#include "KeyAction.h"

class DownKeyAction : public KeyAction {
public:
	DownKeyAction(NotepadForm *notepadForm);
	virtual ~DownKeyAction();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _DOWNKEYACTION_H