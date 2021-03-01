// Matrix.h
#ifndef _MATRIX_H
#define _MATRIX_H
typedef signed long int Long;

class NotepadForm;
class Glyph;
class Matrix {
public:
	Matrix();
	Matrix(NotepadForm *notepadForm);
	Matrix(const Matrix& source);
	~Matrix();
	Long GetWidth(Long index);
	Long GetWidth(char(*text));
	Long GetHeight() const;
	Long GetX(Long current);
	Long GetMaxX();
	Long GetY(Long current);
	Long GetMaxY();
	Long GetDistance(Glyph *line, Long startXPos, Long endXPos);
	Long GetLineCurrent(Long x);
	Long GetNoteCurrent(Long y);
	Long GetSplitCurrent(Glyph *line);
	Long GetSplitCount(Glyph *line);
	Long GetStringCount(char(*text));
	bool GetOnIsGreaterThanScreen();
	Matrix& operator =(const Matrix& source);

private:
	NotepadForm *notepadForm;
	Long(*widths);
	Long height;
};

inline Long Matrix::GetHeight() const {
	return this->height;
}

#endif // _Matrix_H