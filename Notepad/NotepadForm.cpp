// NotepadForm.cpp
/*
파일명칭 : NotepadForm.cpp
기능 : 메모지철 윈도우 클래스를 만든다.
작성자 : 김승현, 정성원
작성일자 : 2021.01.07
객체지향 갱신 내역 : 
인터페이스 갱신 내역 : 
갱신해야 될 내역 : 페이지 단위 이동, State 만들기, 글자 적기 Command 추가하기
주의할 내역 : -
*/
#include "NotepadForm.h"
#include "Glyph.h"
#include "GlyphFactory.h"
#include "Command.h"
#include "EditCommand.h"
#include "CommandFactory.h"
#include "KeyAction.h"
#include "KeyActionFactory.h"
#include "File.h"
#include "Matrix.h"
#include "Font.h"
#include "CommandHistory.h"
#include "Clipboard.h"
#include "Printer.h"
#include "PageInfo.h"
#include "Scroll.h"
#include "ScrollAction.h"
#include "ScrollActionFactory.h"
#include "CaretController.h"
#include "ScrollController.h"
#include "DragBox.h"
#include <afxdlgs.h>
#include <afxext.h>
#include "resource.h"

HHOOK hSaveMessageBoxHook;
static UINT NEAR WM_FIND = ::RegisterWindowMessage(FINDMSGSTRING);
static UINT indicators[] =
{
	IDS_INDICATOR_VOID,
	IDS_INDICATOR_POINT,
	IDS_INDICATOR_ZOOM,
	IDS_INDICATOR_EOL,
	IDS_INDICATOR_ENCODING,
};

BEGIN_MESSAGE_MAP(NotepadForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEHWHEEL()
	ON_COMMAND_RANGE(40001, 40037, OnRangeCmds)
	ON_UPDATE_COMMAND_UI(IDS_INDICATOR_POINT, OnUpdatePoint)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_STARTCOMPOSITION, OnImeStartComposition)
	ON_MESSAGE(WM_IME_COMPOSITION, OnImeComposition)
	ON_MESSAGE(WM_IME_CHAR, OnImeChar)
	ON_REGISTERED_MESSAGE(WM_FIND, OnFindReplace)
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

NotepadForm::NotepadForm() {
	this->pFindReplaceDialog = NULL;
	this->note = NULL;
	this->current = NULL;
	this->file = NULL;
	this->font = NULL;
	this->matrix = NULL;
	this->commandHistory = NULL;
	this->clipboard = NULL;
	//this->printer = NULL;
	this->pageInfo = NULL;
	this->contextMenu = NULL;
	this->caretController = NULL;
	this->scrollController = NULL;
	this->statusBar = NULL;
	this->onIsComposing = FALSE;
	this->onIsSaving = FALSE;
	this->onIsMoving = FALSE;
	this->onIsScrolling = FALSE;
	this->onIsLineWrapping = FALSE;
	this->onIsSaveCanceled = FALSE;
	this->onIsFound = FALSE;
	this->onIsOpeningFindReplace = FALSE;
	this->onIsIBeam = FALSE;
	this->onIsDraging = FALSE;
	this->onIsDoubleClicked = FALSE;
}

BOOL NotepadForm::PreTranslateMessage(MSG *pMsg) {// 액셀러레이터 추가(2021.01.22)
	// 키보드 메시지를 WM_COMMAND 메시지로 변경하여 액셀러레이터가 동작할 수 있도록 한다.
	// 예를 들어, 위의 그림과 같이 액셀러레이터에 Ctrl+A 가 입력되었을 때 Ctrl+A 는 액셀러레이터이기
	// 이전에 키보드로부터 입력을 먼저 받았기 때문에 WM_KEYDOWN 메시지가 발생할 것이다.
	// 그러면 WndProc 의 WM_KEYDOWN 메시지 처리루틴에서 먼저 이 키값을 처리해 버릴 것이다.
	// TranslateAccelerator 함수는 pMsg 의 키보드 입력값을 읽어 이 키값이 hAccTable 에 있는지
	// 먼저 살펴보고 테이블에 있을 경우 그 키에 해당하는 WM_COMMAND 메시지를 hWnd 윈도우로
	// 전달하고 TRUE 를 반환하다.
	if (this->m_hAccelTable != NULL) {
		if (::TranslateAccelerator(this->m_hWnd, this->m_hAccelTable, pMsg)) {
			return TRUE;
		}
	}

	return CFrameWnd::PreTranslateMessage(pMsg);
}

int NotepadForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);

	this->ModifyStyle(0, WS_OVERLAPPEDWINDOW, SWP_DRAWFRAME);

	this->m_hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_MAINFRAME));
	this->SetIcon(this->m_hIcon, ICON_SMALL);
	// 액셀러레이터 추가(2021.01.22)
	this->m_hAccelTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));

	this->m_bAutoMenuEnable = FALSE;
	this->m_hMenu = LoadMenu(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDM_MAINMENU));
	this->SetMenu(CMenu::FromHandle(this->m_hMenu));

	// 컨텍스트 메뉴 추가(2021.02.02)
	this->contextMenu = new CMenu;
	this->contextMenu->CreatePopupMenu();
	this->contextMenu->AppendMenu(MF_STRING, IDM_EDIT_UNDO, "실행취소(&U)");
	this->contextMenu->AppendMenu(MF_STRING, IDM_EDIT_REDO, "다시실행(&R)");
	this->contextMenu->AppendMenu(MF_SEPARATOR);
	this->contextMenu->AppendMenu(MF_STRING, IDM_EDIT_CUT, "잘라내기(&T)");
	this->contextMenu->AppendMenu(MF_STRING, IDM_EDIT_COPY), "복사(&C)";
	this->contextMenu->AppendMenu(MF_STRING, IDM_EDIT_PASTE, "붙여넣기(&P)");
	this->contextMenu->AppendMenu(MF_STRING, IDM_EDIT_DELETE, "삭제(&D)");
	this->contextMenu->AppendMenu(MF_SEPARATOR);
	this->contextMenu->AppendMenu(MF_STRING, IDM_EDIT_SELECT_ALL, "모두 선택(&A)");

	// 1. 종이를 만든다.
	GlyphFactory glyphFactory;
	this->note = glyphFactory.Create((char*)0);

	// 2. 줄을 만든다.
	this->current = glyphFactory.Create((char*)"\r");

	// 3. 종이에서 줄을 추가한다.
	this->note->Add(this->current);
	this->note->First();

	// 4. 파일을 만든다.
	this->file = new File(this);

	// 5. 글자 모양을 정한다. 
	// + 레지스트리에 정보를 가져오고 없으면 기본 값으로 만든다. (2021.01.08)
	this->onIsLineWrapping = !(BOOL)AfxGetApp()->GetProfileInt("NotepadSection", "OnIsWrap", 1);
	this->onIsStatusBar = !(BOOL)AfxGetApp()->GetProfileInt("NotepadSection", "OnIsStatusBar", 1);
	
	CString faceName;
	faceName = AfxGetApp()->GetProfileString("NotepadSection", "FaceName", "맑은 고딕");
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	strcpy_s(lf.lfFaceName, (LPCTSTR)faceName);
	lf.lfHeight = AfxGetApp()->GetProfileInt("NotepadSection", "LogFontHeight", -27); // -27은 16폰트
	lf.lfWidth = AfxGetApp()->GetProfileInt("NotepadSection", "LogFontWidth", 0);

	COLORREF color;
	memset(&color, 0, sizeof(COLORREF));
	color = GetSysColor(COLOR_DESKTOP);

	this->font = new Font(lf, color);

	this->matrix = new Matrix(this);

	// + 명령 기록을 만든다.
	this->commandHistory = new CommandHistory(this);

	// + 필기판을 만든다. (20201.01.19) Clipboard
	this->clipboard = new Clipboard(this);

	// + 인쇄기를 만든다.
	//this->printer = new Printer(this);

	// + 페이지정보를 만든다.
	this->pageInfo = new PageInfo(this);

	// 6. 스크롤바를 만든다.(2021.01.21)
	this->verticalScrollBar = new CScrollBar;
	this->verticalScrollBar->Create(SBS_VERT | SBPS_NORMAL | WS_CHILD, CRect(0, 0, 0, 0), this, NULL);
	this->horizontalScrollBar = new CScrollBar;
	this->horizontalScrollBar->Create(SBS_HORZ | SBPS_NORMAL | WS_CHILD, CRect(0, 0, 0, 0), this, NULL);
	this->sizeBox = new CScrollBar;
	this->sizeBox->Create(SBS_SIZEBOX | WS_CHILD, CRect(0, 0, 0, 0), this, NULL);

	// 스크롤 컨트롤러를 만든다.
	this->scrollController = new ScrollController(this);

	// 7. 상태바를 만든다.
	this->statusBar = new CStatusBar;
	this->statusBar->CreateEx(this, WS_CHILD | CBRS_BOTTOM);
	this->statusBar->SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	Long i = 0;
	while (i < sizeof(indicators) / sizeof(UINT)) {
		this->statusBar->SetPaneInfo(i, indicators[i], 0, 0);
		i++;
	}

	this->ShowControlBar(this->statusBar, FALSE, FALSE);

	// 8. 자동개행이면 메뉴를 체크해준다.
	if (this->onIsLineWrapping == TRUE) {
		this->SendMessage(WM_COMMAND, IDM_FORMAT_WRAPUI);
	}
	// 9. 상태바가 체크되어 있으면 보여준다.
	if (this->onIsStatusBar == TRUE) {
		this->SendMessage(WM_COMMAND, IDM_VIEW_STATUSBAR);
	}

	// 갱신한다. (2021.01.08), 
	this->Notify();

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	return 0;
}

void NotepadForm::OnContextMenu(CWnd *pCWnd, CPoint point) {
	// TODO: Add your message handler code here
	this->contextMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd());
}

