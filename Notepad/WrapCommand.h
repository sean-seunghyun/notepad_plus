// WrapCommand.h
#ifndef _WRAPCOMMAND_H
#define _WRAPCOMMAND_H
#include "Command.h"

class WrapCommand : public Command {
public:
	WrapCommand(NotepadForm *notepadForm = 0);
	virtual ~WrapCommand();
	virtual void Execute();
};

#endif // _WRAPCOMMAND_H