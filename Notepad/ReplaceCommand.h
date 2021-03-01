// ReplaceCommand.h
#ifndef _REPLACECOMMAND_H
#define _REPLACECOMMAND_H
#include "EditCommand.h"

class ReplaceCommand : public EditCommand {
public:
	ReplaceCommand(NotepadForm *notepadForm = 0);
	virtual ~ReplaceCommand();
	virtual void Execute();
	virtual void UnExecute();
	virtual void ReExecute();

private:
	State *state;
	bool onIsReplacedCurrent;
	bool onIsMatchCase;
	bool onIsWrapAround;
};

#endif // _REPLACECOMMAND_H