void NotepadForm::OnSize(UINT nType, int cx, int cy) {
	CFrameWnd::OnSize(nType, cx, cy);
	LONG current;
	LONG remaining;

	if (this->onIsStatusBar == TRUE) {
		this->statusBar->SetPaneInfo(4, IDS_INDICATOR_ENCODING, 0, 140);

		remaining = cx - 140;
		if (remaining > 0 && remaining > 140) {
			this->statusBar->SetPaneInfo(3, IDS_INDICATOR_EOL, 0, 140);
			remaining -= 140;
		}
		else if (remaining > 0) {
			this->statusBar->SetPaneInfo(3, IDS_INDICATOR_EOL, 0, remaining);
			remaining -= remaining;
		}
		else {
			this->statusBar->SetPaneInfo(3, IDS_INDICATOR_EOL, 0, 0);
			remaining = 0;
		}

		if (remaining > 0 && remaining > 60) {
			this->statusBar->SetPaneInfo(2, IDS_INDICATOR_ZOOM, 0, 60);
			remaining -= 60;
		}
		else if (remaining > 0) {
			this->statusBar->SetPaneInfo(2, IDS_INDICATOR_ZOOM, 0, remaining);
			remaining -= remaining;
		}
		else {
			this->statusBar->SetPaneInfo(2, IDS_INDICATOR_ZOOM, 0, 0);
			remaining = 0;
		}

		if (remaining > 0 && remaining > 120) {
			this->statusBar->SetPaneInfo(1, IDS_INDICATOR_POINT, 0, 120);
			remaining -= 120;
		}
		else if (remaining > 0) {
			this->statusBar->SetPaneInfo(1, IDS_INDICATOR_POINT, 0, remaining);
			remaining -= remaining;
		}
		else {
			this->statusBar->SetPaneInfo(1, IDS_INDICATOR_POINT, 0, 0);
			remaining = 0;
		}

		if (remaining > 0) {
			this->statusBar->SetPaneInfo(0, IDS_INDICATOR_VOID, 0, remaining);
		}
		else {
			this->statusBar->SetPaneInfo(0, IDS_INDICATOR_VOID, 0, 0);
		}
	}

	if(this->note != NULL && nType != SIZE_MINIMIZED) {
		if (this->onIsLineWrapping == TRUE) {
			this->note->CombineAll();
			current = this->note->GetCurrent();
			this->current = this->note->GetAt(current);
			this->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
		}
		this->Notify();
	}

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void NotepadForm::OnSetFocus(CWnd *pCWnd) {
	if (this->matrix != 0 && this->caretController == NULL) {
		this->caretController = new CaretController(this);

		this->Notify();
		this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}
}

void NotepadForm::OnKillFocus(CWnd *pCWnd) {
	dynamic_cast<Subject*>(this)->Detach(this->caretController);
	this->caretController = NULL;
}

BOOL NotepadForm::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {
	BOOL ret = TRUE;
	if (this->onIsIBeam == TRUE) {
		SetCursor(LoadCursor(NULL, IDC_IBEAM));
	}
	else {
		ret = CFrameWnd::OnSetCursor(pWnd, nHitTest, message);
	}

	return ret;
}

void NotepadForm::OnLButtonDown(UINT nFlags, CPoint point) {
	LONG lineCurrent = this->current->GetCurrent();
	LONG noteCurrent = this->note->GetCurrent();
	LONG startLineCurrent;
	LONG startNoteCurrent;
	LONG endLineCurrent;
	LONG endNoteCurrent;
	LONG firstLineCurrent = lineCurrent;
	LONG firstNoteCurrent = noteCurrent;

	this->prevPoint = point;

	// 1. 선택된 첫번째 위치를 구한다.
	if ((GetKeyState(VK_SHIFT) & 0x8000)) {
		this->note->GetSelectRange(&startLineCurrent, &startNoteCurrent, &endLineCurrent, &endNoteCurrent);
		firstLineCurrent = startLineCurrent;
		firstNoteCurrent = startNoteCurrent;
		if (firstLineCurrent == lineCurrent && firstNoteCurrent == noteCurrent) {
			firstLineCurrent = endLineCurrent;
			firstNoteCurrent = endNoteCurrent;
		}
	}

	noteCurrent = this->matrix->GetNoteCurrent(point.y + this->scrollController->GetVerticalScroll()->GetCurrent());
	this->note->Move(noteCurrent);
	this->current = this->note->GetAt(noteCurrent);

	lineCurrent = this->matrix->GetLineCurrent(point.x + this->scrollController->GetHorizontalScroll()->GetCurrent());
	this->current->Move(lineCurrent);

	this->onIsComposing = FALSE;
	
	this->note->SelectAll(false);
	if ((GetKeyState(VK_SHIFT) & 0x8000)) {
		this->note->Select(firstLineCurrent, firstNoteCurrent, lineCurrent, noteCurrent, true);
	}

	this->onIsDraging = TRUE;

	this->SetCapture();

	this->Notify();

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void NotepadForm::OnLButtonDblClk(UINT nFlags, CPoint point) {
	LONG startLineCurrent;
	LONG startNoteCurrent;
	LONG lineCurrent;
	LONG lineLength;
	LONG noteCurrent;

	this->onIsComposing = FALSE;

	if (this->prevPoint == point) {
		lineLength = this->current->GetLength();
		if (this->onIsLineWrapping == TRUE) {
			noteCurrent = this->note->GetCurrent();
			this->note->Combine(noteCurrent);
			noteCurrent = this->note->GetCurrent();
			this->current = this->note->GetAt(noteCurrent);
		}
		if (lineLength > 0) {
			this->current->PreviousWord();

			startNoteCurrent = this->note->GetCurrent();
			startLineCurrent = this->current->GetCurrent();

			this->current->NextWord();

			noteCurrent = this->note->GetCurrent();
			lineCurrent = this->current->GetCurrent();

			this->note->SelectAll(false);
			this->note->Select(startLineCurrent, startNoteCurrent, lineCurrent, noteCurrent, true);
		}
		if (this->onIsLineWrapping == TRUE) {
			this->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
		}

		this->onIsComposing = FALSE;
		this->onIsDoubleClicked = TRUE;

		this->Notify();

		this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}
}

void NotepadForm::OnMouseMove(UINT nFlags, CPoint point) { // 스크롤바와 상태바를 뺀 영역의 틈새에 드래깅하면 1줄씩 이동하며 선택
	CRect rect;
	CRect tempRect;

	LONG lineCurrent = this->current->GetCurrent();
	LONG noteCurrent = this->note->GetCurrent();
	LONG startLineCurrent;
	LONG startNoteCurrent;
	LONG endLineCurrent;
	LONG endNoteCurrent;
	LONG firstLineCurrent = lineCurrent;
	LONG firstNoteCurrent = noteCurrent;
	LONG x;

	UINT scrollCurrent;

	this->GetClientRect(&rect);

	if (this->onIsVerticalScrollBar == TRUE) {
		rect.right -= GetSystemMetrics(SM_CXVSCROLL);
	}
	if (this->onIsHorizontalScrollBar == TRUE && this->onIsLineWrapping != TRUE) {
		rect.bottom -= GetSystemMetrics(SM_CYHSCROLL);
	}
	if (this->onIsStatusBar == TRUE) {
		rect.bottom -= GetSystemMetrics(SM_CYHSCROLL);
	}

	tempRect.left = rect.left;
	tempRect.top = rect.top;
	tempRect.right = rect.right - 2;
	tempRect.bottom = rect.bottom - 2;

	if (tempRect.PtInRect(point) != 0) {
		this->onIsIBeam = TRUE;
	}
	else {
		this->onIsIBeam = FALSE;
	}

	this->SendMessage(WM_SETCURSOR, 0, MAKELPARAM(HTCLIENT, WM_MOUSEMOVE));

	if (this->onIsDraging == TRUE) { // 캐럿을 이동시키고 그 캐럿 위치로 선택하며 스크롤되는 원리.
		this->note->GetSelectRange(&startLineCurrent, &startNoteCurrent, &endLineCurrent, &endNoteCurrent);
		firstLineCurrent = startLineCurrent;
		firstNoteCurrent = startNoteCurrent;
		if (firstLineCurrent == lineCurrent && firstNoteCurrent == noteCurrent) {
			firstLineCurrent = endLineCurrent;
			firstNoteCurrent = endNoteCurrent;
		}
		
		x = this->matrix->GetX(lineCurrent) - this->scrollController->GetHorizontalScroll()->GetCurrent();
		if (x > point.x && (rect.left > point.x || rect.right < point.x)) {
			scrollCurrent = this->scrollController->GetHorizontalScroll()->GetCurrent() - this->matrix->GetWidth(128) / 2 * 3;
			if (rect.right < point.x) {
				scrollCurrent = this->scrollController->GetHorizontalScroll()->GetCurrent() + this->matrix->GetWidth(128) / 2 * 3;
			}
			this->SendMessage(WM_HSCROLL, MAKELONG(SB_THUMBTRACK, scrollCurrent));
		}
		if (rect.top > point.y || rect.bottom < point.y) {
			scrollCurrent = this->scrollController->GetVerticalScroll()->GetCurrent() - this->matrix->GetHeight() * 2;
			if (rect.bottom < point.y) {
				scrollCurrent = this->scrollController->GetVerticalScroll()->GetCurrent() + this->matrix->GetHeight() * 2;
			}
			this->SendMessage(WM_VSCROLL, MAKELONG(SB_THUMBTRACK, scrollCurrent));
		}

		noteCurrent = this->matrix->GetNoteCurrent(point.y + this->scrollController->GetVerticalScroll()->GetCurrent());
		this->note->Move(noteCurrent);
		this->current = this->note->GetAt(noteCurrent);

		lineCurrent = this->matrix->GetLineCurrent(point.x + this->scrollController->GetHorizontalScroll()->GetCurrent());
		this->current->Move(lineCurrent);

		this->note->SelectAll(false);
		this->note->Select(firstLineCurrent, firstNoteCurrent, lineCurrent, noteCurrent, true);

		this->Notify();

		this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}
}

void NotepadForm::OnNcMouseMove(UINT nHitTest, CPoint point) {
	CFrameWnd::OnNcMouseMove(nHitTest, point);
	this->onIsIBeam = FALSE;
	this->SendMessage(WM_SETCURSOR, 0, MAKELPARAM(nHitTest, WM_NCMOUSEMOVE));
}

void NotepadForm::OnLButtonUp(UINT nFlags, CPoint point) {
	ReleaseCapture();

	this->onIsDraging = FALSE;
	this->onIsDoubleClicked = FALSE;
}

BOOL NotepadForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint point) {
	SCROLLINFO scrollInfo;

	UINT scrollCurrent = this->scrollController->GetVerticalScroll()->GetCurrent() + this->matrix->GetHeight() * 2;
	if (zDelta > 0) {
		scrollCurrent = this->scrollController->GetVerticalScroll()->GetCurrent() - this->matrix->GetHeight() * 2;
	}

	this->verticalScrollBar->GetScrollInfo(&scrollInfo);
	scrollInfo.nPos = scrollCurrent;
	this->verticalScrollBar->SetScrollInfo(&scrollInfo);

	this->SendMessage(WM_VSCROLL, MAKELONG(SB_THUMBTRACK, scrollCurrent));

	this->onIsScrolling = TRUE;
	this->Notify();
	this->onIsScrolling = FALSE;

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	return TRUE;
}

void NotepadForm::OnMouseHWheel(UINT nFlags, short zDelta, CPoint point) {
	SCROLLINFO scrollInfo;

	UINT scrollCurrent = this->scrollController->GetHorizontalScroll()->GetCurrent() + this->matrix->GetWidth(128) / 2 * 3;
	if (zDelta < 0) {
		scrollCurrent = this->scrollController->GetHorizontalScroll()->GetCurrent() - this->matrix->GetWidth(128) / 2 * 3;
	}

	this->horizontalScrollBar->GetScrollInfo(&scrollInfo);
	scrollInfo.nPos = scrollCurrent;
	this->horizontalScrollBar->SetScrollInfo(&scrollInfo);

	this->SendMessage(WM_HSCROLL, MAKELONG(SB_THUMBTRACK, scrollCurrent));

	this->onIsScrolling = TRUE;
	this->Notify();
	this->onIsScrolling = FALSE;

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void NotepadForm::OnRangeCmds(UINT nId) {
	CommandFactory commandFactory(this);
	Command *command;

	if ((nId == IDM_EDIT_FINDNEXT || nId == IDM_EDIT_FINDPREV) && this->onIsOpeningFindReplace != TRUE) {
		nId = IDM_EDIT_FIND;
		AfxGetApp()->WriteProfileString("NotepadSection", "FindString", "");
		this->onIsOpeningFindReplace = TRUE;
	}

	command = commandFactory.Create(nId);
	command->Execute();
	if (dynamic_cast<EditCommand*>(command) &&
		dynamic_cast<EditCommand*>(command)->GetOnIsCommandSaving() == true) {
		this->commandHistory->Save(command);
	}
	else if (command != NULL) {
		delete command;
	}
	
	this->onIsMoving = TRUE;
	this->Notify();
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void NotepadForm::OnUpdatePoint(CCmdUI *pCmdUI) {
	pCmdUI->Enable();

	Glyph *it;

	Long noteCurrent = this->note->GetCurrent();
	Long lineCurrent = 0;
	Long k = 0;
	Long j = 0;
	Long i = 0;
	while (i <= this->note->GetCurrent() && this->onIsLineWrapping == TRUE) {
		it = this->note->GetAt(i);
		if (it->GetOnIsLine() == true) {
			noteCurrent = j;
			j++;
			k = i;
		}
		i++;
	}

	while (k < this->note->GetCurrent() && this->onIsLineWrapping == TRUE) {
		it = this->note->GetAt(k);
		lineCurrent += it->GetLength();
		k++;
	}
	lineCurrent += this->current->GetCurrent();

	CString strPage;
	strPage.Format("Ln %d, Col %d", noteCurrent + 1, lineCurrent + 1);
	pCmdUI->SetText(strPage);
}

void NotepadForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	ScrollActionFactory scrollActionFactory(this);
	ScrollAction *scrollAction;
	scrollAction = scrollActionFactory.Create(nSBCode);

	SCROLLINFO scrollInfo;
	this->verticalScrollBar->GetScrollInfo(&scrollInfo);
	nPos = scrollInfo.nTrackPos;
	if (scrollAction != 0) {
		scrollAction->OnVScroll(nSBCode, nPos, pScrollBar);
		delete scrollAction;
	}

	this->onIsScrolling = TRUE;
	this->Notify();
	this->onIsScrolling = FALSE;

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void NotepadForm::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	ScrollActionFactory scrollActionFactory(this);
	ScrollAction *scrollAction;
	scrollAction = scrollActionFactory.Create(nSBCode);

	SCROLLINFO scrollInfo;
	this->horizontalScrollBar->GetScrollInfo(&scrollInfo);
	nPos = scrollInfo.nTrackPos;
	if (scrollAction != 0) {
		scrollAction->OnHScroll(nSBCode, nPos, pScrollBar);
		delete scrollAction;
	}

	this->onIsScrolling = TRUE;
	this->Notify();
	this->onIsScrolling = FALSE;

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void NotepadForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	KeyActionFactory keyActionFactory(this);
	KeyAction *keyAction;
	keyAction = keyActionFactory.Create(nChar);

	Long startLineCurrent;
	Long startNoteCurrent;
	Long endLineCurrent;
	Long endNoteCurrent;
	Long firstLineCurrent;
	Long firstNoteCurrent;
	Long lineCurrent = this->current->GetCurrent();
	Long noteCurrent = this->note->GetCurrent();

	// 1. 선택된 첫번째 위치를 구한다.
	if ((GetKeyState(VK_SHIFT) & 0x8000) && !(GetKeyState(VK_CONTROL) & 0x8000) ||
		((GetKeyState(VK_SHIFT) & 0x8000) && (GetKeyState(VK_CONTROL) & 0x8000) && (nChar >= 0x21 && nChar <= 0x28))) {
		this->note->GetSelectRange(&startLineCurrent, &startNoteCurrent, &endLineCurrent, &endNoteCurrent);
		firstLineCurrent = startLineCurrent;
		firstNoteCurrent = startNoteCurrent;
		if (firstLineCurrent == lineCurrent && firstNoteCurrent == noteCurrent) {
			firstLineCurrent = endLineCurrent;
			firstNoteCurrent = endNoteCurrent;
		}
	}

	if (keyAction != 0) {
		keyAction->OnKeyDown(nChar, nRepCnt, nFlags);
		delete keyAction;
	}

	// 2. 선택을 해제하고 3. Shift키가 눌러져 있으면 첫번째 위치와 이동된 위치까지 선택한다.
	if ((nChar >= 0x21 && nChar <= 0x28) || !(GetKeyState(VK_CONTROL) & 0x8000) && !(nChar == '\t' || nChar == '\n' || nChar == '\r' ||
		(nChar >= 32 && nChar < 127) || nChar & 0x80)) {
		this->note->SelectAll(false);
		this->onIsMoving = TRUE;
	}
	if ((GetKeyState(VK_SHIFT) & 0x8000) && !(GetKeyState(VK_CONTROL) & 0x8000) ||
		((GetKeyState(VK_SHIFT) & 0x8000) && (GetKeyState(VK_CONTROL) & 0x8000) && (nChar >= 0x21 && nChar <= 0x28))) {
		lineCurrent = this->current->GetCurrent();
		noteCurrent = this->note->GetCurrent();
		this->note->Select(firstLineCurrent, firstNoteCurrent, lineCurrent, noteCurrent, true);
	}

	this->Notify();
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void NotepadForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->letter[0] = nChar;
	this->letter[1] = '\0';

	this->SendMessage(WM_COMMAND, IDM_EDIT_CHARACTER);

	this->Notify();

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

LRESULT NotepadForm::OnImeStartComposition(WPARAM wParam, LPARAM lParam) {
	CString title;

	this->letter[0] = '\0';
	this->letter[1] = '\0';

	this->SendMessage(WM_COMMAND, IDM_EDIT_IMECHARACTER);

	//1. 글자가 작성되면 타이틀 앞에 *을 붙여준다.(2020.01.07 추가)
	this->GetWindowText(title);
	if (title.GetAt(0) != '*') {
		title = "*" + title;
	}
	this->SetWindowTextA(title);

	return 0;
}

LRESULT NotepadForm::OnImeComposition(WPARAM wParam, LPARAM lParam) {
	// 1. 글자를 만든다.
	GlyphFactory glyphFactory;
	Glyph *letter;
	TCHAR text[3];

	Long current;

	bool onIsAllWrapping = false;

	if (this->onIsLineWrapping == TRUE) {
		current = this->note->GetCurrent();
		this->note->Combine(current);
		current = this->note->GetCurrent();
		this->current = this->note->GetAt(current);
	}

	text[0] = HIBYTE(LOWORD(wParam));
	text[1] = LOBYTE(LOWORD(wParam));
	text[2] = 0x00;

	// 2. 조립 중이면 현재 줄에서 지운다.
	if (this->onIsComposing == TRUE) {
		this->current->Remove(this->current->GetCurrent() - 1);
	}
	// 3. 메모지의 줄에서 추가한다.
	if (text[0] != '\0') {
		letter = glyphFactory.Create(text);
		// 3.1. 현재줄의 current와 current의 length가 같으면 현재 줄에서 추가한다.(2021.01.10 추가)
		if (this->current->GetCurrent() == this->current->GetLength()) {
			this->current->Add(letter);
		}
		else {
			//3.2. 다르면 글자를 current번째에 끼워준다.
			this->current->Add(this->current->GetCurrent(), letter);
		}		
	
		this->onIsComposing = TRUE;
	}
	else {
		this->onIsComposing = FALSE;
	}

	if (this->onIsLineWrapping == TRUE) {
		this->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}

	this->Notify();

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	return ::DefWindowProc(this->m_hWnd, WM_IME_COMPOSITION, wParam, lParam);
}

LRESULT NotepadForm::OnImeChar(WPARAM wParam, LPARAM lParam) {
	// 1. 글자를 읽는다.
	this->letter[0] = HIBYTE(LOWORD(wParam));
	this->letter[1] = LOBYTE(LOWORD(wParam));

	this->SendMessage(WM_COMMAND, IDM_EDIT_IMECHARACTER);

	// 2. 갱신한다.
	this->Notify();

	// 3. 완성된 글자를 보여준다.
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	return 0;
}

LRESULT NotepadForm::OnFindReplace(WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(wParam);

	//CFindReplaceDialog *pDlg = CFindReplaceDialog::GetNotifier(lParam);
	this->pFindReplaceDialog = CFindReplaceDialog::GetNotifier(lParam);
	CString csFindString;
	CString csReplaceString;

	BOOL onIsDown;

	if (this->pFindReplaceDialog != NULL) {
		// Use pDlg as a pointer to the existing FindReplace dlg to
		// call CFindReplaceDialog member functions
		csFindString = this->pFindReplaceDialog->GetFindString();
		csReplaceString = this->pFindReplaceDialog->GetReplaceString();

		AfxGetApp()->WriteProfileString("NotepadSection", "FindString", csFindString);
		AfxGetApp()->WriteProfileString("NotepadSection", "ReplaceString", csReplaceString);
		if (this->pFindReplaceDialog->IsTerminating() == 0) {
			if (this->pFindReplaceDialog->ReplaceCurrent() == 0 && this->pFindReplaceDialog->ReplaceAll() == 0) {
				onIsDown = this->pFindReplaceDialog->SearchDown();
				if (onIsDown != 0) {
					this->SendMessage(WM_COMMAND, IDM_EDIT_FINDNEXT);
				}
				else {
					this->SendMessage(WM_COMMAND, IDM_EDIT_FINDPREV);
				}
			}
			else {
				this->SendMessage(WM_COMMAND, IDM_EDIT_REPLACE);
			}
			this->pFindReplaceDialog->ShowWindow(SW_HIDE);
			this->pFindReplaceDialog->ShowWindow(SW_SHOW);
		}
		else {
			this->pFindReplaceDialog = NULL;
			this->onIsFound = TRUE;
		}
	}
	else {
		this->onIsFound = TRUE;
	}

	this->Notify();

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	CString findMessage;
	if (this->onIsFound != TRUE) {
		findMessage.Format("\"%s\"을(를) 찾을 수 없습니다.", (LPCTSTR)csFindString);
		this->MessageBox((LPCTSTR)findMessage, "메모장", MB_OK);
		::SetFocus(this->pFindReplaceDialog->GetSafeHwnd());
	}

	return 0;
}

void NotepadForm::OnPaint() {
	CPaintDC dc(this);
	CString text;
	Glyph *line;
	
	RECT rect;
	this->GetClientRect(&rect);

	if (this->onIsStatusBar == TRUE) {
		rect.bottom -= GetSystemMetrics(SM_CYHSCROLL);
	}
	if (this->onIsVerticalScrollBar == TRUE) {
		rect.right -= GetSystemMetrics(SM_CXVSCROLL);
	}
	if (this->onIsHorizontalScrollBar == TRUE) {
		rect.bottom -= GetSystemMetrics(SM_CYHSCROLL);
	}

	CDC dcTemp;
	dcTemp.CreateCompatibleDC(&dc);

	HBITMAP hbmp = ::CreateCompatibleBitmap(dc, rect.right, rect.bottom);
	HBITMAP oldBMP = (HBITMAP)dcTemp.SelectObject(hbmp);

	dcTemp.FillRect(&rect, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));

	HFONT hFont;
	HFONT oldFont;
	hFont = CreateFontIndirect(&this->font->GetLogFont());
	oldFont = (HFONT)dcTemp.SelectObject(hFont);
	dcTemp.SetTextColor(this->font->GetColorRef());

	Long height = this->matrix->GetHeight();
	Long i = 0;
	while (i < this->note->GetLength()) {
		line = this->note->GetAt(i);
		text = CString(line->GetString().c_str());
		dcTemp.TextOut(-this->scrollController->GetHorizontalScroll()->GetCurrent(),
			(i * height) - this->scrollController->GetVerticalScroll()->GetCurrent(), text);
		i++;
	}

	DragBox dragBox(this);
	dragBox.DragingOut(&dcTemp);

	dc.BitBlt(0, 0, rect.right, rect.bottom, &dcTemp, 0, 0, SRCCOPY);

	SelectObject(dcTemp, oldFont);
	DeleteObject(hFont);

	dcTemp.SelectObject(oldBMP);
	::DeleteObject(hbmp);
	dcTemp.DeleteDC();
}

void NotepadForm::OnClose() {
	LONG ret = IDNO;
	LONG index;
	CHAR szFilters[] = _T("텍스트문서 (*.txt)|*.txt|All Files (*.*)|*.*||");
	CString asterisk;
	CString windowTitle;
	CString filePath;
	CString saveMessage;

	//1.1.타이틀 바의 제목을 읽는다.
	this->GetWindowText(windowTitle);
	//1.2 달라진게 있으면(*표가 있으면) 또는 제목없음이면
	if (windowTitle.GetAt(0) == '*' || windowTitle.Compare("제목 없음 - 메모장") == 0) {
		// 추가 " - 메모장"이 있으면 없앤다. (2021.01.08)
		if (windowTitle.GetAt(0) == '*') {
			asterisk = windowTitle.GetAt(0);
			windowTitle = windowTitle.Mid(1);
		}
		index = windowTitle.Find(" - 메모장");
		if (index >= 0) {
			windowTitle = windowTitle.Left(index);
		}

		//1.2.1.저장여부를 묻는 메세지박스를 띄운다.		
		filePath = this->file->GetPath().c_str();
		if (filePath != "") {
			windowTitle = (filePath + "\\") + windowTitle;
		}

		saveMessage.Format("변경 내용을 %s에 저장하시겠습니까?", (LPCTSTR)windowTitle);
		if (asterisk == '*') {
			ret = SaveMessageBox(this->GetSafeHwnd(), (LPCTSTR)saveMessage, _T("메모장"),
				MB_YESNOCANCEL);
		}

		//1.2.1.1.예를 눌렀으면 저장하는 메세지를 보낸다.
		this->onIsSaveCanceled = FALSE;
		if (ret == IDYES) {//Yes
			this->SendMessage(WM_COMMAND, IDM_FILE_SAVE);
		}
	}

	if (ret != IDCANCEL && this->onIsSaveCanceled != TRUE) { // 취소가 아니면 윈도우를 종료한다.
		// 레지스트리에 정보들을 저장한다. (2021.02.01)
		AfxGetApp()->WriteProfileString("NotepadSection", "FaceName", this->font->GetLogFont().lfFaceName);
		AfxGetApp()->WriteProfileInt("NotepadSection", "LogFontHeight", this->font->GetLogFont().lfHeight);
		AfxGetApp()->WriteProfileInt("NotepadSection", "LogFontWidth", this->font->GetLogFont().lfWidth);
		AfxGetApp()->WriteProfileInt("NotepadSection", "OnIsWrap", !this->onIsLineWrapping);
		AfxGetApp()->WriteProfileInt("NotepadSection", "OnIsStatusBar", !this->onIsStatusBar);
		if (this->m_hIcon != NULL) {
			DestroyIcon(this->m_hIcon);
		}
		if (this->m_hAccelTable != NULL) {
			DestroyAcceleratorTable(this->m_hAccelTable);
		}
		if (this->m_hMenu != NULL) {
			DestroyMenu(this->m_hMenu);
		}
		if (this->contextMenu != NULL) {
			delete this->contextMenu;
		}
		if (this->verticalScrollBar != NULL) {
			delete this->verticalScrollBar;
		}
		if (this->horizontalScrollBar != NULL) {
			delete this->horizontalScrollBar;
		}
		if (this->sizeBox != NULL) {
			delete this->sizeBox;
		}
		if (this->statusBar != NULL) {
			delete this->statusBar;
		}
		if (this->note != NULL) {
			delete this->note;
		}
		if (this->file != NULL) {
			delete this->file;
		}
		if (this->font != NULL) {
			delete this->font;
		}
		if (this->matrix != NULL) {
			delete this->matrix;
		}
		if (this->commandHistory != NULL) {
			delete this->commandHistory;
		}
		if (this->clipboard != NULL) {
			delete this->clipboard;
		}
		if (this->pageInfo != NULL) {
			delete this->pageInfo;
		}
		/*if (this->printer != NULL) {
			delete this->printer;
		}*/
		
		CFrameWnd::OnClose();
	}
}

LRESULT CALLBACK SaveMessageBoxProc(int nCode, WPARAM wParam, LPARAM lParam) {
	HWND hChildWnd;

	CString msg;

	if (nCode == HCBT_ACTIVATE) {
		hChildWnd = (HWND)wParam;
		if (GetDlgItem(hChildWnd, IDYES) != NULL) {
			msg = "저장(&S)";
			SetWindowText(GetDlgItem(hChildWnd, IDYES), msg);
		}

		if (GetDlgItem(hChildWnd, IDNO) != NULL) {
			msg = "저장 안 함(&N)";
			SetWindowText(GetDlgItem(hChildWnd, IDNO), msg);
		}
		UnhookWindowsHookEx(hSaveMessageBoxHook);
	}

	return 0;
}

int SaveMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT nType) {
	hSaveMessageBoxHook = SetWindowsHookEx(WH_CBT, &SaveMessageBoxProc, 0, GetCurrentThreadId());

	return MessageBox(hWnd, lpText, lpCaption, nType);
}