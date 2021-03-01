// ReplaceDialogCommand.h
#ifndef _REPLACEDIALOGCOMMAND_H
#define _REPLACEDIALOGCOMMAND_H
#include "Command.h"

class ReplaceDialogCommand : public Command {
public:
	ReplaceDialogCommand(NotepadForm *notepadForm = 0);
	virtual ~ReplaceDialogCommand();
	virtual void Execute();
};

#endif // _REPLACEDIALOGCOMMAND_H