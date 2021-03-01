// RedoCommand.h
#ifndef _REDOCOMMAND_H
#define _REDOCOMMAND_H
#include "Command.h"

class RedoCommand : public Command {
public:
	RedoCommand(NotepadForm *notepadForm);
	virtual ~RedoCommand();
	virtual void Execute();
};

#endif // _REDOCOMMAND_H