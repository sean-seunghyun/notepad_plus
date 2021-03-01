// Scroll.h
#ifndef _SCROLL_H
#define _SCROLL_H
typedef signed long int Long;

class Scroll {
public:
	Scroll();
	Scroll(Long min, Long max, Long unit, Long page, Long current);
	Scroll(const Scroll& source);
	virtual ~Scroll() = 0;
	void First();
	void PreviousUnit();
	void NextUnit();
	void PreviousPage();
	void NextPage();
	void Last();
	void Move(Long amount);
	virtual Scroll* Clone(Long min, Long max, Long unit, Long page, Long current) { return 0; }
	Scroll& operator =(const Scroll& source);
	Long GetMin() const;
	Long GetMax() const;
	Long GetUnit() const;
	Long GetPage() const;
	Long GetCurrent() const;

protected:
	Long min;
	Long max;
	Long unit;
	Long page;
	Long current;
};

inline Long Scroll::GetMin() const {
	return this->min;
}

inline Long Scroll::GetMax() const {
	return this->max;
}

inline Long Scroll::GetUnit() const {
	return this->unit;
}

inline Long Scroll::GetPage() const {
	return this->page;
}

inline Long Scroll::GetCurrent() const {
	return this->current;
}

#endif // _SCROLL_H