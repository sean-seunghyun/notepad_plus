//Stack.h
#ifndef _STACK_H
#define _STACK_H
typedef signed long int Long;
template <typename T>

class Stack {
public:
	Stack(Long capacity = 16);
	Stack(const Stack& source);
	~Stack();
	Long Push(T object);
	T Pop();
	T& Peek();
	Long GetCapacity() const;
	Long GetLength() const;
private:
	T(*top);
	Long capacity;
	Long length;
};

template <typename T>
inline Long Stack<T>::GetCapacity() const {
	return this->capacity;
}

template<typename T>
inline Long Stack<T>::GetLength() const {
	return this->length;
}


template<typename T>
Stack<T>::Stack(Long capacity) {
	this->top = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}


template<typename T>
Stack<T>::Stack(const Stack& source) {
	Long i = 0;
	this->top = new T[source.capacity];
	while (i < source.length) {
		this->top[i] = source.top[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

template<typename T>
Stack<T>::~Stack() {
	if (this->top != 0) {
		delete[] this->top;
	}
}

template<typename T>
Long Stack<T>::Push(T object) {

	Long index = 0;
	T(*top);
	Long i = 0;
	top = new T[this->capacity + 1];
	while (i < this->length) {
		top[i + 1] = this->top[i];
		i++;
	}
	if (this->top != 0) {
		delete[] this->top;
	}
	this->top = top;
	this->capacity++;
	this->top[index] = object;
	this->length++;

	return index;
}

template<typename T>
T Stack<T>::Pop() {
	Long index = -1;
	T(*top) = 0;
	Long i = 1;
	T ret = 0;

	if (this->length > 0) {
		ret = this->top[0];
	}

	if (this->capacity > 1) {
		top = new T[this->capacity - 1];
	}
	while (i < this->length) {
		top[i - 1] = this->top[i];
		i++;
	}

	if (this->top != 0) {
		delete[] this->top;
		this->top = 0;
	}
	if (this->capacity > 1) {
		this->top = top;
	}
	this->capacity--;
	this->length--;

	return ret;
}

template<typename T>
T& Stack<T>::Peek() {
	return this->top[0];
}

#endif // !_STACK_H