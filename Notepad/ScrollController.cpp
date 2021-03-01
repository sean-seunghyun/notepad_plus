//ScrollController.cpp
#include"ScrollController.h"
#include"VerticalScroll.h"
#include"HorizontalScroll.h"
#include"Scroll.h"
#include"NotepadForm.h"
#include"Matrix.h"
#include"Glyph.h"
#include<afxext.h>


ScrollController::ScrollController(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	
	Long horizontalMax;
	Long verticalMax;
	Long horizontalPage;
	Long verticalPage;
	Long horizontalUnit;
	Long verticalUnit;
	RECT rect = { 0, };
	this->notepadForm->GetClientRect(&rect);

	horizontalMax = this->notepadForm->matrix->GetMaxX();
	verticalMax = this->notepadForm->matrix->GetMaxY();
	horizontalPage = rect.right;
	verticalPage = rect.bottom;
	horizontalUnit = this->notepadForm->matrix->GetWidth(128) / 2;
	verticalUnit = this->notepadForm->matrix->GetHeight();

	this->horizontalScroll = new HorizontalScroll(0,horizontalMax,horizontalUnit,horizontalPage,0);
	this->verticalScroll = new VerticalScroll(0, verticalMax, verticalUnit, verticalPage, 0);

	dynamic_cast<Subject*>(this->notepadForm)->Attach(this);
}

ScrollController::~ScrollController() {
	if (this->horizontalScroll != 0) {
		delete this->horizontalScroll;
	}
	if (this->verticalScroll != 0) {
		delete this->verticalScroll;
	}
}

