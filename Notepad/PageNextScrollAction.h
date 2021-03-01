// PageNextScrollAction.h
#ifndef _PAGENEXTSCROLLACTION_H
#define _PAGENEXTSCROLLACTION_H
#include "ScrollAction.h"

class PageNextScrollAction : public ScrollAction {
public:
	PageNextScrollAction(NotepadForm *notepadForm);
	virtual ~PageNextScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

#endif // _PAGENEXTSCROLLACTION_H