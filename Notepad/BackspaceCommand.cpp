// BackspaceCommand.cpp
/*
���ϸ�Ī : BackspaceCommand.cpp
��� : ���� ���� ���� ���� Ŭ������ �����.
�ۼ��� : �����, ������
�ۼ����� : 2021.01.25
*/
#include "BackspaceCommand.h"
#include "State.h"
#include "NotepadForm.h"
#include "Glyph.h"
#include "Matrix.h"
#include "resource.h"

BackspaceCommand::BackspaceCommand(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
	this->id = EditCommand::BACKSPACECOMMAND;
	this->onIsNew = true;
	this->onIsSelected = false;
	this->onIsEnter = false;
}

BackspaceCommand::~BackspaceCommand() {
}

void BackspaceCommand::Execute() {
	LONG noteCurrent;
	LONG noteLength;
	LONG lineCurrent;
	LONG lineLength;

	string text;

	Glyph *previousLine;
	Glyph *currentLine;
	Glyph *glyph;
	// + ���õ� ���� �ִ��� Ȯ���Ѵ�.
	this->onIsSelected = this->notepadForm->note->GetOnIsSelected();

	//1. �ڵ��������̰�, ���õǾ� �ִ��� Ȯ���Ѵ�.
	noteCurrent = this->notepadForm->note->GetCurrent();
	if (this->notepadForm->onIsLineWrapping == TRUE && this->onIsSelected == true) {
		// 1.1. ���õ� �ٵ��� ��ģ��.
		this->notepadForm->note->CombineSelectedLines();
	}
	else if (this->notepadForm->onIsLineWrapping == TRUE) {
		// 1.2. ���� ���� ��ģ��.
		this->notepadForm->note->Combine(noteCurrent);
	}

	//2. �������� lineCurrent ���� ���Ѵ�.
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	lineCurrent = this->notepadForm->current->GetCurrent();

	// + ���õ� ���� ������ ���õ� �κ��� �����.
	if (this->onIsSelected == true) {
		// ���õ� ������ �д´�.
		text = this->notepadForm->note->GetSelectString();

		// ���õ� ������ �����.
		this->notepadForm->note->RemoveSelect();
	}
	//3. lineCurrent ���� 0���� �۰ų� ������
	else if (lineCurrent <= 0 && noteCurrent > 0) {
		this->onIsEnter = true;
		text = "\n";
		//3.1. �������� �����´�.
		currentLine = this->notepadForm->note->GetAt(noteCurrent);
		//3.2 �������� �����´�.
		previousLine = this->notepadForm->note->GetAt(noteCurrent - 1);
		//3.3. �����ٿ��� �������� ��ģ��.
		previousLine->Combine(currentLine);

		//3.4. ��Ʈ���� noteCurrent��° ���� ���ش�.
		this->notepadForm->note->Remove(noteCurrent);
		noteCurrent = this->notepadForm->note->Previous();
	}
	//4. lineCurrent ���� 0���� ũ��
	else if (lineCurrent > 0) {
		glyph = this->notepadForm->current->GetAt(lineCurrent - 1);
		text = glyph->GetString();
		this->notepadForm->current->Remove(lineCurrent - 1);
	}

	// ���� ��ġ�� �а� ��ġ�� �̵��Ѵ�.
	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// ���� ���¸� �����.
	if (text != "") {
		this->notepadForm->note->GetCombineCurrent(&lineCurrent, &noteCurrent);
		this->previousState = new State(lineCurrent, noteCurrent, text);
		this->onIsCommandSaving = true;
	}

	if (this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}

	CString title;
	this->notepadForm->GetWindowText(title);
	if (title.GetAt(0) != '*') {
		title = "*" + title;
	}
	noteLength = this->notepadForm->note->GetLength();
	lineLength = this->notepadForm->current->GetLength();
	if ((noteLength > 1 || (noteLength <= 1 && lineLength > 0)) || this->onIsCommandSaving == true) {
		this->notepadForm->SetWindowTextA(title);
	}
}

