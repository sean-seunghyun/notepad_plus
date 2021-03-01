// HorizontalScroll.h
#ifndef _HORIZONTALSCROLL_H
#define _HORIZONTALSCROLL_H
#include "Scroll.h"

class HorizontalScroll : public Scroll {
public:
	HorizontalScroll();
	HorizontalScroll(Long min, Long max, Long unit, Long page, Long current);
	HorizontalScroll(const HorizontalScroll& source);
	virtual ~HorizontalScroll();
	virtual Scroll* Clone(Long min, Long max, Long unit, Long page, Long current);
	HorizontalScroll& operator =(const HorizontalScroll& source);
};

#endif // _HorizontalScroll_H