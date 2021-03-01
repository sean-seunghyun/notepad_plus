// HelpCommand.cpp
/*
파일명칭 : HelpCommand.cpp
기능 : 도움말 보기 명령 클래스를 만든다.
작성자 : 정성원
작성일자 : 2020.09.25
*/
#include "HelpCommand.h"
#include "NotepadForm.h"
#include "resource.h"
#include <htmlhelp.h>
#pragma comment(lib, "htmlhelp")

HelpCommand::HelpCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

HelpCommand::~HelpCommand() {
}

void HelpCommand::Execute() {//GetHelpFile().c_str()//"C:\\Users\\jeong\\Downloads\\helpdocs\\Notepad User Manual.chm::/Intro.htm>Mainwin"
	HWND hwnd = HtmlHelpA(GetDesktopWindow(), "notepad.chm", HH_DISPLAY_TOPIC, NULL);
}