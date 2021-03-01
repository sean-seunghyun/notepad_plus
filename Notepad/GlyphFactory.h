// GlyphFactory.h
#ifndef _GLYPHFACTORY_H
#define _GLYPHFACTORY_H
typedef signed long int Long;

class Glyph;
class GlyphFactory {
public:
	GlyphFactory();
	~GlyphFactory();
	Glyph* Create(char(*text), bool onIsLine = true);
};

#endif // _GLYPHFACTORY_H