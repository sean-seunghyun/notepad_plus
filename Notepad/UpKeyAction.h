// UpKeyAction.h
#ifndef _UPKEYACTION_H
#define _UPKEYACTION_H
#include "KeyAction.h"

class UpKeyAction : public KeyAction {
public:
	UpKeyAction(NotepadForm *notepadForm);
	virtual ~UpKeyAction();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _UPKEYACTION_H