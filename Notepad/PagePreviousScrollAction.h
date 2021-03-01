// PagePreviousScrollAction.h
#ifndef _PAGEPREVIOUSSCROLLACTION_H
#define _PAGEPREVIOUSSCROLLACTION_H
#include "ScrollAction.h"

class PagePreviousScrollAction : public ScrollAction {
public:
	PagePreviousScrollAction(NotepadForm *notepadForm);
	virtual ~PagePreviousScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

#endif // _PAGEPREVIOUSSCROLLACTION_H