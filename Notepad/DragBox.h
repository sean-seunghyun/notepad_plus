// DragBox.h
#ifndef _DRAGBOX_H
#define _DRAGBOX_H

class NotepadForm;
class CDC;
class DragBox {
public:
	NotepadForm *notepadForm;

public:
	DragBox(NotepadForm *notepadForm = 0);
	~DragBox();
	void DragingOut(CDC *dc);
};

#endif // _DRAGBOX_H