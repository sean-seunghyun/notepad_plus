//PageSetupDialog.h
#ifndef _PAGESETUPDIALOG_H
#define _PAGESETUPDIALOG_H
#include<afxdlgs.h>
#include"resource.h"
class NotepadForm;
class PageSetupDialog :public CPageSetupDialog {
public:
	PageSetupDialog(DWORD dwFlags, CWnd *parent = NULL);
public:
	enum { IDD = IDD_PAGESETUPFORM };
public:
	NotepadForm *notepadForm;
protected:
	afx_msg virtual BOOL OnInitDialog();
	afx_msg virtual void OnOK();
	DECLARE_MESSAGE_MAP()

};


#endif // !_PAGESETUPDIALOG_H
