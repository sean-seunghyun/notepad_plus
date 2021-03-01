// SingleByteLetter.h
#ifndef _SINGLEBYTELETTER_H
#define _SINGLEBYTELETTER_H
#include "Letter.h"

class SingleByteLetter : public Letter {
public:
	SingleByteLetter();
	SingleByteLetter(char script);
	SingleByteLetter(const SingleByteLetter& source);
	virtual ~SingleByteLetter();
	virtual Glyph* Clone();
	virtual string GetString();
	char GetScript() const;
	SingleByteLetter& operator =(const SingleByteLetter& source);

private:
	char script;
};

inline char SingleByteLetter::GetScript() const {
	return this->script;
}

#endif // _SINGLEBYTELETTER_H