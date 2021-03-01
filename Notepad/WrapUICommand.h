// WrapUICommand.h
#ifndef _WRAPUICOMMAND_H
#define _WRAPUICOMMAND_H
#include "Command.h"

class WrapUICommand : public Command {
public:
	WrapUICommand(NotepadForm *notepadForm = 0);
	virtual ~WrapUICommand();
	virtual void Execute();
};

#endif // _WRAPUICOMMAND_H