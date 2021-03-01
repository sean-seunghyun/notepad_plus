// CopyCommand.h
#ifndef _COPYCOMMAND_H
#define _COPYCOMMAND_H
#include "EditCommand.h"

class CopyCommand : public EditCommand {
public:
	CopyCommand(NotepadForm *notepadForm = 0);
	virtual ~CopyCommand();
	virtual void Execute();
};

#endif // _COPYCOMMAND_H