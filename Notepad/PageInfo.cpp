// PageInfo.cpp
/*
파일명칭 : PageInfo.cpp
기능 : 인쇄 정보 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.29
*/
#include "PageInfo.h"
#include"PageSetupDialog.h"
#include"NotepadForm.h"
#include<afxdlgs.h>

PageInfo::PageInfo(NotepadForm *notepadForm)
	:header(""), footer("") {
	RECT margin = { 0, };
	tagPOINT paperSize;

	margin.top = 2000;
	margin.left = 2500;
	margin.right = 2500;
	margin.bottom = 2000;
	this->margin = margin;

	paperSize.x = 21000;
	paperSize.y = 29700;
	this->paperSize = paperSize;

	this->devMode = 1;
#if 0
	DEVMODE dev;
	dev.dmOrientation = 1;
	this->devMode = &dev;
#endif
}

PageInfo::PageInfo(POINT paperSize, Long devMode, RECT margin, CString header, CString footer)
	:paperSize(paperSize), margin(margin), header(header), footer(footer) {
	this->devMode = devMode;
}

PageInfo::~PageInfo() {


}