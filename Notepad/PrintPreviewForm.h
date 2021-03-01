// PrintPreviewForm.h
#ifndef _PRINTPREVIEWFORM_H
#define _PRINTPREVIEWFORM_H
#include <afxwin.h>

class NotepadForm;
class PrintPreviewForm : public CFrameWnd {
public:
	NotepadForm *notepadForm;
	BOOL onIsNotepadOrWordMode;
	BOOL onIsWordWrap;
	HICON m_hIcon;
	LONG m_nPages;

public:
	PrintPreviewForm(NotepadForm *notepadForm = NULL, BOOL onIsNotepadOrWordMode = TRUE, BOOL onIsWordWrap = FALSE);
	BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	afx_msg virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg virtual void OnPaint();
	afx_msg virtual void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif // _PRINTPREVIEWFORM_H