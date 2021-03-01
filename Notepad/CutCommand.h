// CutCommand.h
#ifndef _CUTCOMMAND_H
#define _CUTCOMMAND_H
#include "EditCommand.h"

class CutCommand : public EditCommand {
public:
	CutCommand(NotepadForm *notepadForm = 0);
	virtual ~CutCommand();
	virtual void Execute();
	virtual void UnExecute();
	virtual void ReExecute();
};

#endif // _CUTCOMMAND_H