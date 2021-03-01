// LastScrollAction.h
#ifndef _LASTSCROLLACTION_H
#define _LASTSCROLLACTION_H
#include "ScrollAction.h"

class LastScrollAction : public ScrollAction {
public:
	LastScrollAction(NotepadForm *notepadForm);
	virtual ~LastScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

#endif // _LASTSCROLLACTION_H