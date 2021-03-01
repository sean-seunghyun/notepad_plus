// Glyph.h
#ifndef _GLYPH_H
#define _GLYPH_H
//#include "atltypes.h"
#include <string>
using namespace std;
typedef signed long int Long;

class Glyph {
public:
	Glyph();
	virtual ~Glyph() = 0;
	virtual Long Add(Glyph *glyphLink) { return -1; }
	virtual Long Add(Long current, Glyph *glyph) { return -1; }
	virtual void Paste(Glyph *dummyNote) {  }
	virtual void Paste(string text) {  }
	virtual Long Remove(Long index) { return -1; }
	virtual bool RemoveSelect() { return false; }
	virtual void Split(Glyph *line, Long current) {  }
	virtual void Combine(Glyph *line) {  }
	virtual void Combine(Long index, Glyph *line) {  }
	virtual void Combine(Long currentLine) {  }
	virtual void CombineSelectedLines() {  }
	virtual void CombineAll() {  }
	virtual void Select(bool select = true) {  }
	virtual void Select(Long start, Long end, bool select = true) {  }
	virtual void Select(Long startLineCurrent, Long startNoteCurrent, Long endLineCurrent, Long endNoteCurrent, bool select = true) {  }
	virtual void SelectCount(Long startLineCurrent, Long startNoteCurrent, Long textCount) {  }
	virtual void SelectAll(bool select = true) {  }
	virtual bool FindPrevious(string strFindWhat, Long strFindWhatLen, bool onIsMatchCase = false) { return false; }
	virtual bool FindNext(string strFindWhat, Long strFindWhatLen, bool onIsMatchCase = false) { return false; }
	virtual Long First() { return -1; }
	virtual Long Previous() { return -1; }
	virtual Long PreviousWord() { return -1; }
	virtual Long Next() { return -1; }
	virtual Long NextWord() { return -1; }
	virtual Long Last() { return -1; }
	virtual Long Move(Long index) { return -1; }
	virtual void MoveActualCurrent(Long lineCurrent, Long noteCurrent) {  }
	virtual Long MoveToFirstSelectedCurrent() { return -1; }
	virtual Long MoveToLastSelectedCurrent() { return -1; }
	virtual void GetCombineCurrent(Long *lineCurrent, Long *noteCurrent) {  }
	virtual Glyph* GetAt(Long index) { return 0; }
	virtual void GetSelectRange(Long *startLineCurrent, Long *startNoteCurrent, Long *endLineCurrent, Long *endNoteCurrent) {  }
	virtual Glyph* Clone() = 0;
	virtual string GetString() = 0;
	virtual string GetString(Long start, Long end) { return "\0"; }
	virtual string GetSelectString() { return "\0"; }
	virtual string GetLowerCaseString() { return "\0"; };
	virtual Long GetCapacity() const { return 0; }
	virtual Long GetLength() const { return 0; }
	virtual Long GetCurrent() const { return -1; }
	virtual bool GetOnIsLine() const { return false; }
	virtual bool GetOnIsSelected() const { return false; }
};

#endif // _GLYPH_H