#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
{

}


CMainGame::~CMainGame()
{
}

void CMainGame::Initialize()
{
	m_hdc = GetDC(g_hwnd);
	CBmpManager::GetInstance()->LoadBmp(L"BG", L"../Image/BackGround/Stage1BG.bmp",true);//1280 485
	LoadBmp(L"../Image/Player.bmp");
	m_fAngle = 0;
}

void CMainGame::Update()
{

	m_fAngle+=0.1;
}

void CMainGame::Render()
{
	tagRGBTRIPLE trg = { 0,0,0 };
	//cout << m_fAngle << endl;
	//Rectangle(m_hdc, 0, 0, 50, 50);

	//HDC hMemDC = CreateCompatibleDC(m_hdc);
	//SelectObject(hMemDC, m_hBitmap);
	//GdiTransparentBlt(m_hdc, 0, 0, 1296, 485, hMemDC, 0, 0, 1280, 485, RGB(0,0,0));

	//RotateSizingImage(m_hdc, m_hBitmap, m_fAngle, 1280 / 2, 485 / 2, 600, 300, trg);
	//SelectObject(m_hdc, CBmpManager::GetInstance()->GetBMP(L"BG"));						//됨
	//SelectObject(m_hdc, m_hBitmap);

	//RotateSizingImage(m_hdc, CBmpManager::GetInstance()->GetBMP(L"BG"), m_fAngle, 300, 300, 0, 150, 50, 50, 500, 400, trg, 0.1);
	RotateSizingImage(m_hdc, CBmpManager::GetInstance()->GetBMP(L"BG"), 50, 800, 300, 0, 0, 1600, 800, 500, 400, trg, 1);


	//BITMAP bm = RotateSizingImage(m_hdc, m_hBitmap, m_fAngle, 1280 / 2, 485 / 2, 600, 300);
	//cout << bm.bmWidth << "                    " << bm.bmHeight << endl;
	//BitBlt(m_hdc, 0, 0, WinCX, WinCY, hMemDC, 0, 0, SRCCOPY);
	//RotateSizingImage(hMemDC, m_hBitmap, m_fAngle, 1280 / 2, 485 / 2, 0, 0);

	//TransparentBlt()
	//GetClientRect()



}

void CMainGame::Release()
{
}

