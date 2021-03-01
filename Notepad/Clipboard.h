// Clipboard.h
#ifndef _CLIPBOARD_H
#define _CLIPBOARD_H
#include <afxwin.h>

class NotepadForm;
class Clipboard {
public:
	NotepadForm *notepadForm;

public:
	Clipboard(NotepadForm *notepadForm);
	~Clipboard();
	void Write(CString copyString);
	CString Read();
};

#endif // _CLIPBOARD_H