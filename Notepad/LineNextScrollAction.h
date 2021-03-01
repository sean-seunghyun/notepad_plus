// LineNextScrollAction.h
#ifndef _LINENEXTSCROLLACTION_H
#define _LINENEXTSCROLLACTION_H
#include "ScrollAction.h"

class LineNextScrollAction : public ScrollAction {
public:
	LineNextScrollAction(NotepadForm *notepadForm);
	virtual ~LineNextScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

#endif // _LINENEXTSCROLLACTION_H