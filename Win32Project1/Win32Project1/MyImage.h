#pragma once
class Image;
class CMyImage
{
public:
	CMyImage();
	~CMyImage();
public:
	HDC GetMemDC() const;

public:
	bool LoadBmp(const wstring& wstrFilePath);

private:
	void Release();

private:
	//HBITMAP	m_hBitmap;
	//HBITMAP	m_hOldBmp;

	HDC		m_hMemDC; // 메모리DC: 불러온 비트맵을 미리 그려놓을 DC
	Gdiplus::Image* m_CurImg;
	Gdiplus::Image* m_OldImg;
};

