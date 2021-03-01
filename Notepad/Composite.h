// Composite.h
#ifndef _COMPOSITE_H
#define _COMPOSITE_H
#include "Glyph.h"
#include "Array.h"

class Composite : public Glyph {
public:
	Composite(Long capacity = 256);
	Composite(const Composite& source);
	~Composite() = 0;
	virtual Long Add(Glyph *glyph);
	virtual Long Add(Long current, Glyph *glyph) { return -1; }
	virtual void Paste(Glyph *dummyNote) {  }
	virtual void Paste(string text) {  }
	virtual Long Remove(Long index);
	virtual bool RemoveSelect() { return false; }
	virtual void Split(Glyph *line, Long current) {  }
	virtual void Combine(Glyph *line) {  }
	virtual void Combine(Long index, Glyph *line) {  }
	virtual void Combine(Long currentLine) {  }
	virtual void CombineSelectedLines() {  }
	virtual void CombineAll() {  }
	virtual void Select(Long start, Long end, bool select = true) {  }
	virtual void Select(Long startLineCurrent, Long startNoteCurrent, Long endLineCurrent, Long endNoteCurrent, bool select = true) {  }
	virtual void SelectCount(Long startLineCurrent, Long startNoteCurrent, Long textCount) {  }
	virtual void SelectAll(bool select = true) {  }
	virtual bool FindPrevious(string strFindWhat, Long strFindWhatLen, bool onIsMatchCase = false) { return false; }
	virtual bool FindNext(string strFindWhat, Long strFindWhatLen, bool onIsMatchCase = false) { return false; }
	virtual Long First();
	virtual Long Previous() { return -1; }
	virtual Long PreviousWord() { return -1; }
	virtual Long Next() { return -1; }
	virtual Long NextWord() { return -1; }
	virtual Long Last(){ return -1; }
	virtual Long Move(Long index);
	virtual void MoveActualCurrent(Long lineCurrent, Long noteCurrent) {  }
	virtual Long MoveToFirstSelectedCurrent() { return -1; }
	virtual Long MoveToLastSelectedCurrent() { return -1; }
	virtual void GetCombineCurrent(Long *lineCurrent, Long *noteCurrent) {  }
	virtual Glyph* GetAt(Long index);
	virtual void GetSelectRange(Long *startLineCurrent, Long *startNoteCurrent, Long *endLineCurrent, Long *endNoteCurrent) {  }
	virtual string GetString(Long start, Long end) { return "\0"; }
	virtual string GetLowerCaseString() { return "\0"; };
	virtual string GetSelectString() { return "\0"; }
	virtual Long GetCapacity() const;
	virtual Long GetLength() const;
	virtual Long GetCurrent() const;
	virtual bool GetOnIsLine() const { return false; }
	virtual bool GetOnIsSelected() const { return false; }
	Composite& operator =(const Composite& source);

protected:
	Array<Glyph*> glyphs;
	Long capacity;
	Long length;
	Long current;
};

inline Long Composite::GetCapacity() const {
	return this->capacity;
}

inline Long Composite::GetLength() const {
	return this->length;
}

inline Long Composite::GetCurrent() const {
	return this->current;
}

#endif // _COMPOSITE_H