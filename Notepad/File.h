//File.h
#ifndef _FILE_H
#define _FILE_H
#define _CRT_SECURE_NO_WARNINGS
#include<string>
using namespace std;

class NotepadForm;
class File {
public:
	NotepadForm *notepadForm;

public:
	File(NotepadForm *notepadForm);
	File(NotepadForm *notepadForm, string title, string path);
	~File();
	void Load();
	void Save(string str);
	
	string GetTitle() const;
	string GetPath() const;

private:
	string title;
	string path;
};


inline string File::GetTitle() const {
	return this->title;
}

inline string File::GetPath() const {
	return this->path;
}


#endif // !_FILE_H
