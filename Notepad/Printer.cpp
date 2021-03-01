// Printer.cpp
/*
파일명칭 : Printer.cpp
기능 : 인쇄기 클래스를 만든다.
작성자 : 정성원
작성일자 : 2020.08.21
*/
#include "Printer.h"
#include "PageInfo.h"
#include "NotepadForm.h"
#include "Font.h"
#if _MFC_VER < 0x0700
#include <..\src\afximpl.h>
#else
#include <..\src\mfc\afximpl.h>
#endif
//#include "PrintPreviewForm.h"

Printer::Printer(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->printerDC = 0;
	this->notepadPage = 0;
	this->previewPage = 0;
}

Printer::~Printer() {
	if (this->printerDC != 0) {
		DeleteDC(this->printerDC);
	}
	if (this->notepadPage != 0) {
		delete this->notepadPage;
	}
	if (this->previewPage != 0) {
		delete this->previewPage;
	}
}
/*
1. 인쇄 용지 크기를 구한다.
dc에서 구한다.
2. 줄의 개수와 칸의 개수를 구한다.
GetTextMetric
3. 여백을 구한다.
4. 미리보기 용지 크기를 구한다.
5. 글자 크기를 구한다.
6. 글자 크기로 폰트를 설정한다.
7. 미리보기 용지의 여백을 구한다.
*/
void Printer::CreatePageInfo(CWnd *previewForm) {// 여기에서 만들때 인쇄, 미리보기를 모두 설정한다.
	CRect printRect;
	CRect previewRect;
	CRect printMargin;
	CRect previewMargin;
	CRect printWriteRect;
	CRect previewWriteRect;
	CRect previewScreenRect;

	HFONT hFont;
	HFONT oldFont;

	CSize ratio;
	CSize previewSize;

	LOGFONT notepadFont;
	LOGFONT printerLogFont;
	LOGFONT previewLogFont;

	TEXTMETRIC metric;

	LONG rowCount = 0;
	LONG columnCount = 0;
	LONG letterWidth;
	LONG letterHeight;

	int nNum;
	int nDen;

	CDC *dc = CDC::FromHandle(this->printerDC);

	// 1. 인쇄 용지 크기를 구한다.
	printRect.left = 0;
	printRect.top = 0;
	printRect.right = dc->GetDeviceCaps(HORZRES);
	printRect.bottom = dc->GetDeviceCaps(VERTRES);

	dc->DPtoLP(&printRect);

	// 2. 인쇄 용지의 폰트를 구한다.
	notepadFont = this->notepadForm->font->GetLogFont();
	printerLogFont = notepadFont;
	printerLogFont.lfHeight = -MulDiv(printerLogFont.lfHeight, GetDeviceCaps(this->printerDC, LOGPIXELSY), 72);
	printerLogFont.lfWidth = 0;

	// 3. 글자 크기를 구한다.
	hFont = CreateFontIndirect(&printerLogFont);
	oldFont = (HFONT)dc->SelectObject(hFont);
	dc->SetTextColor(this->notepadForm->font->GetColorRef());
	dc->GetTextMetrics(&metric);

	// 4. 줄의 개수와 칸의 개수를 구한다.
	columnCount = printRect.right / metric.tmAveCharWidth;
	rowCount = printRect.bottom / metric.tmHeight;

	// 5. 여백을 구한다.
	printMargin.left = AfxGetApp()->GetProfileInt("NotepadSection", "LEFT", 20) * 240;
	printMargin.top = AfxGetApp()->GetProfileInt("NotepadSection", "TOP", 20) * 240;
	printMargin.right = AfxGetApp()->GetProfileInt("NotepadSection", "RIGHT", 20) * 240;
	printMargin.bottom = AfxGetApp()->GetProfileInt("NotepadSection", "BOTTOM", 20) * 240;

	// 6. 인쇄 용지의 적을 범위를 구한다.
	printWriteRect = printRect;
	printWriteRect.left += printMargin.left;
	printWriteRect.top += printMargin.top;
	printWriteRect.right -= printMargin.right;
	printWriteRect.bottom -= printMargin.bottom;

	// 7. 미리보기 용지 크기를 구한다.
	previewRect = printRect;
	dc->DPtoLP(&previewRect);

	previewMargin = printMargin;
	dc->DPtoLP(&previewMargin);

	previewForm->GetClientRect(&previewScreenRect);

	previewSize.cx = MulDiv(printRect.right, afxData.cxPixelsPerInch, dc->GetDeviceCaps(LOGPIXELSX));
	previewSize.cy = MulDiv(printRect.bottom, afxData.cyPixelsPerInch, dc->GetDeviceCaps(LOGPIXELSY));

	previewMargin.left = MulDiv(printMargin.left, afxData.cxPixelsPerInch, dc->GetDeviceCaps(LOGPIXELSX));
	previewMargin.top = MulDiv(printMargin.top, afxData.cyPixelsPerInch, dc->GetDeviceCaps(LOGPIXELSY));
	previewMargin.right = MulDiv(printMargin.right, afxData.cxPixelsPerInch, dc->GetDeviceCaps(LOGPIXELSX));
	previewMargin.bottom = MulDiv(printMargin.bottom, afxData.cyPixelsPerInch, dc->GetDeviceCaps(LOGPIXELSY));

	// 수직 치수를 기준으로 비율을 사용할 것인지 확인
	nNum = previewScreenRect.bottom;
	nDen = previewSize.cy;

	// 조정된 너비가 더 큰 경우 너비를 기준으로 비율 측정
	if (MulDiv(previewScreenRect.right, nNum, nDen) > previewSize.cx) {
		nNum = previewScreenRect.right;
		nDen = previewSize.cx;
	}

	ratio.cx = nNum;
	ratio.cy = nDen;

	// 비율로 미리보기 용지 크기 줄인다.
	previewSize.cx = MulDiv(previewSize.cx, ratio.cx, ratio.cy);
	previewSize.cy = MulDiv(previewSize.cy, ratio.cx, ratio.cy);

	// 비율로 여백을 줄인다.
	previewMargin.left = MulDiv(previewMargin.left, ratio.cx, ratio.cy);
	previewMargin.top = MulDiv(previewMargin.top, ratio.cx, ratio.cy);
	previewMargin.right = MulDiv(previewMargin.right, ratio.cx, ratio.cy);
	previewMargin.bottom = MulDiv(previewMargin.bottom, ratio.cx, ratio.cy);

	// 미리보기 용지 크기를 구한다.
	previewRect.SetRect(3, 3, previewSize.cx - 3, previewSize.cy - 3);

	// 용지를 중앙으로 이동
	previewRect.OffsetRect((previewScreenRect.right - previewRect.Size().cx) / 2 - 1,
		(previewScreenRect.bottom - previewRect.Size().cy) / 2 - 1);

	// 8. 미리보기의 적을 범위를 구한다. 구한 용지에서 여백빼기.
	previewWriteRect = previewRect;
	previewRect.left += previewMargin.left;
	previewRect.top += previewMargin.top;
	previewRect.right -= previewMargin.right;
	previewRect.bottom -= previewMargin.bottom;

	// 9. 글자 크기를 구한다.
	letterWidth = previewSize.cx / columnCount;
	letterHeight = previewSize.cy / rowCount;

	// 10. 미리보기 용지의 폰트를 구한다.
	CFont font;
	font.CreateFontA(letterHeight, letterWidth, notepadFont.lfEscapement, notepadFont.lfOrientation, notepadFont.lfWeight,
		notepadFont.lfItalic, notepadFont.lfUnderline, notepadFont.lfStrikeOut, notepadFont.lfCharSet, notepadFont.lfOutPrecision, 
		notepadFont.lfClipPrecision, notepadFont.lfQuality, notepadFont.lfPitchAndFamily, notepadFont.lfFaceName);

	font.GetLogFont(&previewLogFont);

	if (this->notepadPage != 0) {
		delete this->notepadPage;
	}
	//this->notepadPage = new PageInfo(printRect, printMargin, printWriteRect, printerLogFont);

	if (this->previewPage != 0) {
		delete this->previewPage;
	}
	//this->previewPage = new PageInfo(previewRect, previewMargin, previewWriteRect, previewLogFont);

	dc->SelectObject(oldFont);
	DeleteObject(hFont);
}
#if 0
CRect Printer::GetPrintPageRect() {
	//int nPageWidth = GetDeviceCaps(this->printerDC, HORZRES);
	// PHYSICALOFFSETX : 인쇄 가능한 영역과 용지와의 거리를 장치 단위로 조사, PHYSICALWIDTH : 여백을 제외한 중앙 부분
	//인쇄할 높이를 픽셀값으로 얻는다. PHYSICALWIDTH, PHYSICALHEIGHT
	//int nPageHeight = GetDeviceCaps(this->printerDC, VERTRES);
	// PHYSICALOFFSETY : 인쇄 가능한 영역과 용지와의 거리를 장치 단위로 조사, PHYSICALHEIGHT : 여백을 제외한 중앙 부분
	return this->notepadPage->GetPageRect();
}

CRect Printer::GetPreviewPageRect() {
	return this->previewPage->GetPageRect();
}
#endif
CRect Printer::GetPrintPageMargin() {
	return this->notepadPage->GetMargin();
}

CRect Printer::GetPreviewPageMargin() {
	return this->previewPage->GetMargin();
}
#if 0
CRect Printer::GetPrintWriteRect() {
	return this->notepadPage->GetWriteRect();
}

CRect Printer::GetPreviewWriteRect() {
	return this->previewPage->GetWriteRect();
}

LOGFONT Printer::GetPrintLogFont() {
	return this->notepadPage->GetLogFont();
}

LOGFONT Printer::GetPreviewLogFont() { // 폰트는 제대로 구했고 여백이 문제. 여백을 참고해서 구하자.
	return this->previewPage->GetLogFont();
}
#endif
void Printer::SetDC(HDC printerDC) {
	if (this->printerDC != 0) {
		DeleteDC(this->printerDC);
	}
	this->printerDC = printerDC;
}