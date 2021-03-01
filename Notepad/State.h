// State.h
#ifndef _STATE_H
#define _STATE_H
#include <string>
using namespace std;
typedef signed long int Long;

class Glyph;
class State {
public:
	State();
	State(Long lineCurrent, Long noteCurrent, string text);
	State(const State& source);
	~State();
	State& operator =(const State& source);
	Glyph* GetNote() const;
	Long GetLineCurrent() const;
	Long GetNoteCurrent() const;

private:
	Glyph *note;
	Long lineCurrent;
	Long noteCurrent;
};

inline Glyph* State::GetNote() const {
	return const_cast<Glyph*>(this->note);
}

inline Long State::GetLineCurrent() const {
	return this->lineCurrent;
}

inline Long State::GetNoteCurrent() const {
	return this->noteCurrent;
}

#endif // _STATE_H