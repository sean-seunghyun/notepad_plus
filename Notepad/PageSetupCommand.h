// PageSetupCommand.h
#ifndef _PAGESETUPCOMMAND_H
#define _PAGESETUPCOMMAND_H
#include "Command.h"

class NotepadForm;
class PageSetupCommand :public Command {
public:
	PageSetupCommand(NotepadForm *notepadForm);
	virtual ~PageSetupCommand();
	virtual void Execute();
};

#endif // _PAGESETUPCOMMAND_H