// Font.h
#ifndef _FONT_H
#define _FONT_H
#include <afxwin.h>

class Font {
public:
	Font();
	Font(LOGFONT logFont, COLORREF color);
	Font(const Font& source);
	~Font();
	LOGFONT GetLogFont() const;
	COLORREF GetColorRef() const;
	Font& operator =(const Font& source);

private:
	LOGFONT logFont;
	COLORREF color;
};

inline LOGFONT Font::GetLogFont() const {
	return this->logFont;
}

inline COLORREF Font::GetColorRef() const {
	return this->color;
}

#endif // _FONT_H