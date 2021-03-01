// PasteCommand.h
#ifndef _PASTECOMMAND_H
#define _PASTECOMMAND_H
#include "EditCommand.h"

class PasteCommand : public EditCommand {
public:
	PasteCommand(NotepadForm *notepadForm = 0);
	virtual ~PasteCommand();
	virtual void Execute();
	virtual void UnExecute();
	virtual void ReExecute();

private:
	State *state;
};

#endif // _PASTECOMMAND_H