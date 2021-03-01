// FirstScrollAction.h
#ifndef _FIRSTSCROLLACTION_H
#define _FIRSTSCROLLACTION_H
#include "ScrollAction.h"

class FirstScrollAction : public ScrollAction {
public:
	FirstScrollAction(NotepadForm *notepadForm);
	virtual ~FirstScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

#endif // _FIRSTSCROLLACTION_H