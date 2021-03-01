//OpenCommand.h
#ifndef _OPENCOMMAND_H
#define _OPENCOMMAND_H
#include"Command.h"
class OpenCommand :public Command {
public:
	OpenCommand(NotepadForm *notepadForm);
	virtual ~OpenCommand();
	virtual void Execute();
};


#endif // !_OPENCOMMAND_H
