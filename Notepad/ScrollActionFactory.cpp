// ScrollActionFactory.cpp
/*
파일명칭 : ScrollActionFactory.cpp
기능 : 이동 스크롤 펙토리 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.13
*/
#include "ScrollActionFactory.h"
#include "ScrollAction.h"
#include "FirstScrollAction.h"
#include "LinePreviousScrollAction.h"
#include "LineNextScrollAction.h"
#include "PagePreviousScrollAction.h"
#include "PageNextScrollAction.h"
#include "ThumbTrackScrollAction.h"
#include "LastScrollAction.h"

#define SB_LINEPREVIOUS 0 // SB_LINEUP, SB_LINELEFT
#define SB_LINENEXT 1 // SB_LINEDOWN, SB_LINERIGHT
#define SB_PAGEPREVIOUS 2 // SB_PAGEUP, SB_PAGELEFT
#define SB_PAGENEXT 3 // SB_PAGEDOWN, SB_PAGERIGHT
#define SB_FIRST 6 // SB_TOP, SB_LEFT
#define SB_LAST 7 // SB_BOTTOM, SB_RIGHT

ScrollActionFactory::ScrollActionFactory(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

ScrollActionFactory::~ScrollActionFactory() {
}

ScrollAction* ScrollActionFactory::Create(UINT nSBCode) {
	ScrollAction* scrollAction = 0;

	switch (nSBCode) {
	case SB_LINEPREVIOUS:
		scrollAction = new LinePreviousScrollAction(this->notepadForm);
		break;

	case SB_LINENEXT:
		scrollAction = new LineNextScrollAction(this->notepadForm);
		break;

	case SB_PAGEPREVIOUS:
		scrollAction = new PagePreviousScrollAction(this->notepadForm);
		break;

	case SB_PAGENEXT:
		scrollAction = new PageNextScrollAction(this->notepadForm);
		break;

	case SB_THUMBTRACK:
		scrollAction = new ThumbTrackScrollAction(this->notepadForm);
		break;

	case SB_FIRST:
		scrollAction = new FirstScrollAction(this->notepadForm);
		break;

	case SB_LAST:
		scrollAction = new LastScrollAction(this->notepadForm);
		break;

	default:
		break;
	}

	return scrollAction;
}