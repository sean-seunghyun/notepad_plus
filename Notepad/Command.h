#ifndef _COMMAND_H
#define _COMMAND_H
class NotepadForm;

class Command {
public:
	NotepadForm *notepadForm;

public:
	Command();
	virtual ~Command() = 0;
	virtual void Execute() = 0;
};



#endif // !_COMMAND_H
