#pragma once
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Render();
	void Release();
	bool RotateSizingImage(HDC& hdc, HBITMAP hBmp,
		float dblAngle,
		int ixRotateAxis, int iyRotateAxis,int srcX,int srcY,int srcWidth,int srcHeight,
		int ixDisplay, int iyDisplay, tagRGBTRIPLE rgb,
		float dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0); 
	bool LoadBmp(const wstring& wstrFilePath);


private:
	HDC m_hdc;
	float m_fAngle;

private:
	HDC m_hMemDC;
	HBITMAP m_hBitmap;
	HBITMAP m_hOldBmp;
};

//HDC hMemdc, hMemdc2;
//HBITMAP hOldBmp;
//hMemdc = CreateCompatibleDC(hdc);
//hMemdc2 = CreateCompatibleDC(hdc);
//hOldBmp = (HBITMAP)SelectObject(hMemdc, hBmp);
//BOOL iRes = PlgBlt(hdc, apt, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
//GdiTransparentBlt(m_hdc, 0, 0, 1280, 485, hdc, 0, 0, 1280, 485, SRCCOPY);