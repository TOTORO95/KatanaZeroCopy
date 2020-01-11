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

	HDC		m_hMemDC; // �޸�DC: �ҷ��� ��Ʈ���� �̸� �׷����� DC
	Gdiplus::Image* m_CurImg;
	Gdiplus::Image* m_OldImg;
};

