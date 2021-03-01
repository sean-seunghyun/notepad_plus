// PreviewCommand.cpp
/*
파일명칭 : PreviewCommand.cpp
기능 : 미리보기 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.29
*/
#include "PreviewCommand.h"
#include "PrintPreviewForm.h"
#include "NotepadForm.h"
#include "Printer.h"
#include "PageSetupDialog.h"
#include <afxdlgs.h>
#include <afxstat_.h>
#include <afxdisp.h>

PreviewCommand::PreviewCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

PreviewCommand::~PreviewCommand() {
}

void PreviewCommand::Execute() {
	PageSetupDialog dlg(PSD_MARGINS | PSD_RETURNDEFAULT, this->notepadForm);
	dlg.DoModal();
	this->notepadForm->printer->SetDC(dlg.CreatePrinterDC());

	PrintPreviewForm *printPreviewForm = new PrintPreviewForm(this->notepadForm);
	printPreviewForm->Create(NULL, "미리보기");
	printPreviewForm->ShowWindow(SW_SHOW);
	printPreviewForm->UpdateWindow();
}