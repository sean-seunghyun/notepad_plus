// PrintCommand.h
#ifndef _PRINTCOMMAND_H
#define _PRINTCOMMAND_H
#include "Command.h"

class PrintCommand : public Command {
public:
	PrintCommand(NotepadForm *notepadForm = 0);	
	virtual ~PrintCommand();
	virtual void Execute();
};

#endif // _PRINTCOMMAND_H