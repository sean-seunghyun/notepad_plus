// DateCommand.h
#ifndef _DATECOMMAND_H
#define _DATECOMMAND_H
#include "EditCommand.h"

class DateCommand :public EditCommand {
public:
	DateCommand(NotepadForm *notepadForm = 0);
	virtual ~DateCommand();
	virtual void Execute();
	virtual void UnExecute();
	virtual void ReExecute();
};

#endif //_DATECOMMAND_H