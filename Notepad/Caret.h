// Caret.h
#ifndef _CARET_H
#define _CARET_H
typedef signed long int Long;

class CaretController;
class Caret {
public:
	CaretController *caretController;

public:
	Caret(CaretController *caretController);
	Caret(const Caret& source);
	~Caret();
	void Create(Long width, Long height);
	void Move(Long x, Long y);
	void Hide();
	Caret& operator =(const Caret& source);
};

#endif // _CARET_H