void ScrollController::Update() {
	
	Long box;
	RECT rect = { 0, };
	Long verticalMax;
	Long horizontalMax;
	Long verticalPage;
	Long horizontalPage;
	Long verticalUnit;
	Long horizontalUnit;
	Long verticalCurrent;
	Long horizontalCurrent;

	Long horizontalScrollBarX;
	Long horizontalScrollBarY;
	Long horizontalScrollBarWidth;
	Long horizontalScrollBarHeight;

	Long verticalScrollBarX;
	Long verticalScrollBarY;
	Long verticalScrollBarWidth;
	Long verticalScrollBarHeight;

	Long statusBarHeight = 0;

	

	SCROLLINFO horizontalScrollInfo;
	SCROLLINFO verticalScrollInfo;

	

	this->notepadForm->onIsHorizontalScrollBar = FALSE;
	this->notepadForm->onIsVerticalScrollBar = FALSE;

	//1. 스크롤바 박스의 길이를 구한다.
	box = GetSystemMetrics(SM_CYHSCROLL);



	//2. 윈도우 화면 크기를 구한다.
	this->notepadForm->GetClientRect(&rect);
	//CClientDC dc(this->notepadForm);

	//3. 스크롤의 가로, 세로 최대 길이를 구한다.
	horizontalMax = this->notepadForm->matrix->GetMaxX();
	verticalMax = this->notepadForm->matrix->GetMaxY();
	// 높이는 캐럿의 위 기준이 아니라 아래의 기준으로 스크롤바가 생기므로 높이를 한 번 더함(2021.01.13)

	//4. 페이지의 가로, 세로 길이를 구한다.
	horizontalPage = rect.right;
	verticalPage = rect.bottom;

	//5. 가로, 세로 current 값을 읽는다.
	horizontalCurrent = this->horizontalScroll->GetCurrent();
	verticalCurrent = this->verticalScroll->GetCurrent();

	// + 상태바가 있으면 수직 페이지 크기를 줄인다.
	if (this->notepadForm->onIsStatusBar == TRUE) {
		verticalPage -= box;
		statusBarHeight = box;
	}

	//6. 수평스크롤바가 생기면(가로스크롤의 최대 길이가 페이지의 가로길이보다 크면)
	if (horizontalMax > horizontalPage) {
		//6.1 수평스크롤바의 플래그를 설정한다.
		this->notepadForm->onIsHorizontalScrollBar = TRUE;
		//6.1. 페이지의 세로길이에서 박스의 길이를 뺀다.
		verticalPage -= box;
	}
	//7. 수직스크롤바가 생기면(세로스크롤의 최대 길이가 페이지의 세로길이보다 크면)
	if (verticalMax > verticalPage) {
		//7.1 수평스크롤바의 플래그를 설정한다.
		this->notepadForm->onIsVerticalScrollBar = TRUE;
		//7.2. 페이지의 가로길이에서 박스의 길이를 뺀다.
		horizontalPage -= box;
	}
	// 8. 수평 스크롤바가 생기면(한번 더 확인) (2021.01.13)
	if (horizontalMax > horizontalPage && this->notepadForm->onIsHorizontalScrollBar != TRUE) {
		//6.1 수평스크롤바의 플래그를 설정한다.
		this->notepadForm->onIsHorizontalScrollBar = TRUE;
		//6.1. 페이지의 세로길이에서 박스의 길이를 뺀다.
		verticalPage -= box;
	}

	//8. 수평스크롤바가 안생겼으면 수평스크롤의 현재 위치를 0으로 설정한다.
	if (this->notepadForm->onIsHorizontalScrollBar != TRUE) {
		horizontalCurrent = 0;
	}
	
	// + 자동개행모드이면 수평 스크롤바 0으로 설정.
	if (this->notepadForm->onIsLineWrapping == TRUE) {
		horizontalCurrent = 0;
	}

	//9. 수직스크롤바가 안생겼으면 수직스크롤의 현재위치를 0으로 설정한다.
	if (this->notepadForm->onIsVerticalScrollBar != TRUE) {
		verticalCurrent = 0;
	}

	//10. 수평, 수직 스크롤의 유닛을 구한다.
	horizontalUnit = this->notepadForm->matrix->GetWidth(128) / 2;
	verticalUnit = this->notepadForm->matrix->GetHeight();

	//11. 수평스크롤바가 있으면 스크롤바의 위치를 정해준다.
	if (this->notepadForm->onIsHorizontalScrollBar == TRUE) {
		horizontalScrollBarX = 0;
		horizontalScrollBarY = rect.bottom - statusBarHeight - box;
		horizontalScrollBarWidth = horizontalPage;
		horizontalScrollBarHeight = box;
	}

	//12. 수직스크롤바가 있으면 스크롤바의 위치를 정해준다.
	if (this->notepadForm->onIsVerticalScrollBar == TRUE) {
		verticalScrollBarX = rect.right - box;
		verticalScrollBarY = 0;
		verticalScrollBarWidth = box;
		verticalScrollBarHeight = verticalPage;
	}

	//14. 기존의 스크롤들을 지운다.
	if (this->horizontalScroll != 0) {
		delete this->horizontalScroll;
	}

	if (this->verticalScroll != 0) {
		delete this->verticalScroll;
	}

	// + 스크롤의 현재 위치 값을 보정한다.(2021.02.03)
	if (horizontalCurrent >= horizontalMax - horizontalPage && horizontalMax > horizontalPage) {
		horizontalCurrent = horizontalMax - horizontalPage + 2;
	}

	if (verticalCurrent >= verticalMax - verticalPage && verticalMax > verticalPage) {
		verticalCurrent = verticalMax - verticalPage + 2;
	}

	//15. 스크롤의 값들을 새로 저장한다.
	this->horizontalScroll = new HorizontalScroll(0,horizontalMax,horizontalUnit,horizontalPage,horizontalCurrent);
	this->verticalScroll = new VerticalScroll(0,verticalMax,verticalUnit,verticalPage,verticalCurrent);

	//16. 스크롤에 정보를 저장한다
	horizontalScrollInfo.cbSize = sizeof(SCROLLINFO);
	horizontalScrollInfo.fMask = SIF_ALL;
	horizontalScrollInfo.nMin = this->horizontalScroll->GetMin();
	horizontalScrollInfo.nMax = this->horizontalScroll->GetMax();
	horizontalScrollInfo.nPage = this->horizontalScroll->GetPage();
	horizontalScrollInfo.nPos = this->horizontalScroll->GetCurrent();
	horizontalScrollInfo.nTrackPos = 2;

	verticalScrollInfo.cbSize = sizeof(SCROLLINFO);
	verticalScrollInfo.fMask = SIF_ALL;
	verticalScrollInfo.nMin = this->verticalScroll->GetMin();
	verticalScrollInfo.nMax = this->verticalScroll->GetMax();
	verticalScrollInfo.nPage = this->verticalScroll->GetPage();
	verticalScrollInfo.nPos = this->verticalScroll->GetCurrent();
	verticalScrollInfo.nTrackPos = 2;

	//17. 수평 스크롤바를 보여준다.
	this->notepadForm->horizontalScrollBar->SetScrollInfo(&horizontalScrollInfo, TRUE); // 어차피 설정하니 밖으로 빼냄 (2021.01.13)
	if (this->notepadForm->onIsHorizontalScrollBar == TRUE) {
		this->notepadForm->horizontalScrollBar->SetWindowPos(NULL, horizontalScrollBarX, horizontalScrollBarY, horizontalScrollBarWidth, horizontalScrollBarHeight, SWP_DRAWFRAME);
		this->notepadForm->horizontalScrollBar->ShowScrollBar(TRUE);
	}
	else {
		this->notepadForm->horizontalScrollBar->ShowScrollBar(FALSE);
	}
	//18. 수직 스크롤바를 보여준다.
	this->notepadForm->verticalScrollBar->SetScrollInfo(&verticalScrollInfo, TRUE); // 어차피 설정하니 밖으로 빼냄 (2021.01.13)
	if (this->notepadForm->onIsVerticalScrollBar == TRUE) {
		this->notepadForm->verticalScrollBar->SetWindowPos(NULL, verticalScrollBarX,verticalScrollBarY, verticalScrollBarWidth,
			verticalScrollBarHeight, SWP_DRAWFRAME);
		this->notepadForm->verticalScrollBar->ShowScrollBar(TRUE);
	}
	else {
		this->notepadForm->verticalScrollBar->ShowScrollBar(FALSE);
	}

	//19. 수평, 수직스크롤바가 동시에 있으면 사이즈 박스를 끼워넣는다.
	if (this->notepadForm->onIsHorizontalScrollBar == TRUE && this->notepadForm->onIsVerticalScrollBar == TRUE) {
		// X = VerticalScrollBar의 X, Y = HorizontalScrollBar의 Y축으로 변경(2021.01.13)
		this->notepadForm->sizeBox->SetWindowPos(NULL, verticalScrollBarX, horizontalScrollBarY, box, box, SWP_DRAWFRAME);
		this->notepadForm->sizeBox->ShowScrollBar(TRUE);
	}
	else {
		this->notepadForm->sizeBox->ShowScrollBar(FALSE);
	}
}

