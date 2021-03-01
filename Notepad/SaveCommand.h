//SaveCommand.h
#ifndef _SAVECOMMAND_H
#define _SAVECOMMAND_H
#include"Command.h"

class SaveCommand :public Command {
public:
	SaveCommand(NotepadForm *notepadForm=0);
	virtual ~SaveCommand();
	virtual void Execute();
};

#endif // !_SAVECOMMAND_H
