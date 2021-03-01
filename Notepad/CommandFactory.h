//CommandFactory.h
#ifndef _COMMANDFACTORY_H
#define _COMMANDFACTORY_H
#include<string>
using namespace std;
typedef signed long int Long;
class Command;
class NotepadForm;
class CommandFactory {
public:
	CommandFactory(NotepadForm *notepadForm);
	~CommandFactory();
	Command *Create(Long id);
public:
	NotepadForm *notepadForm;
};


#endif // !_COMMANDFACTORY_H
