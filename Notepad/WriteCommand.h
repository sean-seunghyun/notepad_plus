// WriteCommand.h
#ifndef _WRITECOMMAND_H
#define _WRITECOMMAND_H
#include "EditCommand.h"

class WriteCommand : public EditCommand {
public:
	WriteCommand(NotepadForm *notepadForm = 0);
	virtual ~WriteCommand();
	virtual void Execute() {  }
	virtual void UnExecute() {  }
	virtual void ReExecute() {  }
	virtual bool GetOnIsNew();
	virtual bool GetOnIsMore();
	virtual bool GetOnIsEnter() { return false; }
	virtual Long GetLineCurrent() { return -1; }
	virtual Long GetNoteCurrent() { return -1; }
	virtual void SetOnIsNew(bool onIsNew = true);

protected:
	State *state;
	bool onIsNew;
	bool onIsMore;
	bool onIsSelected;
};

inline bool WriteCommand::GetOnIsNew() {
	return this->onIsNew;
}

inline bool WriteCommand::GetOnIsMore() {
	return this->onIsMore;
}

#endif // _WRITECOMMAND_H