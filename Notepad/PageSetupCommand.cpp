// PageSetUpCommand.cpp
/*
파일명칭 : PageSetUpCommand.cpp
기능 : 페이지 설정 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.29
*/

#include"PageSetupCommand.h"
#include"NotepadForm.h"
#include"PageSetupDialog.h"
#include"PageInfo.h"

PageSetupCommand::PageSetupCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

PageSetupCommand::~PageSetupCommand() {

}

void PageSetupCommand::Execute() {
	PageSetupDialog PageSetupDialog(PSD_INHUNDREDTHSOFMILLIMETERS | PSD_MARGINS |
		PSD_ENABLEPAGEPAINTHOOK, this->notepadForm);
	RECT margin;
	CString header;
	CString footer;

	margin = this->notepadForm->pageInfo->GetMargin();

	PageSetupDialog.m_psd.rtMargin.top = margin.top;
	PageSetupDialog.m_psd.rtMargin.left = margin.left;
	PageSetupDialog.m_psd.rtMargin.right = margin.right;
	PageSetupDialog.m_psd.rtMargin.bottom = margin.bottom;


	
	PAGESETUPDLG& psd = PageSetupDialog.m_psd;
	PRINTDLG printDialog;
	printDialog.hDevNames = NULL;
	printDialog.hDevMode = NULL;
	AfxGetApp()->GetPrinterDeviceDefaults(&printDialog);
	psd.hDevNames = printDialog.hDevNames;
	psd.hDevMode = printDialog.hDevMode;
	LPDEVMODE pDevMode = PageSetupDialog.GetDevMode();
	short dmOrientation = pDevMode->dmOrientation;
	GlobalUnlock(pDevMode);


	PageSetupDialog.DoModal();

}