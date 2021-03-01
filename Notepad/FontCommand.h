// FontCommand.h
#ifndef _FONTCOMMAND_H
#define _FONTCOMMAND_H
#include "Command.h"

class FontCommand : public Command {
public:
	FontCommand(NotepadForm *notepadForm);
	virtual ~FontCommand();
	virtual void Execute();
};

#endif // _FONTCOMMAND_H