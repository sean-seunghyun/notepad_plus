// WrapLineCommand.h
#ifndef _WRAPLINECOMMAND_H
#define _WRAPLINECOMMAND_H
#include "Command.h"

class WrapLineCommand : public Command {
public:
	WrapLineCommand(NotepadForm *notepadForm);
	virtual ~WrapLineCommand();
	virtual void Execute();
};

#endif // _WRAPLINECOMMAND_H