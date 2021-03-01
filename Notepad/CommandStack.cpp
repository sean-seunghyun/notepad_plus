//CommandStack.cpp
#include"CommandStack.h"
#include"Command.h"

CommandStack::CommandStack(Long capacity)
	: commands(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

CommandStack::~CommandStack() {
	Command *command;

	Long i = 0;
	while (i < this->length) {
		command = this->commands.Pop();
		if (command != 0) {
			delete command;
		}
		this->capacity--;
		this->length--;
	}
}

Long CommandStack::Push(Command *command) {
	Long index;
	index = this->commands.Push(command);
	this->capacity++;
	this->length++;

	return index;
}

Command* CommandStack::Pop() {
	Command *command;

	command = this->commands.Pop();
	this->capacity--;
	this->length--;

	return command;
}

Command* CommandStack::Peek() {
	Command* command;
	command = this->commands.Peek();

	return command;
}