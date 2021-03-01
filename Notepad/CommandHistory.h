//CommandHistory.h
#ifndef _COMMANDHISTORY_H
#define _COMMANDHISTORY_H

class NotepadForm;
class CommandStack;
class Command;
class CommandHistory {
public:
	NotepadForm *notepadForm;

public:
	CommandHistory(NotepadForm *notepadForm = 0);
	~CommandHistory();
	void Save(Command *command);
	void Undo();
	void Redo();

private:
	CommandStack *undoStack;
	CommandStack *redoStack;
};

#endif // !_COMMANDHISTORY_H
