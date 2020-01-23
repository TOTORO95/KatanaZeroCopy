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

	bool LoadBmp(HBITMAP &hmp,const wstring& wstrFilePath);

	BOOL RotateSizingImage(HDC hdc, HBITMAP hBmp,
		float fDgree,
		int ixRotateAxis, int iyRotateAxis,
		int ixDisplay, int iyDisplay,
		float dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0) {
		int i;
		BITMAP bm;
		GetObject(hBmp, sizeof(BITMAP), &bm);
		POINT apt[3] = { 0 };
		float fWidth = (double)bm.bmWidth*dblSizeRatio;
		float fHeight = (double)bm.bmHeight*dblSizeRatio;
		float ixRotate = (int)((float)ixRotateAxis*dblSizeRatio); // ũ�Ⱑ ���ϴ� �� ���
		float iyRotate = (int)((float)iyRotateAxis*dblSizeRatio);



		float fRadian, flx, fly, fxDest, fyDest, cosVal, sinVal;
		fRadian = fDgree*PI / 180.0f;
		cosVal = cos(fRadian), sinVal = sin(fRadian);

		// 1. ȸ������ �������� �����ǥ�� ���ϰ� 
		// 2. ȸ���� ��ġ��ǥ(�����ǥ)�� ���� ��
		// 3. ���� ���� ������ ��ǥ�� ����.
		for (i = 0; i < 3; i++) {
			if (i == 0) { flx = -ixRotate, fly = -iyRotate; }    // left up  ������ �κ�
			else if (i == 1) { flx = fWidth - ixRotate, fly = -iyRotate; }  // right up ������ �κ�
			else if (i == 2) { flx = -ixRotate, fly = fHeight - iyRotate; } // left low ������ �κ�
			fxDest = flx*cosVal - fly*sinVal;
			fyDest = flx*sinVal + fly*cosVal;
			fxDest += ixRotate, fyDest += iyRotate;
			apt[i].x = ixDisplay - (long)ixRotate + (long)fxDest;
			apt[i].y = iyDisplay - (long)iyRotate + (long)fyDest;
		}

		HDC hMemdc;
		HBITMAP hOldBmp;
		hMemdc = CreateCompatibleDC(hdc);
		hOldBmp = (HBITMAP)SelectObject(hMemdc, hBmp);
		BOOL iRes = PlgBlt(hdc, apt, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
		SelectObject(hMemdc, hOldBmp);
		DeleteDC(hMemdc);
		return iRes;
	}
private:
	HDC m_hdc;
	float m_fAngle;

private:
	HDC m_hMemDC;

	HBITMAP m_hBitmap[2];
	//HBITMAP m_hBitmap1;
	//HBITMAP m_hBitmap2;
	HBITMAP m_hOldBmp;
};

//HDC hMemdc, hMemdc2;
//HBITMAP hOldBmp;
//hMemdc = CreateCompatibleDC(hdc);
//hMemdc2 = CreateCompatibleDC(hdc);
//hOldBmp = (HBITMAP)SelectObject(hMemdc, hBmp);
//BOOL iRes = PlgBlt(hdc, apt, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
//GdiTransparentBlt(m_hdc, 0, 0, 1280, 485, hdc, 0, 0, 1280, 485, SRCCOPY);