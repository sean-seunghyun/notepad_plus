// GoToLineDialog.h
#ifndef _GOTOLINEDIALOG_H
#define _GOTOLINEDIALOG_H
#include <afxwin.h>
#include "resource.h"

class NotepadForm;
class GoToLineDialog : public CDialog {
public:
	enum { IDD = IDD_GOTOLINEFORM };

public:
	NotepadForm *notepadForm;

public:
	GoToLineDialog(NotepadForm *notepadForm = NULL);
	~GoToLineDialog();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};

#endif // _GOTOLINEDIALOG_H