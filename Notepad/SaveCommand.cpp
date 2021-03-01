//SaveCommand.cpp
#include"SaveCommand.h"
#include"File.h"
#include"NotepadForm.h"
#include"Glyph.h"

#include<afxdlgs.h>
#include<string>
using namespace std;

SaveCommand::SaveCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

SaveCommand::~SaveCommand() {

}

void SaveCommand::Execute() {// ret 초기화
	CFileStatus status;

	CString windowText;
	CString pathName;
	CString fileName;
	string str;
	bool onIsSaving = false;
	INT_PTR ret = IDCANCEL;
	
	TCHAR szFilters[] = _T("텍스트문서 (*.txt)|*.txt|All Files (*.*)|*.*||");
	/*2021.01.17
	1. 저장하기 메뉴를 눌렀을 때
		1.1 타이틀 바의 제목을 읽는다.
		1.2 달라진게 있으면(*표가 있으면) 또는 제목없음이면
			1.2.1.현재 저장이 되어있는 상태가 아니면
				1.2.1.1.파일 저장 다이얼로그를 띄운다.
				1.2.1.2.확인을 눌렀으면
					1.2.2.1.2.1 저장할 파일 이름, 경로를 읽는다.
					1.2.2.1.2.2.기존 파일을 없앤다.
					1.2.2.1.2.3.파일을 새로 만든다.
			1.2.2.현재 저장이 되어있는 상태이면
				1.2.2.1.파일에서 파일이름과 경로를 읽는다.
			1.2.3.노트에서 문자열을 가져온다.
			1.2.4.파일에서 저장한다.
			1.2.5.타이틀바의 제목을 바꾼다.
		*/

		//1.1 타이틀 바의 제목을 읽는다.
	this->notepadForm->GetWindowText(windowText);

	//1.2 달라진게 있으면(*표가 있으면) 또는 제목없음이면
	if (windowText.GetAt(0) == '*' || windowText.Compare("제목 없음 - 메모장") == 0) {
		//1.2.1.현재 저장이 되어있는 상태가 아니면
		if (this->notepadForm->onIsSaving != TRUE) {
			//1.2.1.1.파일 저장 다이얼로그를 띄운다.
			CFileDialog fileDlg(FALSE, _T("txt"), _T("*.txt"), NULL, szFilters);
			ret = fileDlg.DoModal();

			this->notepadForm->onIsSaveCanceled = TRUE;
			if (ret == IDOK) {
				fileName = fileDlg.GetFileName();
				pathName = fileDlg.GetFolderPath();
				//1.2.2.1.2.2.기존 파일을 없앤다.					
				if (this->notepadForm->file != NULL) {
					delete this->notepadForm->file;
				}
				//1.2.2.1.2.3.파일을 새로 만든다.
				this->notepadForm->file = new File(this->notepadForm, (LPCTSTR)fileName, (LPCTSTR)pathName);
				this->notepadForm->onIsSaving = TRUE;
				this->notepadForm->onIsSaveCanceled = FALSE;
			}
		}
		//1.2.2.현재 저장이 되어있는 상태이면
		else {
			//1.2.2.1.파일에서 파일이름과 경로를 읽는다.
			ret = IDYES;
			fileName = CString(this->notepadForm->file->GetTitle().c_str());
			pathName = CString(this->notepadForm->file->GetPath().c_str());
		}

		if (ret != IDCANCEL) {//취소를 안눌렀으면
			//1.2.3.노트에서 문자열을 가져온다.	
			str = this->notepadForm->note->GetString();
			//1.2.4.파일에서 저장한다.
			this->notepadForm->file->Save(str);
			
			//1.2.5.타이틀바의 제목을 바꾼다.
			this->notepadForm->SetWindowText(fileName);
		}
	}
}