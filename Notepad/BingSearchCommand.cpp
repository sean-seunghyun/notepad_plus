// BingSearchCommand.cpp
/*
파일명칭 : BingSearchCommand.cpp
기능 : 비잉으로 검색 명령 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.02.02
*/
#include "BingSearchCommand.h"
#include "NotepadForm.h"
#include "Glyph.h"

BingSearchCommand::BingSearchCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

BingSearchCommand::~BingSearchCommand() {
}

void BingSearchCommand::Execute() {
	CString text = this->notepadForm->note->GetSelectString().c_str();
	CString searchMessage;
	searchMessage.Format("https://www.bing.com/search?q=%s", text);
	::ShellExecute(NULL, _T("open"), _T("chrome.exe"), searchMessage, NULL, SW_SHOW);
}