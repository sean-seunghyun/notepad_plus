// ThumbTrackScrollAction.h
#ifndef _THUMBTRACKSCROLLACTION_H
#define _THUMBTRACKSCROLLACTION_H
#include "ScrollAction.h"

class ThumbTrackScrollAction : public ScrollAction {
public:
	ThumbTrackScrollAction(NotepadForm *notepadForm);
	virtual ~ThumbTrackScrollAction();
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
};

#endif // _THUMBTRACKSCROLLACTION_H