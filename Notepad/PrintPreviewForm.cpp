// PrintPreviewForm.cpp
/*
파일명칭 : PrintPreviewForm.cpp
기능 : 인쇄 미리보기 윈도우를 만든다.
작성자 : 정성원
작성일자 : 2020.08.07
*/
#include "PrintPreviewForm.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include "Font.h"
#include "Printer.h"
#include "resource.h"
#include <afxtempl.h>
#if _MFC_VER < 0x0700
#include <..\src\afximpl.h>
#else
#include <..\src\mfc\afximpl.h>
#endif
#define PREVIEW_MARGIN 9

BEGIN_MESSAGE_MAP(PrintPreviewForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

PrintPreviewForm::PrintPreviewForm(NotepadForm *notepadForm, BOOL onIsNotepadOrWordMode, BOOL onIsWordWrap) {
	this->notepadForm = notepadForm;
	this->onIsNotepadOrWordMode = onIsNotepadOrWordMode;
	this->onIsWordWrap = onIsWordWrap;
}

BOOL PrintPreviewForm::PreCreateWindow(CREATESTRUCT& cs) {
	CFrameWnd::PreCreateWindow(cs);

	cs.style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);

	return TRUE;
}

int PrintPreviewForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
#if 0
	CFrameWnd::OnCreate(lpCreateStruct);
	this->m_hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_MAINFRAME));
	this->SetIcon(this->m_hIcon, ICON_SMALL);

	this->notepadForm->printer->CreatePageInfo(this);
#endif
	Invalidate();

	return 0;
}

