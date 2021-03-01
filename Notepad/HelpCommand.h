// HelpCommand.h
#ifndef _HELPCOMMAND_H
#define _HELPCOMMAND_H
#include "Command.h"

class HelpCommand : public Command {
public:
	HelpCommand(NotepadForm *notepadForm = 0);
	virtual ~HelpCommand();
	virtual void Execute();
};

#endif // _HELPCOMMAND_H