// FindCommand.h
#ifndef _FINDCOMMAND_H
#define _FINDCOMMAND_H
#include "Command.h"

class FindCommand : public Command {
public:
	FindCommand(NotepadForm *notepadForm = 0);
	virtual ~FindCommand();
	virtual void Execute();
};

#endif // _FINDCOMMAND_H