// DummyLine.h
#ifndef _DUMMYLINE_H
#define _DUMMYLINE_H
#include "Line.h"

class DummyLine : public Line {
public:
	DummyLine(Long capacity = 256, bool onIsLine = false);
	DummyLine(const DummyLine& source);
	virtual ~DummyLine();
	virtual Glyph* Clone();
	DummyLine& operator =(const DummyLine& source);
};

#endif // _DUMMYLINE_H