void PrintPreviewForm::OnPaint() {
	CPaintDC paintDC(this);
#if 0
	CDC tempDC;
	CDC *m_dcPrint = CDC::FromHandle(this->notepadForm->printer->GetHDC());

	CPoint ViewportOrg = paintDC.GetViewportOrg();

	CRect rectScreen;
	CRect pageRect;
	CRect rectFill;

	CPen rectPen;
	CPen shadowPen;

	HBITMAP hbmp;
	HBITMAP oldBMP;

	this->GetClientRect(&rectScreen);

	tempDC.CreateCompatibleDC(&paintDC);

	hbmp = ::CreateCompatibleBitmap(paintDC, rectScreen.right, rectScreen.bottom);
	oldBMP = (HBITMAP)tempDC.SelectObject(hbmp);

	tempDC.FillRect(&rectScreen, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));

	rectPen.CreatePen(PS_SOLID, 2, GetSysColor(COLOR_WINDOWFRAME));
	shadowPen.CreatePen(PS_SOLID, 3, GetSysColor(COLOR_BTNSHADOW)); // 그림자를 줌.

	pageRect = this->notepadForm->printer->GetPreviewPageRect();

	tempDC.SetMapMode(MM_TEXT);   // Page Rectangle is in screen device coords
	tempDC.SetViewportOrg(ViewportOrg);
	tempDC.SetWindowOrg(0, 0);

	tempDC.SelectStockObject(HOLLOW_BRUSH);
	tempDC.SelectObject(&rectPen);
	tempDC.Rectangle(&pageRect);

	tempDC.SelectObject(&shadowPen);

	tempDC.MoveTo(pageRect.right + 1, pageRect.top + 3);
	tempDC.LineTo(pageRect.right + 1, pageRect.bottom + 1);
	tempDC.MoveTo(pageRect.left + 3, pageRect.bottom + 1);
	tempDC.LineTo(pageRect.right + 1, pageRect.bottom + 1);

	// erase background to white (most paper is white)
	rectFill = pageRect;
	rectFill.left += 1;
	rectFill.top += 1;
	rectFill.right -= 2;
	rectFill.bottom -= 2;

	CBrush br(RGB(240, 240, 240));
	tempDC.FillRect(&pageRect, &br);
	br.DeleteObject();

	CBrush brush(RGB(255, 255, 255));
	tempDC.FillRect(&rectFill, &brush);
	brush.DeleteObject();

	// 인쇄 미리보기 To do

	HFONT hFont;
	HFONT oldFont;
	LOGFONT logFont = this->notepadForm->printer->GetPreviewLogFont();
	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)tempDC.SelectObject(hFont);
	tempDC.SetTextColor(this->notepadForm->font->GetColorRef());

	CString header = AfxGetApp()->GetProfileString("NotepadSection", "Header", "");
	CString footer = AfxGetApp()->GetProfileString("NotepadSection", "Footer", "");

	TEXTMETRIC metric;
	tempDC.GetTextMetrics(&metric);

	CRect writeRect = this->notepadForm->printer->GetPreviewWriteRect();
	if (header != "") {
		writeRect.top += metric.tmHeight;

		RECT headerRect = { rectScreen.left, rectScreen.top, rectScreen.right, writeRect.top };
		tempDC.DrawText(header, &headerRect, DT_EXPANDTABS | DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}

	if (footer != "") {
		writeRect.bottom -= metric.tmHeight;

		RECT footerRect = { rectScreen.left, writeRect.bottom, rectScreen.right, rectScreen.bottom };
		tempDC.DrawText(footer, &footerRect, DT_EXPANDTABS | DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}

	CString text = CString(this->notepadForm->note->GetString().c_str());
	tempDC.DrawText(text, &writeRect, /*DT_WORDBREAK | DT_EDITCONTROL | */DT_EXPANDTABS);

	paintDC.BitBlt(0, 0, rectScreen.right, rectScreen.bottom, &tempDC, 0, 0, SRCCOPY);

	SelectObject(tempDC, oldFont);
	DeleteObject(hFont);

	tempDC.SelectObject(oldBMP);
	::DeleteObject(hbmp);
#endif
}

/*
CPaintDC paintDC(this);
	CDC tempDC;

	RECT screenRect;
	this->GetClientRect(&screenRect);

	RECT reducedPage = this->notepadForm->printer->GetReducedPages(this);

	tempDC.CreateCompatibleDC(&paintDC);

	HBITMAP hbmp = ::CreateCompatibleBitmap(paintDC, screenRect.right, screenRect.bottom);
	HBITMAP oldBMP = (HBITMAP)tempDC.SelectObject(hbmp);

	tempDC.FillRect(&screenRect, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));

	HFONT hFont;
	HFONT oldFont;
	LOGFONT logFont = this->notepadForm->printer->GetPreviewLogFont(this);
	hFont = CreateFontIndirect(&logFont);
	oldFont = (HFONT)tempDC.SelectObject(hFont);
	tempDC.SetTextColor(this->notepadForm->font.GetColorRef());

	CString header = AfxGetApp()->GetProfileString("NotepadSection", "Header", "");
	CString footer = AfxGetApp()->GetProfileString("NotepadSection", "Footer", "");

	TEXTMETRIC metric;
	tempDC.GetTextMetrics(&metric);

	tempDC.Rectangle(reducedPage.left, reducedPage.top, reducedPage.right, reducedPage.bottom);

	RECT margin = this->notepadForm->printer->GetMargin();

	RECT writeRect = { reducedPage.left + margin.left, reducedPage.top + margin.top, reducedPage.right - margin.right,
		reducedPage.bottom - margin.bottom };
	if (header != "") {
		writeRect.top += metric.tmHeight;

		RECT headerRect = { reducedPage.left, reducedPage.top, reducedPage.right, writeRect.top };
		tempDC.DrawText(header, &headerRect, DT_EXPANDTABS | DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}

	if (footer != "") {
		writeRect.bottom -= metric.tmHeight;

		RECT footerRect = { reducedPage.left, writeRect.bottom, reducedPage.right, reducedPage.bottom };
		tempDC.DrawText(footer, &footerRect, DT_EXPANDTABS | DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}

	CString text = CString(this->notepadForm->note->GetString().c_str());
	tempDC.DrawText(text, &writeRect, /*DT_WORDBREAK | DT_EDITCONTROL | DT_EXPANDTABS);

	paintDC.BitBlt(0, 0, screenRect.right, screenRect.bottom, &tempDC, 0, 0, SRCCOPY);

	SelectObject(tempDC, oldFont);
	DeleteObject(hFont);

	tempDC.SelectObject(oldBMP);
	::DeleteObject(hbmp);

*/

void PrintPreviewForm::OnClose() {
	if (this->m_hIcon != 0) {
		DestroyIcon(this->m_hIcon);
	}
	CFrameWnd::OnClose();
}