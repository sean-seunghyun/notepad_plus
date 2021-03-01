// LinePreviousScrollAction.h
#ifndef _LINEPREVIOUSSCROLLACTION_H
#define _LINEPREVIOUSSCROLLACTION_H
#include "ScrollAction.h"

class LinePreviousScrollAction : public ScrollAction {
public:
	LinePreviousScrollAction(NotepadForm *notepadForm);
	virtual ~LinePreviousScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

#endif // _LINEPREVIOUSSCROLLACTION_H