bool CMainGame::RotateSizingImage(HDC& hdc, HBITMAP hBmp, float dblAngle, int ixRotateAxis, int iyRotateAxis, int srcX, int srcY, int srcWidth, int srcHeight, int ixDisplay, int iyDisplay,tagRGBTRIPLE rgb, float dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{

	int i;
	BITMAP bm;
	GetObject(hBmp, sizeof(BITMAP), &bm);
	POINT apt[3] = { 0 };
	float dblWidth = (float)bm.bmWidth*dblSizeRatio;
	float dblHeight = (float)bm.bmHeight*dblSizeRatio;
	float ixRotate = (int)((float)ixRotateAxis*dblSizeRatio); // 크기가 변하는 것 고려
	float iyRotate = (int)((float)iyRotateAxis*dblSizeRatio);


	float dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
	dblRadian = dblAngle*PI / 180.0f;
	cosVal = cos(dblRadian), sinVal = sin(dblRadian);

	// 1. 회전축을 기준으로 상대좌표를 구하고 
	// 2. 회전후 위치좌표(상대좌표)를 얻은 후
	// 3. 얻은 값을 원래의 좌표에 적용.
	for (i = 0; i < 3; i++) {
		if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  꼭지점 부분
		else if (i == 1) { dblx = dblWidth - ixRotate, dbly = -iyRotate; }  // right up 꼭지점 부분
		else if (i == 2) { dblx = -ixRotate, dbly = dblHeight - iyRotate; } // left low 꼭지점 부분
		dblxDest = dblx*cosVal - dbly*sinVal;
		dblyDest = dblx*sinVal + dbly*cosVal;
		dblxDest += ixRotate, dblyDest += iyRotate;
		apt[i].x = ixDisplay - (long)ixRotate + (long)dblxDest;
		apt[i].y = iyDisplay - (long)iyRotate + (long)dblyDest; //*0.5 추가함;
	}



	//HDC hMemdc;
	//HDC hMemdc2;
	//HBITMAP hOldBmp, hTemp;

	//hMemdc = CreateCompatibleDC(hdc);
	//hMemdc2 = CreateCompatibleDC(hdc);
	////RECT rt;
	////GetClientRect (
	////FillRect(hMemdc, &rt, (HBRUSH)NULL_BRUSH);
	////FillRect(hMemdc2, &rt, (HBRUSH)NULL_BRUSH);
	//// 

	//hOldBmp = (HBITMAP)SelectObject(hMemdc2, hBmp);
	//hTemp = CreateCompatibleBitmap(hdc, bm.bmWidth, bm.bmHeight);
	//SelectObject(hMemdc, hTemp);
	////BOOL iRes = PlgBlt(hdc, apt, hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);

	//SelectObject(hMemdc2, hOldBmp);
	////BOOL iRes = PlgBlt(hdc, apt, hMemdc2, srcX, srcY, srcWidth, srcHeight, hMaskBmp, ixMask, iyMask);
	////TransparentBlt(hdc, 0, 0, srcWidth, srcHeight, hMemdc, 0, 0, srcWidth, srcHeight, RGB(0, 0, 0));

	//GdiTransparentBlt(hdc, 0, 0, srcWidth, srcHeight, hMemdc2, 0, 0, srcWidth, srcHeight, RGB(0, 0, 0));
	////cout << iRes << endl;

	//cout << bm.bmWidth << "                    " << bm.bmHeight << endl;

	//SelectObject(hMemdc2, hOldBmp);
	//SelectObject(hMemdc, hOldBmp);
	//DeleteDC(hMemdc);
	//DeleteDC(hMemdc2);
	//return true;
	//
	
//	HDC hMemdc;
//	HDC hMemdc2;
//	HBITMAP hOldBmp, hTemp;
//
//	hMemdc = CreateCompatibleDC(hdc);
//	hMemdc2 = CreateCompatibleDC(hdc);
//	/*RECT rt;
//	GetClientRect (
//	FillRect(hMemdc, &rt, (HBRUSH)NULL_BRUSH);
//	FillRect(hMemdc2, &rt, (HBRUSH)NULL_BRUSH);
//	 
//*/
//	hOldBmp = (HBITMAP)SelectObject(hMemdc2, hBmp);
//	hTemp = CreateCompatibleBitmap(hdc, bm.bmWidth, bm.bmHeight);
//	SelectObject(hMemdc, hTemp);
//	//BOOL iRes = PlgBlt(hdc, apt, hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
//
//	//SelectObject(hMemdc2, hOldBmp);
//	BOOL iRes = PlgBlt(hMemdc, apt, hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
//	TransparentBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));
//
//	//GdiTransparentBlt(hdc, 0, 0, srcWidth, srcHeight, hMemdc2, 0, 0, srcWidth, srcHeight, RGB(0, 0, 0));
//	//cout << iRes << endl;
//
//	//cout << bm.bmWidth << "                    " << bm.bmHeight << endl;
//
//	SelectObject(hMemdc2, hOldBmp);
//	//SelectObject(hMemdc, hOldBmp);
//	DeleteDC(hMemdc);
//	DeleteDC(hMemdc2);
//	return true;
//








	HDC hMemdc, hMemdc2, hMemdc3;
	//HDC hMemdc2;
	HBITMAP hOldBmp, hTemp,hTemp2;

	hMemdc = CreateCompatibleDC(hdc);
	hMemdc2 = CreateCompatibleDC(hdc);
	hMemdc3 = CreateCompatibleDC(hdc);

	hTemp = CreateCompatibleBitmap(hdc, bm.bmWidth, bm.bmHeight);
	hTemp2 = CreateCompatibleBitmap(hdc, bm.bmWidth, bm.bmHeight);


	hOldBmp = (HBITMAP)SelectObject(hMemdc, hBmp);
	SelectObject(hMemdc2, hTemp);
	SelectObject(hMemdc3, hTemp2);

	//BOOL iRes = PlgBlt(hdc, apt, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);

	//GdiTransparentBlt(hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));
	/*TransparentBlt(hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));
	BOOL iRes = PlgBlt(hdc, apt, hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
	TransparentBlt(hMemdc3, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255));*/

	SelectObject(hMemdc2, hOldBmp);

	//BOOL iRes = PlgBlt(hMemdc, apt, hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
	TransparentBlt(hdc, 0, 0, 1600, 800, hMemdc2, 0, 0, 1600, 800, RGB(0, 0, 0));
	//GdiTransparentBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));
	//GdiTransparentBlt(hdc, ixDisplay- bm.bmWidth, iyDisplay - bm.bmHeight, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));
	//cout << iRes << endl;

	cout << bm.bmWidth << "                    " << bm.bmHeight << endl;

	SelectObject(hMemdc2, hOldBmp);
	SelectObject(hMemdc, hOldBmp);
	DeleteDC(hMemdc);
	DeleteDC(hMemdc2);
	DeleteDC(hMemdc3);
	return true;

}
bool CMainGame::LoadBmp(const wstring& wstrFilePath)
{
	// 비트맵 읽어오기.
	m_hBitmap = (HBITMAP)LoadImage(nullptr, wstrFilePath.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (m_hBitmap == nullptr)
		return false;
	//cout << "df" << endl;
	//HDC hDC = GetDC(g_hwnd);

	//// CreateCompatibleDC: 출력DC와 호환이 되는 메모리DC를 생성하는 함수.
	//m_hMemDC = CreateCompatibleDC(hDC);

	//ReleaseDC(g_hwnd, hDC);
	//if (m_hMemDC == nullptr)
	//	return false;

	// 메모리DC에 불러온 비트맵을 미리 그린다.
	//m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	return true;
}

