#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
	:m_fAngle(0)
{

}


CMainGame::~CMainGame()
{
}

void CMainGame::Initialize()
{
	m_hdc = GetDC(g_hWnd);
	CBitmapManager::GetInstance()->InsertBitmap("bk", L"../Image/BossLaser3.bmp");//1280 800
	CBitmapManager::GetInstance()->InsertBitmap("skull", L"../Image/Skull.bmp");//15x15
	//if (LoadBmp(m_hBitmap[0],L"../Image/BossLaser3.bmp"))//1280x300
	//	cout << "성공" << endl;
	if (LoadBmp(m_hBitmap[0],L"../Image/BossLaser1.bmp"))//1280x300
		cout << "성공" << endl;
	if (LoadBmp(m_hBitmap[1],L"../Image/BossLaser2.bmp"))//1280x300
		cout << "성공" << endl;
}

void CMainGame::Update()
{
	m_fAngle+=0.2;

}

void CMainGame::Render()
{
	RECT rt;
	//GetClientRect(g_hWnd, &rt);
	//Rectangle(m_hdc, 0, 0, 1280, 800);
	//RotateSizingImage(m_hdc, m_hBitmap[1], m_fAngle, 1280, 15, 1100, 700, 1);

	if ((int)m_fAngle & 1)
		RotateSizingImage(m_hdc, m_hBitmap[0], m_fAngle, 1280, 15, 1100, 700, 1);
	else
		RotateSizingImage(m_hdc, m_hBitmap[1], m_fAngle, 1280, 15, 1100, 700, 1);

		//BitBlt(m_hdc, 0, 0, WinCX, WinCY,
	//	CBitmapManager::GetInstance()->FindBitmapDC("bk"), 0, 0, SRCCOPY);

	/*GdiTransparentBlt(m_hdc, 0, 0, 15 ,15, 
		CBitmapManager::GetInstance()->FindRotatedDC("skull", 90),
		0, 0, 15, 15, RGB(255, 255, 255));*/
	

}

