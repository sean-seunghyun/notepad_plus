//OpenCommand.cpp
#include"OpenCommand.h"
#include"NotepadForm.h"
#include"Glyph.h"
#include"File.h"
#include"CommandHistory.h"
#include"GlyphFactory.h"
#include<afxdlgs.h>
#include"resource.h"

OpenCommand::OpenCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

OpenCommand::~OpenCommand() {
	
}

void OpenCommand::Execute() {
	CString fileName;
	CString pathName;
	CString asterisk;
	GlyphFactory glyphFactory;
	Glyph *line;
	
	LONG index;
	LONG ret = IDNO;
	CString saveMessage;
	string filePath;

	string noteStr;

	CHAR szFilters[] = _T("텍스트문서 (*.txt)|*.txt|All Files (*.*)|*.*||");
	CString windowTitle;
	CFileDialog fileDlgLoad(TRUE, _T("txt"), NULL, NULL, szFilters);
	/*
	1. 열기 메뉴를 눌렀을 때(2021.01.07)
		1.1.타이틀 바의 제목을 읽는다.
		1.2.달라진게 있으면(*표가 있으면) 또는 제목없음이면
		1.2.1.저장여부를 묻는 메세지박스를 띄운다.
		1.2.1.1.예를 눌렀으면 저장하는 메세지를 보낸다.
		1.2.1.2.취소가 아닌 예 혹은 아니오를 눌렀으면
		1.2.1.2.1.파일 열기 다이얼로그를 띄운다.
		1.2.1.2.2.확인을 눌렀으면
		1.2.1.2.2.1.열기 파일이름, 파일 경로를 읽는다.
		1.2.1.2.2.2.기존 파일을 없앤다.
		1.2.1.2.2.3.파일을 새로 만든다.
		1.2.1.2.2.4.타이틀의 제목을 설정한다.
		1.2.1.2.2.5.파일에서 불러오기를 한다.	
		*/
	
	//1.1.타이틀 바의 제목을 읽는다.
	this->notepadForm->GetWindowText(windowTitle);
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

		//1.2.1.저장여부를 묻는 메세지박스를 띄운다. + 수정 저장 메시지 박스를 띄운다. (2021.01.08)
		filePath = this->notepadForm->file->GetPath();
		if (filePath != "") {
			windowTitle = (filePath + "\\").c_str() + windowTitle;
		}
		saveMessage.Format("변경 내용을 %s에 저장하시겠습니까?", (LPCTSTR)windowTitle);
		if (asterisk == '*') {
			ret = SaveMessageBox(this->notepadForm->GetSafeHwnd(), (LPCTSTR)saveMessage, _T("메모장"),
				MB_YESNOCANCEL);
		}

		//1.2.1.1.예를 눌렀으면 저장하는 메세지를 보낸다.
		this->notepadForm->onIsSaving = TRUE;
		this->notepadForm->onIsSaveCanceled = FALSE;
		if (ret == IDYES) {//Yes
			this->notepadForm->SendMessage(WM_COMMAND, IDM_FILE_SAVE);
		}
	}
	//1.2.1.2.취소가 아닌 예 혹은 아니오를 눌렀으면
	if (ret != IDCANCEL && this->notepadForm->onIsSaveCanceled != TRUE) {

		//1.2.1.2.1. 확인을 눌렀으면
		if (fileDlgLoad.DoModal() == IDOK) {
			//1.2.1.2.2.1.열기 파일이름, 파일 경로를 읽는다.
			fileName = fileDlgLoad.GetFileName();
			pathName = fileDlgLoad.GetFolderPath();
			this->notepadForm->onIsSaving = TRUE; // (2021.02.22)

			//1.2.1.2.2.2.기존 파일을 없앤다.
			if (this->notepadForm->file != NULL) {
				delete this->notepadForm->file;
			}
			//1.2.2.1.2.3.파일을 새로 만든다.
			this->notepadForm->file = new File(this->notepadForm, (LPCTSTR)fileName, (LPCTSTR)pathName);
			//1.2.1.2.2.4.타이틀의 제목을 설정한다.
			this->notepadForm->SetWindowTextA(fileName);
			//1.2.1.2.2.5. 노트에 있던 내용들을 모두 지운다.
			if (this->notepadForm->note != NULL) {
				delete this->notepadForm->note;
			}
			this->notepadForm->note = glyphFactory.Create((char*)0);
			line = glyphFactory.Create((char*)"\r");
			index = this->notepadForm->note->Add(line);
			this->notepadForm->note->First();
			this->notepadForm->current = this->notepadForm->note->GetAt(index);

			//1.2.1.2.2.6.파일에서 불러오기를 한다.
			this->notepadForm->file->Load();
			index = this->notepadForm->note->First();
			this->notepadForm->current = this->notepadForm->note->GetAt(index);
			this->notepadForm->current->First();
			if (this->notepadForm->onIsLineWrapping == TRUE) {
				this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
			}
			if (this->notepadForm->commandHistory != NULL) {
				delete this->notepadForm->commandHistory;
			}
			this->notepadForm->commandHistory = new CommandHistory(this->notepadForm);
		}
	}
}