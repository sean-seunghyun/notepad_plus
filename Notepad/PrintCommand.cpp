// PrintCommand.cpp
/*
파일명칭 : PrintCommand.cpp
기능 : 인쇄 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.29
*/
#include"PrintCommand.h"
#include"NotepadForm.h"
#include"Glyph.h"
#include"Matrix.h"
#include"Font.h"
#include"PageInfo.h"
#include<afxdlgs.h>
#include"File.h"
#include<afxpriv.h>

PrintCommand::PrintCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

PrintCommand::~PrintCommand() {

}

void PrintCommand::Execute() {
	CPrintDialog dlg(FALSE);
	DOCINFO di;
	CDC *cdc;
	Long printWidth;
	Long printHeight;

	Long j;
	Long i = 0;

	bool onIsKorean = false;

	string linestr;

	CFont font;
	LOGFONT logFont;

	RECT margin;
	CString header;
	CString footer;
	Long devMode;
	string fileTitle;


	if (dlg.DoModal() == IDOK) {
		//docInfo 작성
		memset(&di, 0, sizeof(DOCINFO));
		di.cbSize = sizeof(DOCINFO);
		fileTitle = this->notepadForm->file->GetTitle();
		di.lpszDocName = fileTitle.c_str();

		//dc정보읽기
		cdc = CDC::FromHandle(dlg.GetPrinterDC());

		//가로세로 정보 설정
		devMode = this->notepadForm->pageInfo->GetDevMode();
		if (devMode != 1) {//가로모드로 설정이 되어있으면
			DEVMODE *pDevMode = dlg.GetDevMode();
			pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
			cdc->ResetDCA(pDevMode);
		}

#if 0
		//용지 설정
		paperSize = this->notepadForm->pageInfo->GetPaperSize();
		printWidth = paperSize.x;
		printHeight = paperSize.y;
#endif
		printWidth = cdc->GetDeviceCaps(HORZRES);
		printHeight = cdc->GetDeviceCaps(VERTRES);

		//폰트 적용
		logFont = this->notepadForm->font->GetLogFont();
		logFont.lfHeight = -((logFont.lfHeight * cdc->GetDeviceCaps(LOGPIXELSY)) / 96);
		font.CreateFontIndirectA(&logFont);
		TEXTMETRIC metric;
		CFont *def_font = cdc->SelectObject(&font);
		cdc->GetTextMetrics(&metric);

		//페이지 여백설정
		margin = this->notepadForm->pageInfo->GetMargin();
		header = this->notepadForm->pageInfo->GetHeader();
		footer = this->notepadForm->pageInfo->GetFooter();


		CRect writeRect(0 + (int)(margin.left*0.24), 0 + (int)(margin.top*0.24),
			printWidth - (int)(margin.right*0.24), printHeight - (int)(margin.bottom*0.24));

		if (header.Compare("") != 0) {
			writeRect.top += (metric.tmHeight);
		}
		if (footer.Compare("") != 0) {
			writeRect.bottom -= (metric.tmHeight);
		}



		CRect headerRect(0, 0, printWidth, printHeight + (metric.tmHeight));
		CRect footerRect(0, printHeight - (metric.tmHeight), printWidth, printHeight);
		cdc->SetMapMode(MM_TEXT);
		CString noteString = CString(this->notepadForm->note->GetString().c_str());
		char *p = noteString.GetBuffer(noteString.GetLength());
		char *startAt = p;

		//인쇄 시작
		CRect           r;
		int             nHeight;
		CPrintInfo info;
		info.m_rectDraw.SetRect(writeRect.left, writeRect.top, writeRect.right, writeRect.bottom);


		int totalDone = 0;
		int lengthToGo = noteString.GetLength();



		// 도큐먼트 인쇄 시작
		BOOL bPrintingOK = cdc->StartDoc(&di);

		// 페이지를 인쇄하는 루프
		for (UINT page = info.GetMinPage(); bPrintingOK && totalDone < lengthToGo; page++) {
			// 페이지 인쇄 시작
			cdc->StartPage();
			info.m_nCurPage = page;
			// calc how much text fits on one page
			r = info.m_rectDraw;
			r.bottom = r.top;
			j = 0;
			while (r.bottom < info.m_rectDraw.bottom && totalDone + j < lengthToGo) {
				r.right = info.m_rectDraw.right;

				if ((startAt[j] & 0x80) == 0) {//영문이면
					j = j + 1;
					onIsKorean = false;
				}
				else if ((startAt[j] & 0x80) != 0) {//한글이면
					j = j + 2;
					onIsKorean = true;
				}

				nHeight = cdc->DrawText(startAt, j, r, DT_CALCRECT | DT_WORDBREAK | DT_EDITCONTROL | DT_EXPANDTABS);
			}

			// go one back to assure correct height
			if (r.bottom >= info.m_rectDraw.bottom && onIsKorean == true) {
				j -= 2;
			}
			else if (r.bottom >= info.m_rectDraw.bottom) {
				j--;
			}

			//머릿말 꼬릿말 인쇄
			cdc->DrawText(header, &headerRect, DT_CENTER);
			cdc->DrawText(footer, &footerRect, DT_CENTER);

			// print that text
			cdc->DrawText(startAt, j, info.m_rectDraw, DT_WORDBREAK | DT_EDITCONTROL | DT_EXPANDTABS);

			// go to next page


			startAt += j;
			totalDone += j;

			// 페이지 인쇄 완료
			bPrintingOK = (cdc->EndPage() > 0);
		}
		noteString.ReleaseBuffer();

		// 도큐먼트 인쇄 종료
		if (bPrintingOK) cdc->EndDoc();
		else cdc->AbortDoc();
		cdc->SelectObject(def_font);

		font.DeleteObject();
		//dc할당해제
		cdc->DeleteDC();
	}
}