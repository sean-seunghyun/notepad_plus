// NotepadForm.h
#ifndef _NOTEPADFORM_H
#define _NOTEPADFORM_H
#include <afxwin.h>
#include "Subject.h"

class Glyph;
class File;
class Matrix;
class Font;
class CommandHistory;
class Clipboard;
class Printer;
class PageInfo;
class CaretController;
class ScrollController;
class CStatusBar;
class CFindReplaceDialog;
class NotepadForm : public CFrameWnd, public Subject {
public:
	HICON m_hIcon;
	CMenu *contextMenu;
	CScrollBar *verticalScrollBar;
	CScrollBar *horizontalScrollBar;
	CScrollBar *sizeBox;
	CStatusBar *statusBar;
	CFindReplaceDialog *pFindReplaceDialog;
	

	Glyph *note;
	Glyph *current;
	File *file;
	Font *font;
	Matrix *matrix;
	CPoint prevPoint;
	CommandHistory *commandHistory;
	Clipboard *clipboard;
	Printer *printer;
	PageInfo *pageInfo;
	CaretController *caretController;
	ScrollController *scrollController;
	BOOL onIsVerticalScrollBar;
	BOOL onIsHorizontalScrollBar;
	BOOL onIsStatusBar;

	BOOL onIsComposing;
	BOOL onIsSaving;
	BOOL onIsMoving;
	BOOL onIsScrolling;
	BOOL onIsLineWrapping;
	BOOL onIsSaveCanceled;
	BOOL onIsFound;
	BOOL onIsOpeningFindReplace;
	BOOL onIsIBeam;
	BOOL onIsDraging;
	BOOL onIsDoubleClicked;

public:
	NotepadForm();
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	TCHAR* GetLetter() const;

protected:
	afx_msg virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd *pCWnd, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd *pCWnd);
	afx_msg void OnKillFocus(CWnd *pCWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint point);
	afx_msg void OnRangeCmds(UINT nId);
	afx_msg void OnUpdatePoint(CCmdUI *pCmdUI);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnImeStartComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeChar(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFindReplace(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg virtual void OnClose();
	DECLARE_MESSAGE_MAP()

private:
	TCHAR letter[2];
};

inline TCHAR* NotepadForm::GetLetter() const {
	return const_cast<TCHAR*>(this->letter);
}

LRESULT CALLBACK SaveMessageBoxProc(int nCode, WPARAM wParam, LPARAM lParam);
int SaveMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT nType);

#endif // _NOTEPADFORM_H