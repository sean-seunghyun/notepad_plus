// StatusBarCommand.h
#ifndef _STATUSBARCOMMAND_H
#define _STATUSBARCOMMAND_H
#include "Command.h"

class StatusBarCommand : public Command {
public:
	StatusBarCommand(NotepadForm *notepadForm = 0);
	StatusBarCommand(const StatusBarCommand& source);
	virtual ~StatusBarCommand();
	virtual void Execute();
	StatusBarCommand& operator =(const StatusBarCommand& source);
};

#endif // _STATUSBARCOMMAND_H