// CharacterCommand.h
#ifndef _CHARACTERCOMMAND_H
#define _CHARACTERCOMMAND_H
#include "WriteCommand.h"

class CharacterCommand : public WriteCommand {
public:
	CharacterCommand(NotepadForm *notepadForm);
	virtual ~CharacterCommand();
	virtual void Execute();
	virtual void UnExecute();
	virtual void ReExecute();
	virtual bool GetOnIsEnter();
	virtual Long GetLineCurrent();
	virtual Long GetNoteCurrent();

private:
	bool onIsEnter;
};

inline bool CharacterCommand::GetOnIsEnter() {
	return this->onIsEnter;
}

#endif // _CHARACTERCOMMAND_H