//CommandStack.h
#ifndef _COMMANDSTACK_H
#define _COMMANDSTACK_H


#include"Stack.h"
typedef signed long int Long;
class Command;

class CommandStack {
public:
	CommandStack(Long capacity = 16);
	~CommandStack();

	Long Push(Command *command);
	Command* Pop();
	Command* Peek();

	Long GetCapacity() const;
	Long GetLength() const;
private:
	Stack<Command*> commands;
	Long capacity;
	Long length;
};


inline Long CommandStack::GetCapacity() const {
	return this->capacity;
}

inline Long CommandStack::GetLength() const {
	return this->length;
}



#endif // !_COMMANDSTACK_H
