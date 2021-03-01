
//SaveAsCommand.h
#ifndef _SAVEASCOMMAND_H
#define _SAVEASCOMMAND_H
#include"Command.h"

class SaveAsCommand :public Command {
public:
	SaveAsCommand(NotepadForm *notepadForm = 0);
	virtual ~SaveAsCommand();
	virtual void Execute();
};



#endif // !_SAVECOMMAND_H
