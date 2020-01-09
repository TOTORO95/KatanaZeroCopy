#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	: m_bIsDead(false),
	m_fSpeed(0.f),
	m_fAngle(0.f),
	m_wstrImageKey(L"")
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));

}


CGameObject::~CGameObject()
{
}

const INFO & CGameObject::GetInfo() const
{
	return m_tInfo;
}

const RECT & CGameObject::GetRect() const
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

}

void CGameObject::SetAngle(float _x, float _y)
{
	float w = _x - m_tInfo.fX + g_fScrollX;
	float h = _y - m_tInfo.fY;
	float d = sqrtf(w * w + h * h);

	// 라디안 단위.
	m_fRadian = acosf(w / d);
	// acosf 함수가 구한 끼인각의 범위는 0 ~ 180도 이기에 다음과 같은 예외처리!
	if (m_tInfo.fY < _y)
		m_fRadian *= -1.f;

	m_fAngle = m_fRadian / PI * 180;
	cout << m_fAngle << " 도" << endl;
}

void CGameObject::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - m_tInfo.fCX * 0.5f);
	m_tRect.top = LONG(m_tInfo.fY - m_tInfo.fCY * 0.5f);
	m_tRect.right = LONG(m_tInfo.fX + m_tInfo.fCX * 0.5f);
	m_tRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY * 0.5f);
}
