// DeleteCommand.h
#ifndef _DELETECOMMAND_H
#define _DELETECOMMAND_H
#include "EditCommand.h"

class DeleteCommand : public EditCommand {
public:
	DeleteCommand(NotepadForm *notepadForm = 0);
	virtual ~DeleteCommand();
	virtual void Execute();
	virtual void UnExecute();
	virtual void ReExecute();
	virtual bool GetOnIsNew();
	virtual bool GetOnIsEnter();
	virtual Long GetLineCurrent();
	virtual Long GetNoteCurrent();
	virtual void SetOnIsNew(bool onIsNew = true);

private:
	bool onIsNew;
	bool onIsSelected;
	bool onIsEnter;
};

inline bool DeleteCommand::GetOnIsNew() {
	return this->onIsNew;
}

inline bool DeleteCommand::GetOnIsEnter() {
	return this->onIsEnter;
}

#endif // _DELETECOMMAND_H