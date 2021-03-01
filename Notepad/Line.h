// Line.h
#ifndef _LINE_H
#define _LINE_H
#include "Composite.h"

class Line : public Composite {
public:
	Line(Long capacity = 256, bool onIsLine = true);
	Line(const Line& source);
	virtual ~Line();
	virtual Long Add(Long current, Glyph *glyph);
	virtual bool RemoveSelect();
	virtual void Split(Glyph *line, Long current);
	virtual void Combine(Glyph *line);
	virtual void Combine(Long index, Glyph *line);
	virtual void Select(bool onIsSelect = true);
	virtual void Select(Long start, Long end, bool onIsSelect = true);
	virtual void SelectAll(bool onIsSelect = true);
	virtual Long Previous();
	virtual Long PreviousWord();
	virtual Long Next();
	virtual Long NextWord();
	virtual Long Last();
	virtual Long MoveToFirstSelectedCurrent();
	virtual Long MoveToLastSelectedCurrent();
	virtual string GetString();
	virtual string GetString(Long startXPos, Long endXPos);
	virtual string GetSelectString();
	virtual Glyph* Clone();
	virtual bool GetOnIsLine() const;
	virtual bool GetOnIsSelected() const;
	Line& operator =(const Line& source);

protected:
	bool onIsLine;
	bool onIsSelected;
};

inline bool Line::GetOnIsLine() const {
	return this->onIsLine;
}

inline bool Line::GetOnIsSelected() const {
	return this->onIsSelected;
}

#endif // _LINE_H