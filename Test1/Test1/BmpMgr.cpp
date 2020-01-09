#include "stdafx.h"
#include "BmpMgr.h"
#include "MyBmp.h"

IMPLEMENT_SINGLETON(CBmpMgr)

CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
	Release();
}

HDC CBmpMgr::GetMemDC(const wstring& wstrImgKey) const
{
	auto iter_find = m_mapBmp.find(wstrImgKey);

	if (m_mapBmp.end() == iter_find)
		return nullptr;

	return iter_find->second->GetMemDC();
}

void CBmpMgr::LoadBmp(const wstring& wstrImgKey, const wstring& wstrFilePath)
{
	auto iter_find = m_mapBmp.find(wstrImgKey);

	if (m_mapBmp.end() != iter_find)
		return;

	CMyBmp* pBmp = new CMyBmp;

	if (!pBmp->LoadBmp(wstrFilePath))
	{
		SafeDelete(pBmp);
		MessageBox(nullptr, wstrFilePath.c_str(), L"Image Load Failed", MB_OK);
		return;
	}


	m_mapBmp.insert(make_pair(wstrImgKey, pBmp));
}

BOOL CBmpMgr::RotateSizingImage(HDC hdc, HBITMAP hBmp, double dblAngle, int ixRotateAxis, int iyRotateAxis, int ixDisplay, int iyDisplay, double dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	int i;
	BITMAP bm;
	GetObject(hBmp, sizeof(BITMAP), &bm);
	POINT apt[3] = { 0 };
	double dblWidth = (double)bm.bmWidth*dblSizeRatio;
	double dblHeight = (double)bm.bmHeight*dblSizeRatio;
	double ixRotate = (int)((double)ixRotateAxis*dblSizeRatio); // 크기가 변하는 것 고려
	double iyRotate = (int)((double)iyRotateAxis*dblSizeRatio);
	const double pi = 3.14159265358979323846;

	double dblRadian, dblx, dbly, dblxDest, dblyDest, cosVal, sinVal;
	dblRadian = dblAngle*pi / 180.0f;
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
		apt[i].y = iyDisplay - (long)iyRotate + (long)dblyDest;
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

	


void CBmpMgr::Release()
{
	for (auto& MyPair : m_mapBmp)
		SafeDelete(MyPair.second);

	m_mapBmp.clear();
}