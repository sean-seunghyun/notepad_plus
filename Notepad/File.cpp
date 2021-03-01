//File.cpp
#include"File.h"
#include"Glyph.h"
#include"NotepadForm.h"
#include<stdio.h>
#include"GlyphFactory.h"
#include "Line.h"


File::File(NotepadForm *notepadForm)
	:title("제목 없음 - 메모장"), path("") {
	this->notepadForm = notepadForm;
}

File::File(NotepadForm *notepadForm, string title, string path)
	: title(title), path(path) {
	this->notepadForm = notepadForm;
}

File::~File() {

}

void File::Load() {
	string noteString;
	FILE *file;

	char(*text);

	Long size;

	file = fopen((char*)(this->path + "\\" + this->title).c_str(), "rt");
	if (file != 0) {
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		if (size > 0) {
			text = (char(*))calloc(size + 1, sizeof(char));
			fseek(file, 0, SEEK_SET);
			fread((char*)text, sizeof(char), size, file);
			noteString = text;
			if (text != 0) {
				delete text;
			}
		}
		fclose(file);
	}

	this->notepadForm->note->Paste(noteString);
}

void File::Save(string noteString) {
	FILE *file;
	file = fopen((char*)(this->path + "\\" + this->title).c_str(), "wt");
	if (file != 0) {
		fwrite((char*)noteString.c_str(), strlen(noteString.c_str()), 1, file);

		fclose(file);
	}
}

#if 0
string File::Load() {
	Long i = 0;
	char letter[2];
	Glyph *glyph;
	GlyphFactory glyphFactory;
	Long index;

	while (string[i] != '\0') {

		if (string[i] == '\n') {
			letter[0] = string[i];
			letter[1] = ' ';
		}

		else if ((string[i] & 0x80) != 0) {
			letter[0] = string[i];
			i++;
			letter[1] = string[i];
		}
		else if ((string[i] & 0x80) == 0) {
			letter[0] = string[i];
			letter[1] = ' ';
		}
		glyph = glyphFactory.Create(letter);
		if (dynamic_cast<Line*>(glyph)) {
			Long index = this->notepadForm->note->Add(glyph);
			this->notepadForm->current = this->notepadForm->note->GetAt(index);
		}
		else {
			this->notepadForm->current->Add(glyph);
		}

		i++;
	}

#if 0
	//캐럿의 위치 조정
	index = this->notepadForm->note->First();
	this->notepadForm->current = this->notepadForm->note->GetAt(index - 1);
	this->notepadForm->current->First();
#endif
}
#endif