void BackspaceCommand::UnExecute() {
	Glyph *previousNote;

	Long lineCurrent;
	Long noteCurrent;

	if (this->previousState != 0) {
		// 2.1. ���� ���� ������ �о�´�.
		previousNote = this->previousState->GetNote();
		lineCurrent = this->previousState->GetLineCurrent();
		noteCurrent = this->previousState->GetNoteCurrent();

		this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

		if (this->notepadForm->onIsLineWrapping == TRUE) {// �ڵ��������̸� �� �� �ڵ������Ѵ�.(2021.02.09)
			noteCurrent = this->notepadForm->note->GetCurrent();
			this->notepadForm->note->Combine(noteCurrent);
		}

		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

		// 2.2. ���� ������ ������ �߰��Ѵ�.
		previousNote->SelectAll(true);
		this->notepadForm->note->Paste(previousNote);

		// 2.3. �޸������� ���� ���� ���Ѵ�.
		noteCurrent = this->notepadForm->note->GetCurrent();
		this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	}

	if (this->previousState != 0 && this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

void BackspaceCommand::ReExecute() {
	Glyph *previousNote;
	Glyph *currentLine;
	Glyph *nextLine;

	string text;

	Long lineCurrent;
	Long noteCurrent;
	Long textCount;

	// 1. ���� ���� ������ �о�´�.
	previousNote = this->previousState->GetNote();
	text = previousNote->GetString();
	lineCurrent = this->previousState->GetLineCurrent();
	noteCurrent = this->previousState->GetNoteCurrent();

	// 2. �о�� ��ġ�� �̵��Ѵ�.
	this->notepadForm->note->MoveActualCurrent(lineCurrent, noteCurrent);

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	lineCurrent = this->notepadForm->current->GetCurrent();

	// 3. ���õǾ� ������ ������ �����Ѵ�.
	if (this->onIsSelected == true) {
		textCount = this->notepadForm->matrix->GetStringCount((char*)text.c_str());
		this->notepadForm->note->SelectCount(lineCurrent, noteCurrent, textCount);
	}

	// 4. �ڵ��������̰� ���õǾ� �ִ��� Ȯ���Ѵ�.
	noteCurrent = this->notepadForm->note->GetCurrent();
	if (this->notepadForm->onIsLineWrapping == TRUE && this->onIsSelected == true) {
		// 4.1. ���õ� �ٵ��� �����ش�.
		this->notepadForm->note->CombineSelectedLines();
	}
	else if (this->notepadForm->onIsLineWrapping == TRUE) {
		// 4.2. ���� ���� ��ģ��.
		this->notepadForm->note->Combine(noteCurrent);
	}

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);
	lineCurrent = this->notepadForm->current->GetCurrent();

	// 5. ���õǾ� ������ ���õ� ������ �����.
	if (this->onIsSelected == true) {
		this->notepadForm->note->RemoveSelect();
	}
	// 6. ���๮���̸� ���� ��ģ��.
	else if (text == "\n") {
		//6.1. �������� �����´�.
		currentLine = this->notepadForm->note->GetAt(noteCurrent);

		//6.2 �������� �����´�.
		nextLine = this->notepadForm->note->GetAt(noteCurrent + 1);

		//6.3. �����ٿ��� �������� ��ģ��.
		currentLine->Combine(nextLine);

		//6.4. ��Ʈ���� noteCurrent��° ���� ���ش�.
		this->notepadForm->note->Remove(noteCurrent + 1);
		this->notepadForm->note->Previous();
	}
	// 7. ���๮�ڰ� �ƴϸ� ��ġ�� ���ڸ� �����.
	else {
		// 7.2 lineCurrent��° ���ڸ� �����.
		this->notepadForm->current->Remove(lineCurrent);
	}

	noteCurrent = this->notepadForm->note->GetCurrent();
	this->notepadForm->current = this->notepadForm->note->GetAt(noteCurrent);

	// 8. �ڵ��������̸� �ڵ������Ѵ�.
	if (this->previousState != 0 && this->notepadForm->onIsLineWrapping == TRUE) {
		this->notepadForm->SendMessage(WM_COMMAND, IDM_FORMAT_WRAP);
	}
}

Long BackspaceCommand::GetLineCurrent() {
	Long ret = -1;
	if (this->previousState != 0) {
		ret = this->previousState->GetLineCurrent();
	}

	return ret;
}

Long BackspaceCommand::GetNoteCurrent() {
	Long ret = -1;
	if (this->previousState != 0) {
		ret = this->previousState->GetNoteCurrent();
	}

	return ret;
}

void BackspaceCommand::SetOnIsNew(bool onIsNew) {
	this->onIsNew = onIsNew;
}