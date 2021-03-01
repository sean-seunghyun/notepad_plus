// Printer.h
#ifndef _PRINTER_H
#define _PRINTER_H
#include <afxwin.h>

class NotepadForm;
class CWnd;
class PrintPreviewForm;
class PageInfo;
class Printer {
public:
	Printer(NotepadForm *notepadForm = 0);
	~Printer();
	void CreatePageInfo(CWnd *previewForm);
	CRect GetPrintPageRect();
	CRect GetPreviewPageRect();
	CRect GetPrintPageMargin();
	CRect GetPreviewPageMargin();
	CRect GetPrintWriteRect();
	CRect GetPreviewWriteRect();
	LOGFONT GetPrintLogFont();
	LOGFONT GetPreviewLogFont();
	PageInfo* GetNotepadPageInfo() const;
	PageInfo* GetPreviewPageInfo() const;
	HDC GetHDC();
	void SetDC(HDC printerDC);

private:
	NotepadForm *notepadForm;
	HDC printerDC;
	PageInfo *notepadPage;
	PageInfo *previewPage;
};

inline HDC Printer::GetHDC() {
	return this->printerDC;
}

inline PageInfo* Printer::GetNotepadPageInfo() const {
	return const_cast<PageInfo*>(this->notepadPage);
}

inline PageInfo* Printer::GetPreviewPageInfo() const {
	return const_cast<PageInfo*>(this->previewPage);
}

#endif // _PRINTER_H