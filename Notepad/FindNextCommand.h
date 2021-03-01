// FindNextCommand.h
#ifndef _FINDNEXTCOMMAND_H
#define _FINDNEXTCOMMAND_H
#include "EditCommand.h"

class FindNextCommand : public EditCommand {
public:
	FindNextCommand(NotepadForm *notepadForm = 0);
	virtual ~FindNextCommand();
	virtual void Execute();
};

#endif // _FINDNEXTCOMMAND_H