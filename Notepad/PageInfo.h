//PageInfo.h
#ifndef _PAGEINFO_H
#define _PAGEINFO_H
#include<afxwin.h>
typedef signed long int Long;
class NotepadForm;
class PageInfo {
public:
	PageInfo(NotepadForm *notepadForm = 0);
	PageInfo(POINT paperSize, Long devMode, RECT margin, CString header, CString footer);
	~PageInfo();
	POINT GetPaperSize() const;
	Long GetDevMode() const;
	RECT GetMargin() const;
	CString GetHeader() const;
	CString GetFooter() const;

private:
	POINT paperSize;
	Long devMode;
	RECT margin;
	CString header;
	CString footer;
};

inline POINT PageInfo::GetPaperSize() const {
	return this->paperSize;
}
inline Long PageInfo::GetDevMode() const {
	return this->devMode;
}
inline RECT PageInfo::GetMargin() const {
	return this->margin;
}
inline CString PageInfo::GetHeader() const {
	return this->header;
}
inline CString PageInfo::GetFooter() const {
	return this->footer;
}



#endif // !_PAGEINFO_H
