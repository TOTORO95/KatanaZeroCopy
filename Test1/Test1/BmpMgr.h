#pragma once
class CMyBmp;
class CBmpMgr
{
	DECLARE_SINGLETON(CBmpMgr)

public:
	CBmpMgr();
	~CBmpMgr();

public:
	HDC GetMemDC(const wstring& wstrImgKey) const;

public:
	void LoadBmp(const wstring& wstrImgKey, const wstring& wstrFilePath);
	BOOL RotateSizingImage(HDC hdc, HBITMAP hBmp, double dblAngle, int ixRotateAxis, int iyRotateAxis, int ixDisplay, int iyDisplay, double dblSizeRatio = 1, HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);

private:
	void Release();

private:
	map<wstring, CMyBmp*>	m_mapBmp;
};

