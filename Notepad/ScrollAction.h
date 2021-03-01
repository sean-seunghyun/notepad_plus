// ScrollAction.h
#ifndef _SCROLLACTION_H
#define _SCROLLACTION_H
#include "NotepadForm.h"

class ScrollAction {
public:
	NotepadForm *notepadForm;

public:
	ScrollAction(NotepadForm *notepadForm);
	virtual ~ScrollAction() = 0;
	virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) = 0;
	virtual void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) = 0;
};

#endif // _SCROLLACTION_H