#pragma once
class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();
public:
	HDC GetMemDC() const;
	HBITMAP GetBMP() { return m_hBitmap; }

public:
	bool LoadBmp(const wstring& wstrFilePath);
	bool LoadBmp(const wstring& wstrFilePath, bool isRot);
	
private:
	void Release();

private:
		HBITMAP	m_hBitmap;
		HBITMAP	m_hOldBmp;
	HDC		m_hMemDC; // 메모리DC: 불러온 비트맵을 미리 그려놓을 DC

};

