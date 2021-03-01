// SelectedLeftKeyAction.h
#ifndef _SELECTEDLEFTKEYACTION_H
#define _SELECTEDLEFTKEYACTION_H
#include "KeyAction.h"

class SelectedLeftKeyAction : public KeyAction {
public:
	SelectedLeftKeyAction(NotepadForm *notepadForm);
	virtual ~SelectedLeftKeyAction();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _SELECTEDLEFTKEYACTION_H