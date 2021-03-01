// Letter.h
#ifndef _LETTER_H
#define _LETTER_H
#include "Glyph.h"

class Letter : public Glyph {
public:
	Letter();
	virtual ~Letter() = 0;
	virtual void Select(bool select = true);
	virtual bool GetOnIsSelected() const;

protected:
	bool onIsSelected;
};

inline bool Letter::GetOnIsSelected() const {
	return this->onIsSelected;
}

#endif // _LETTER_H