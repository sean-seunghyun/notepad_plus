// GoToLineCommand.h
#ifndef _GOTOLINECOMMAND_H
#define _GOTOLINECOMMAND_H
#include "Command.h"

class GoToLineCommand : public Command {
public:
	GoToLineCommand(NotepadForm *notepadForm = 0);
	virtual ~GoToLineCommand();
	virtual void Execute();
};

#endif // _GOTOLINECOMMAND_H