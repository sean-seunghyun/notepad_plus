// SelectedRightKeyAction.h
#ifndef _SELECTEDRIGHTKEYACTION_H
#define _SELECTEDRIGHTKEYACTION_H
#include "KeyAction.h"

class SelectedRightKeyAction : public KeyAction {
public:
	SelectedRightKeyAction(NotepadForm *notepadForm);
	virtual ~SelectedRightKeyAction();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _SELECTEDRIGHTKEYACTION_H