void CMainGame::Release()
{
}
//
//bool CMainGame::RotateSizingImage(HDC& hdc, HBITMAP hBmp, float dblAngle, int ixRotateAxis, int iyRotateAxis, int srcX, int srcY, int srcWidth, int srcHeight, int ixDisplay, int iyDisplay, tagRGBTRIPLE rgb, float dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
//{
//
//	int i;
//	BITMAP bm;
//	GetObject(hBmp, sizeof(BITMAP), &bm);
//	POINT apt[3] = { 0 };
//	float dblWidth = (float)bm.bmWidth*dblSizeRatio;
//	float dblHeight = (float)bm.bmHeight*dblSizeRatio;
//	float ixRotate = (int)((float)ixRotateAxis*dblSizeRatio); // 크기가 변하는 것 고려
//	float iyRotate = (int)((float)iyRotateAxis*dblSizeRatio);
//
//
//	float dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
//	dblRadian = dblAngle*PI / 180.0f;
//	cosVal = cos(dblRadian), sinVal = sin(dblRadian);
//
//	// 1. 회전축을 기준으로 상대좌표를 구하고 
//	// 2. 회전후 위치좌표(상대좌표)를 얻은 후
//	// 3. 얻은 값을 원래의 좌표에 적용.
//	for (i = 0; i < 3; i++) {
//		if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  꼭지점 부분
//		else if (i == 1) { dblx = dblWidth - ixRotate, dbly = -iyRotate; }  // right up 꼭지점 부분
//		else if (i == 2) { dblx = -ixRotate, dbly = dblHeight - iyRotate; } // left low 꼭지점 부분
//		dblxDest = dblx*cosVal - dbly*sinVal;
//		dblyDest = dblx*sinVal + dbly*cosVal;
//		dblxDest += ixRotate, dblyDest += iyRotate;
//		apt[i].x = ixDisplay - (long)ixRotate + (long)dblxDest;
//		apt[i].y = iyDisplay - (long)iyRotate + (long)dblyDest; //*0.5 추가함;
//	}
//	HDC hMemdc, hMemdc2;
//	HBITMAP hOldBmp;
//	hMemdc = CreateCompatibleDC(hdc);
//	hMemdc2 = CreateCompatibleDC(hdc);
//	hOldBmp = (HBITMAP)SelectObject(hMemdc, hBmp);
//	BOOL iRes = PlgBlt(hdc, apt, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
//	GdiTransparentBlt(m_hdc, 0, 0, 1280, 485, hdc, 0, 0, 1280, 485, SRCCOPY);
//		return true;
//	//}
//}
//
//
//	HDC hMemdc;
//	HDC hMemdc2;
//	HBITMAP hOldBmp, hTemp;
//
//	hMemdc = CreateCompatibleDC(hdc);
//	hMemdc2 = CreateCompatibleDC(hdc);
//	RECT rt;
//	GetClientRect(g_hWnd, &rt);
//	FillRect(hMemdc, &rt, (HBRUSH)NULL_BRUSH);
//	FillRect(hMemdc2, &rt, (HBRUSH)NULL_BRUSH);
//	// 
//
//	hOldBmp = (HBITMAP)SelectObject(hMemdc2, hBmp);
//	//hTemp = CreateCompatibleBitmap(hdc, bm.bmWidth, bm.bmHeight);
//	//SelectObject(hMemdc, hTemp);
//	BOOL iRes = PlgBlt(hMemdc, apt, hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
//	SelectObject(hMemdc2, hOldBmp);
//	//BOOL iRes = PlgBlt(hdc, apt, hMemdc2, srcX, srcY, srcWidth, srcHeight, hMaskBmp, ixMask, iyMask);
//	TransparentBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));
//
//	//GdiTransparentBlt(hdc, 0, 0, srcWidth, srcHeight, hMemdc2, 0, 0, srcWidth, srcHeight, RGB(0, 0, 0));
//	//cout << iRes << endl;
//
//	cout << bm.bmWidth << "                    " << bm.bmHeight << endl;
//
//	SelectObject(hMemdc2, hOldBmp);
//	SelectObject(hMemdc, hOldBmp);
//	DeleteDC(hMemdc);
//	DeleteDC(hMemdc2);
//	return true;
//	
//	
////	HDC hMemdc;
////	HDC hMemdc2;
////	HBITMAP hOldBmp, hTemp;
////
////	hMemdc = CreateCompatibleDC(hdc);
////	hMemdc2 = CreateCompatibleDC(hdc);
////	/*RECT rt;
////	GetClientRect (
////	FillRect(hMemdc, &rt, (HBRUSH)NULL_BRUSH);
////	FillRect(hMemdc2, &rt, (HBRUSH)NULL_BRUSH);
////	 
////*/
////	hOldBmp = (HBITMAP)SelectObject(hMemdc2, hBmp);
////	hTemp = CreateCompatibleBitmap(hdc, bm.bmWidth, bm.bmHeight);
////	SelectObject(hMemdc, hTemp);
////	//BOOL iRes = PlgBlt(hdc, apt, hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
////
////	//SelectObject(hMemdc2, hOldBmp);
////	BOOL iRes = PlgBlt(hMemdc, apt, hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
////	TransparentBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));
////
////	//GdiTransparentBlt(hdc, 0, 0, srcWidth, srcHeight, hMemdc2, 0, 0, srcWidth, srcHeight, RGB(0, 0, 0));
////	//cout << iRes << endl;
////
////	//cout << bm.bmWidth << "                    " << bm.bmHeight << endl;
////
////	SelectObject(hMemdc2, hOldBmp);
////	//SelectObject(hMemdc, hOldBmp);
////	DeleteDC(hMemdc);
////	DeleteDC(hMemdc2);
////	return true;
//
//
//
//
//
//
//
//
//
//	//HDC hMemdc, hMemdc2, hMemdc3;
//	////HDC hMemdc2;
//	//HBITMAP hOldBmp, hTemp,hTemp2;
//
//	//hMemdc = CreateCompatibleDC(hdc);
//	//hMemdc2 = CreateCompatibleDC(hdc);
//	//hMemdc3 = CreateCompatibleDC(hdc);
//
//	//hTemp = CreateCompatibleBitmap(hdc, bm.bmWidth, bm.bmHeight);
//	//hTemp2 = CreateCompatibleBitmap(hdc, bm.bmWidth, bm.bmHeight);
//
//
//	//hOldBmp = (HBITMAP)SelectObject(hMemdc, hBmp);
//	//SelectObject(hMemdc2, hTemp);
//	//SelectObject(hMemdc3, hTemp2);
//
//	////BOOL iRes = PlgBlt(hdc, apt, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
//
//	////GdiTransparentBlt(hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));
//	///*TransparentBlt(hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));
//	//BOOL iRes = PlgBlt(hdc, apt, hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
//	//TransparentBlt(hMemdc3, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 255, 255));*/
//
//	//SelectObject(hMemdc2, hOldBmp);
//
//	////BOOL iRes = PlgBlt(hMemdc, apt, hMemdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
//	//TransparentBlt(hdc, 0, 0, 1600, 800, hMemdc2, 0, 0, 1600, 800, RGB(0, 0, 0));
//	////GdiTransparentBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));
//	////GdiTransparentBlt(hdc, ixDisplay- bm.bmWidth, iyDisplay - bm.bmHeight, bm.bmWidth, bm.bmHeight, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0, 0, 0));
//	////cout << iRes << endl;
//
//	//cout << bm.bmWidth << "                    " << bm.bmHeight << endl;
//
//	//SelectObject(hMemdc2, hOldBmp);
//	//SelectObject(hMemdc, hOldBmp);
//	//DeleteDC(hMemdc);
//	//DeleteDC(hMemdc2);
//	//DeleteDC(hMemdc3);
//	//return true;
//
//}
//void CMainGame::RotateSizingImage(HDC hdc, HBITMAP hBmp, RECT rt,
//double dblAngle,
//int ixRotateAxis, int iyRotateAxis,
//int ixDisplay, int iyDisplay,
//double dblSizeRatio,
//HBITMAP hMaskBmp, int ixMask, int iyMask){
//int i;
//BITMAP bm;
//GetObject(hBmp, sizeof(BITMAP), &bm);
//POINT apt[3] = { 0 };
//double dblWidth = (double)bm.bmWidth*dblSizeRatio;
//double dblHeight = (double)bm.bmHeight*dblSizeRatio;
//double ixRotate = (int)((double)ixRotateAxis*dblSizeRatio); // 크기가 변하는 것 고려
//double iyRotate = (int)((double)iyRotateAxis*dblSizeRatio);
//const double pi = 3.14159265358979323846;
//
//double dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
//dblRadian = dblAngle*pi / 180.0f;
//cosVal = cos(dblRadian), sinVal = sin(dblRadian);
//// 1. 회전축을 기준으로 상대좌표를 구하고 
//// 2. 회전후 위치좌표(상대좌표)를 얻은 후
//// 3. 얻은 값을 원래의 좌표에 적용.
//for (i = 0; i<3; i++) {
//	if (i == 0) { dblx = -ixRotate, dbly = -iyRotate; }    // left up  꼭지점 부분
//	else if (i == 1) { dblx = dblWidth - ixRotate, dbly = -iyRotate; }  // right up 꼭지점 부분
//	else if (i == 2) { dblx = -ixRotate, dbly = dblHeight - iyRotate; } // left low 꼭지점 부분
//	dblxDest = dblx*cosVal - dbly*sinVal;
//	dblyDest = dblx*sinVal + dbly*cosVal;
//	dblxDest += ixRotate, dblyDest += iyRotate;
//	apt[i].x = ixDisplay - (long)ixRotate + (long)dblxDest;
//	apt[i].y = iyDisplay - (long)iyRotate + (long)dblyDest;
//}
//HDC memdc, memdc2, memdc3;
//HBITMAP hBit2, hBit3;
//
//memdc = CreateCompatibleDC(hdc);
//memdc2 = CreateCompatibleDC(hdc);
//memdc3 = CreateCompatibleDC(hdc);
//
//
//hBit2 = CreateCompatibleBitmap(hdc, 800, 600);
//hBit3 = CreateCompatibleBitmap(hdc, 800, 600);
//
//SelectObject(memdc, hBmp);
//SelectObject(memdc2, hBit2);
//SelectObject(memdc3, hBit3);
//
//FillRect(memdc2, &rt, (HBRUSH)NULL_BRUSH);
//FillRect(memdc3, &rt, (HBRUSH)NULL_BRUSH);
//
//TransparentBlt(memdc2, 0, 0, bm.bmWidth, bm.bmHeight, memdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255, 0, 0));//<-이 RGB값은 출력할 비트맵의 알파값(?)수정해서 사용.
//PlgBlt(memdc3, apt, memdc2, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
//TransparentBlt(hdc, 0, 0, 800, 600, memdc3, 0, 0, 800, 600, RGB(255, 255, 255));//<-이 RGB는 건드리지않는다.
//
//
//																				/* 총정리 */
//																				/*
//																				1.회전할 그림을 디시 한개 생성해서 SelectObject해준다.그리고 다른디시에 TransBlt해준다.(그 다른디시에 FillRect해줌)
//																				2.1에서 출력한 디시를 PlgBlt해준다.다른디시에다가. 그 다른디시에 FillRect해줌.
//																				3. 2에서 출력한거를 hdc에다가 TransBlt해줌.그 브러시색깔로.ㅇㅋ?
//																				*/
//
//DeleteDC(memdc);
//DeleteDC(memdc2);
//DeleteDC(memdc3);
//
//DeleteObject(hBit3);
//DeleteObject(hBit2);
//
//}

bool CMainGame::LoadBmp(HBITMAP &hmp,const wstring& wstrFilePath)
{
	// 비트맵 읽어오기.
	hmp = (HBITMAP)LoadImage(nullptr, wstrFilePath.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hmp == nullptr)
		return false;
	
	//cout << "df" << endl;
	//HDC hDC = GetDC(g_hWnd);

	////// CreateCompatibleDC: 출력DC와 호환이 되는 메모리DC를 생성하는 함수.
	//m_hMemDC = CreateCompatibleDC(hDC);

	//ReleaseDC(g_hWnd, hDC);
	//if (m_hMemDC == nullptr)
	//	return false;

	//// 메모리DC에 불러온 비트맵을 미리 그린다.
	//m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	return true;
}

