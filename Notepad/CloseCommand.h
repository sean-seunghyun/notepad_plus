// CloseCommand.h
#ifndef _CLOSECOMMAND_H
#define _CLOSECOMMAND_H
#include"Command.h"

class CloseCommand :public Command {
public:
	CloseCommand(NotepadForm *notepadForm = 0);
	virtual ~CloseCommand();
	virtual void Execute();
};

#endif // !_CLOSECOMMAND_H