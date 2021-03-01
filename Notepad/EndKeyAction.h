// EndKeyAction.h
#ifndef _ENDKEYACTION_H
#define _ENDKEYACTION_H
#include "KeyAction.h"

class EndKeyAction : public KeyAction {
public:
	EndKeyAction(NotepadForm *notepadForm);
	virtual ~EndKeyAction();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _ENDKEYACTION_H