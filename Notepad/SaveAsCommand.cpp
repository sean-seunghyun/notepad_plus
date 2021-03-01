//SaveAsCommand.cpp
#include"SaveAsCommand.h"
#include"File.h"
#include"NotepadForm.h"
#include"Glyph.h"

#include<afxdlgs.h>
#include<string>
using namespace std;

SaveAsCommand::SaveAsCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

SaveAsCommand::~SaveAsCommand() {

}

void SaveAsCommand::Execute() {

	CString windowText;
	CString pathName;
	CString fileName;
	string str;
	bool onIsSaving = false;
	string title="*";

	TCHAR szFilters[] = _T("텍스트문서 (*.txt)|*.txt|All Files (*.*)|*.*||");
	/*
	1. 다름이름으로 저장하기 메뉴를 눌렀을 때
	1.1. 파일 저장 다이얼로그를 띄운다.
	1.2 확인을 눌렀으면
		1.2.1 저장할 파일 이름, 경로를 읽는다.
		1.2.2. 기존 파일을 없앤다.
		1.2.3. 파일을 새로 만든다.
		1.2.4. 노트에서 문자열을 가져온다.
		1.2.5. 파일에서 저장한다.
		1.2.6. 타이틀바의 제목을 바꾼다.
		*/




		
		//1.1. 파일 저장 다이얼로그를 띄운다.	
		this->notepadForm->GetWindowTextA(windowText);	
		if (this->notepadForm->onIsSaving == TRUE) {
			title=this->notepadForm->file->GetTitle();
		}		
		CFileDialog fileDlg(FALSE, _T("txt"), title.c_str(), NULL, szFilters);
	
		
		//1.2 확인을 눌렀으면
		if (fileDlg.DoModal() == IDOK) {		
			//1.2.1 저장할 파일 이름, 경로를 읽는다.
			fileName = fileDlg.GetFileName();
			pathName = fileDlg.GetFolderPath();
			//1.2.2. 기존 파일을 없앤다.					
			if (this->notepadForm->file != NULL) {
				delete this->notepadForm->file;
			}
			//1.2.3. 파일을 새로 만든다.
			this->notepadForm->file = new File(this->notepadForm, (LPCTSTR)fileName, (LPCTSTR)pathName);
			

			//1.2.4. 노트에서 문자열을 가져온다.
			str = this->notepadForm->note->GetString();
			//1.2.5.파일에서 저장한다.
			this->notepadForm->file->Save(str);
			this->notepadForm->onIsSaving = true;
			//1.2.5.타이틀바의 제목을 바꾼다.
			this->notepadForm->SetWindowText(fileName);
		}
	}