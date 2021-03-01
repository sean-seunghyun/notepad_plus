// Note.h
#ifndef _NOTE_H
#define _NOTE_H
#include "Composite.h"

class Note : public Composite {
public:
	Note(Long capacity = 256);
	Note(const Note& source);
	virtual ~Note();
	virtual Long Add(Long current, Glyph *glyph);
	virtual void Paste(Glyph *dummyNote);
	virtual void Paste(string text);
	virtual bool RemoveSelect();
	virtual void Combine(Long currentLine);
	virtual void CombineSelectedLines();
	virtual void CombineAll();
	virtual void Select(Long startLineCurrent, Long startNoteCurrent, Long endLineCurrent, Long endNoteCurrent, bool onIsSelect = true);
	virtual void SelectCount(Long startLineCurrent, Long startNoteCurrent, Long textCount);
	virtual void SelectAll(bool onIsSelect = true);
	virtual bool FindPrevious(string strFindWhat, Long strFindWhatLen, bool onIsMatchCase = false);
	virtual bool FindNext(string strFindWhat, Long strFindWhatLen, bool onIsMatchCase = false);
	virtual Long Previous();
	virtual Long Next();
	virtual Long Last();
	virtual void MoveActualCurrent(Long lineCurrent, Long noteCurrent);
	virtual Long MoveToFirstSelectedCurrent();
	virtual Long MoveToLastSelectedCurrent();
	virtual void GetCombineCurrent(Long *lineCurrent, Long *noteCurrent);
	virtual void GetSelectRange(Long *startLineCurrent, Long *startNoteCurrent, Long *endLineCurrent, Long *endNoteCurrent);
	virtual Glyph* Clone();
	virtual string GetString();
	virtual string GetSelectString();
	virtual bool GetOnIsSelected() const;
	Note& operator =(const Note& source);
};

#endif // _NOTE_H