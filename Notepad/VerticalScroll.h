// VerticalScroll.h
#ifndef _VERTICALSCROLL_H
#define _VERTICALSCROLL_H
#include "Scroll.h"

class VerticalScroll : public Scroll {
public:
	VerticalScroll();
	VerticalScroll(Long min, Long max, Long unit, Long page, Long current);
	VerticalScroll(const VerticalScroll& source);
	virtual ~VerticalScroll();
	virtual Scroll* Clone(Long min, Long max, Long unit, Long page, Long current);
	VerticalScroll& operator =(const VerticalScroll& source);
};

#endif // _VERTICALSCROLL_H