Observer* ScrollController::Clone() {
	return new ScrollController(*this);
}
// Scroll들을 읽는 연산 추가 (2021.01.13)
Scroll* ScrollController::GetHorizontalScroll() {
	return this->horizontalScroll;
}

Scroll* ScrollController::GetVerticalScroll() {
	return this->verticalScroll;
}



#if 0
void ScrollController::Update() {


	Long verticalMax;
	Long horizontalMax;
	Long verticalPage;
	Long horizontalPage;
	Long verticalUnit;
	Long horizontalUnit;
	Long verticalCurrent;
	Long horizontalCurrent;
	RECT rect = { 0, };
	RECT statusBarRect = { 0, };
	SCROLLINFO hScrollInfo;
	SCROLLINFO vScrollInfo;
	CRect  hScrollRect = { 0, };
	CRect  vScrollRect = { 0, };
	Long hScrollHeight;
	Long vScrollWidth;






	hScrollHeight = GetSystemMetrics(SM_CYHSCROLL);
	vScrollWidth = GetSystemMetrics(SM_CXHSCROLL);
	this->notepadForm->statusBar->GetItemRect(0, &statusBarRect);
	this->notepadForm->GetClientRect(&rect);
	CClientDC dc(this->notepadForm);

	horizontalMax = this->notepadForm->matrix->GetMaxX();
	horizontalUnit = this->notepadForm->matrix->GetWidth(128) * 5;
	horizontalPage = rect.right;


	//수직스크롤바가 있면 수평 page의 값이 줄어들어야 한다.
	verticalMax = this->notepadForm->matrix->GetMaxY();
	verticalPage = rect.bottom;

#if 0
	? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?
		if (verticalMax > verticalPage) {
			horizontalPage -= hScrollHeight;
		}
#endif


	if (this->notepadForm->onIsAutomaticCarriageReturning == TRUE) {
		horizontalCurrent = 0;
		//this->notepadForm->hScrollBar->ShowScrollBar(FALSE);
	}

	else {
		horizontalCurrent = this->horizontalScroll->GetCurrent();
		if (horizontalMax < horizontalPage) {//스크롤 없어질 경우 처음으로
			horizontalCurrent = 0;
		}
	}



	//verticalMax = this->notepadForm->matrix->GetMaxY(); 위에서 읽음

	verticalUnit = this->notepadForm->matrix->GetHeight();
	//verticalPage = rect.bottom; 위에서 읽음
	//수평스크롤바가 생기면 page의 값이 줄어들어야 한다.
	if (horizontalMax > horizontalPage) {
		verticalPage -= hScrollHeight;
	}
	verticalCurrent = this->verticalScroll->GetCurrent();
	if (verticalMax < verticalPage) {//스크롤 없어질 경우 처음으로
		verticalCurrent = 0;
	}

	if (this->horizontalScroll != 0) {
		delete this->horizontalScroll;
	}


	if (this->verticalScroll != 0) {
		delete this->verticalScroll;
	}


	//스크롤바가 생기는 만큼 page의 값이 줄어들었음.

	this->horizontalScroll = new HorizontalScroll(this, horizontalCurrent, horizontalUnit, horizontalPage - vScrollWidth, 0, horizontalMax);


	if (this->notepadForm->onIsShowingStatusBar == TRUE) {
		this->verticalScroll = new VerticalScroll(this, verticalCurrent, verticalUnit, verticalPage - hScrollHeight - statusBarRect.bottom, 0, verticalMax);
	}
	else {
		this->verticalScroll = new VerticalScroll(this, verticalCurrent, verticalUnit, verticalPage - hScrollHeight, 0, verticalMax);
	}



	hScrollInfo.cbSize = sizeof(SCROLLINFO);
	hScrollInfo.fMask = SIF_ALL;
	hScrollInfo.nMin = this->horizontalScroll->GetMin();
	hScrollInfo.nMax = this->horizontalScroll->GetMax();
	hScrollInfo.nPage = this->horizontalScroll->GetPage();
	hScrollInfo.nPos = this->horizontalScroll->GetCurrent();

	hScrollInfo.nTrackPos = 2;

	vScrollInfo.cbSize = sizeof(SCROLLINFO);
	vScrollInfo.fMask = SIF_ALL;
	vScrollInfo.nMin = this->verticalScroll->GetMin();
	vScrollInfo.nMax = this->verticalScroll->GetMax();
	vScrollInfo.nPage = this->verticalScroll->GetPage();
	vScrollInfo.nPos = this->verticalScroll->GetCurrent();
	vScrollInfo.nTrackPos = 2;

	if (this->horizontalScroll->GetMax() > this->horizontalScroll->GetPage() && this->notepadForm->onIsAutomaticCarriageReturning != TRUE) {
		this->notepadForm->hOnIsScrolling = TRUE;

		if (this->notepadForm->onIsShowingStatusBar == FALSE) {//상태표시줄이 안보이면
			if (this->notepadForm->vOnIsScrolling == TRUE) {//수평스크롤과 수직스크롤이 동시에 생기면
				this->notepadForm->hScrollBar->SetWindowPos(NULL, 0, rect.bottom - hScrollHeight, rect.right - hScrollHeight, hScrollHeight, SWP_DRAWFRAME);

			}
			else {//수평스크롤만 생기면
				this->notepadForm->hScrollBar->SetWindowPos(NULL, 0, rect.bottom - hScrollHeight, rect.right, hScrollHeight, SWP_DRAWFRAME);
			}
		}
		else {//상태표시줄이 보이면

			if (this->notepadForm->vOnIsScrolling == TRUE) {//수평스크롤과 수직스크롤이 동시에 생기면
				this->notepadForm->hScrollBar->SetWindowPos(NULL, 0, rect.bottom - hScrollHeight - statusBarRect.bottom, rect.right - hScrollHeight, hScrollHeight, SWP_DRAWFRAME);



				dc.Rectangle(rect.right - vScrollWidth, rect.bottom - hScrollHeight - statusBarRect.bottom, rect.right, rect.bottom - statusBarRect.bottom);


			}
			else {//수평스크롤만 생기면
				this->notepadForm->hScrollBar->SetWindowPos(NULL, 0, rect.bottom - hScrollHeight - statusBarRect.bottom, rect.right, hScrollHeight, SWP_DRAWFRAME);
			}


		}
		this->notepadForm->hScrollBar->ShowScrollBar(TRUE);
		this->notepadForm->hScrollBar->SetScrollInfo(&hScrollInfo, TRUE);
	}

	else {
		this->notepadForm->hOnIsScrolling = FALSE;
		this->notepadForm->hScrollBar->ShowScrollBar(FALSE);
		this->notepadForm->hScrollBar->SetScrollInfo(&hScrollInfo, TRUE);//
	}




	if (this->verticalScroll->GetMax() > this->verticalScroll->GetPage()) {
		this->notepadForm->vOnIsScrolling = TRUE;
		this->notepadForm->vScrollBar->SetWindowPos(NULL, rect.right - vScrollWidth, 0, vScrollWidth, rect.bottom, SWP_DRAWFRAME);

		if (this->notepadForm->onIsShowingStatusBar == FALSE) {//상태표시줄이 안보이면
			if (this->notepadForm->hOnIsScrolling == TRUE) {//수평, 수직 스크롤이 동시에 생기면
				this->notepadForm->vScrollBar->SetWindowPos(NULL, rect.right - vScrollWidth, 0, vScrollWidth, rect.bottom - vScrollWidth, SWP_DRAWFRAME);
			}
			else {
				this->notepadForm->vScrollBar->SetWindowPos(NULL, rect.right - vScrollWidth, 0, vScrollWidth, rect.bottom, SWP_DRAWFRAME);

			}
		}
		else {//상태표시줄이 보이면

			if (this->notepadForm->hOnIsScrolling == TRUE) {//수평, 수직 스크롤이 동시에 생기면

				this->notepadForm->vScrollBar->SetWindowPos(NULL, rect.right - vScrollWidth, 0, vScrollWidth, rect.bottom - vScrollWidth - statusBarRect.bottom, SWP_DRAWFRAME);

			}
			else {
				this->notepadForm->vScrollBar->SetWindowPos(NULL, rect.right - vScrollWidth, 0, vScrollWidth, rect.bottom, SWP_DRAWFRAME);

			}

		}
		this->notepadForm->vScrollBar->ShowScrollBar(TRUE);
		this->notepadForm->vScrollBar->SetScrollInfo(&vScrollInfo, TRUE);

	}

	else {
		this->notepadForm->vOnIsScrolling = FALSE;
		this->notepadForm->vScrollBar->ShowScrollBar(FALSE);
		this->notepadForm->vScrollBar->SetScrollInfo(&vScrollInfo, TRUE);
	}


}
#endif
