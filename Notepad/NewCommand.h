// NewCommand.h
#ifndef _NEWCOMMAND_H
#define _NEWCOMMAND_H
#include "Command.h"

class NewCommand : public Command {
public:
	NewCommand(NotepadForm *notepadForm);
	virtual ~NewCommand();
	virtual void Execute();
};

#endif // _NEWCOMMAND_H