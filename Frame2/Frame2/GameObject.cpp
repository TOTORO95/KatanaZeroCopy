#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	: m_bIsDead(false),
	m_fSpeed(0.f),
	m_fAngle(0.f),
	m_wstrImageKey(L""),
	m_bIsColl(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));

}


CGameObject::~CGameObject()
{
}

INFO & CGameObject::GetInfo() 
{
	return m_tInfo;
}

RECT & CGameObject::GetRect() 
{
	return m_tRect;
}

void CGameObject::SetImageKey(const wstring & wstrImageKey)
{
	m_wstrImageKey = wstrImageKey;
}


void CGameObject::SetPos(float x, float y)
{
	m_tInfo.fX = x;
	m_tInfo.fY = y;
}

void CGameObject::SetSize(float x, float y)
{
	m_tInfo.fCX = x;
	m_tInfo.fCY = y;
}


void CGameObject::SetAngle(float degree)
{
	m_fRadian = degree;
}

void CGameObject::SetAngle(float _x, float _y)
{
	float w = _x - m_tInfo.fX + g_fScrollX;
	float h = _y - m_tInfo.fY +g_fScrollY;
	float d = sqrtf(w * w + h * h);

	// 라디안 단위.
	m_fRadian = acosf(w / d);
	// acosf 함수가 구한 끼인각의 범위는 0 ~ 180도 이기에 다음과 같은 예외처리!
	if (m_WorldPos.y< _y)
		m_fRadian *= -1.f;

	m_fAngle = m_fRadian / PI * 180;
	//cout << m_fAngle << " 도" << endl;
}

float CGameObject::Lerp(float src, float dest,float t)
{
	float cur = src*(1 - t) + dest*t;
	return cur;
}

void CGameObject::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - m_tInfo.fCX * 0.5f);
	m_tRect.top = LONG(m_tInfo.fY - m_tInfo.fCY * 0.5f);
	m_tRect.right = LONG(m_tInfo.fX + m_tInfo.fCX * 0.5f);
	m_tRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY * 0.5f);
}

void CGameObject::UpdateWorldPos()
{
	m_WorldPos = {(LONG) (m_tInfo.fX - g_fScrollX)
		,(LONG)(m_tInfo.fY+g_fScrollY )};
}
void CGameObject::UpdateRect2()
{
	m_tRect.left = LONG(m_WorldPos.x- m_tInfo.fCX * 0.5f );
	m_tRect.top = LONG(m_WorldPos.y - m_tInfo.fCY * 0.5f);
	m_tRect.right = LONG(m_WorldPos.x + m_tInfo.fCX * 0.5f);
	m_tRect.bottom = LONG(m_WorldPos.y + m_tInfo.fCY * 0.5f);
}
void CGameObject::UpdateWorldPos2()
{
	m_WorldPos = { (LONG)(m_tInfo.fX - g_fScrollX)
		,(LONG)(m_tInfo.fY - g_fScrollY) };
}

bool CGameObject::RotateSizingImage(HDC & hdc, HBITMAP hBmp, float dblAngle, int ixRotateAxis, int iyRotateAxis, int srcX, int srcY, int srcWidth, int srcHeight, int ixDisplay, int iyDisplay, tagRGBTRIPLE rgb, float dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
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


	HDC hMemdc;
	HDC hMemdc2;
	HBITMAP hOldBmp, hTemp;

	hMemdc = CreateCompatibleDC(hdc);
	hMemdc2 = CreateCompatibleDC(hdc);

	hOldBmp = (HBITMAP)SelectObject(hMemdc2, hBmp);
	hTemp = CreateCompatibleBitmap(hdc, bm.bmWidth, bm.bmHeight);
	SelectObject(hMemdc, hTemp);
	BOOL iRes = PlgBlt(hdc, apt, hMemdc2, srcX, srcY, srcWidth, srcHeight, hMaskBmp, ixMask, iyMask);

	SelectObject(hMemdc2, hOldBmp);
	DeleteDC(hMemdc);
	DeleteDC(hMemdc2);
	return true;
}
