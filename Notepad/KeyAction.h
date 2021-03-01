// KeyAction.h
#ifndef _KEYACTION_H
#define _KEYACTION_H
#include <afxwin.h>

class NotepadForm;
class KeyAction {
public:
	KeyAction();
	KeyAction(const KeyAction& source);
	virtual ~KeyAction() = 0;
	KeyAction& operator =(const KeyAction& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {  }

protected:
	NotepadForm *notepadForm;
};

#endif // _KEYACTION_H