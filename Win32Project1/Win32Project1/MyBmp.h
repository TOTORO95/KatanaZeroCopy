#pragma once
class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();
public:
	HDC GetMemDC() const;
	HBITMAP GetBMP() { return m_hBitmap; }
	//void SetBitmap(HBITMAP hBitmap){}
public:
	bool LoadBmp(const wstring& wstrFilePath);
	bool LoadBmp(const wstring& wstrFilePath, bool isRot);
	
private:
	void Release();
	//BOOL RotateSizingImage(HDC hdc, HBITMAP hBmp, float flAngle, int ixRotateAxis, int iyRotateAxis, int ixDisplay, int iyDisplay, float flSizeRatio = 1, HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);

private:

	HBITMAP	m_hBitmap;
	HBITMAP	m_hOldBmp;
	HDC		m_hMemDC; // 메모리DC: 불러온 비트맵을 미리 그려놓을 DC

};
