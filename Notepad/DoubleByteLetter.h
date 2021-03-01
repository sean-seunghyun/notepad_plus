// DoubleByteLetter.h
#ifndef _DOUBLEBYTELETTER_H
#define _DOUBLEBYTELETTER_H
#include "Letter.h"

class DoubleByteLetter : public Letter {
public:
	DoubleByteLetter();
	DoubleByteLetter(char(*script));
	DoubleByteLetter(const DoubleByteLetter& source);
	virtual ~DoubleByteLetter();
	virtual Glyph* Clone();
	virtual string GetString();
	char* GetScript() const;
	DoubleByteLetter& operator =(const DoubleByteLetter& source);

private:
	char script[2];
};

inline char* DoubleByteLetter::GetScript() const {
	return const_cast<char*>(this->script);
}

#endif // _DOUBLEBYTELETTER_H