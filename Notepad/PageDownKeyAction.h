// PageDownKeyAction.h
#ifndef _PAGEDOWNKEYACTION_H
#define _PAGEDOWNKEYACTION_H
#include "KeyAction.h"

class PageDownKeyAction : public KeyAction {
public:
	PageDownKeyAction(NotepadForm *notepadForm = 0);
	virtual ~PageDownKeyAction();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif // _PAGEDOWNKEYACTION_H