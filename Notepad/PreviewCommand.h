// PreviewCommand.h
#ifndef _PREVIEWCOMMAND_H
#define _PREVIEWCOMMAND_H
#include "Command.h"

class PreviewCommand : public Command {
public:
	PreviewCommand(NotepadForm *notepadForm = 0);
	virtual ~PreviewCommand();
	virtual void Execute();
};

#endif // _PREVIEWCOMMAND_H