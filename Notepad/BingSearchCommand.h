// BingSearchCommand.h
#ifndef _BINGSEARCHCOMMAND_H
#define _BINGSEARCHCOMMAND_H
#include "Command.h"

class BingSearchCommand : public Command {
public:
	BingSearchCommand(NotepadForm *notepadForm = 0);
	virtual ~BingSearchCommand();
	virtual void Execute();
};

#endif // _BINGSEARCHCOMMAND_H