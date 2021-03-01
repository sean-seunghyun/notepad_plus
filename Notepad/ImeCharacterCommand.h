// ImeCharacterCommand.h
#ifndef _IMECHARACTERCOMMAND_H
#define _IMECHARACTERCOMMAND_H
#include "WriteCommand.h"

class ImeCharacterCommand : public WriteCommand {
public:
	ImeCharacterCommand(NotepadForm *notepadForm);
	virtual ~ImeCharacterCommand();
	virtual void Execute();
	virtual void UnExecute();
	virtual void ReExecute();
	virtual Long GetLineCurrent();
	virtual Long GetNoteCurrent();
};

#endif // _IMECHARACTERCOMMAND_H