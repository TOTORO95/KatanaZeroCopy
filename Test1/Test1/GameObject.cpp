#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}

void CGameObject::SetAngle(INFO _info)
{
	float fx = _info.fPosX - m_tInfo.fPosX;
	float fy = _info.fPosY - m_tInfo.fPosY;
	m_fRadian=atan2f(fx, fy);
	m_fDegree = m_fRadian / PI * 180;
	cout << m_fDegree<<" µµ" << endl;
	m_tAimInfo.fPosX = -cosf(m_fRadian);
	m_tAimInfo.fPosY = sinf(m_fRadian);

}

void CGameObject::SetAngle(float _x, float _y)
{
	float fx = _x-m_tInfo.fPosX ;
	float fy = _y-m_tInfo.fPosY ;
	m_fRadian = atan2f(fx,fy);

	m_fDegree = m_fRadian / PI * 180;
	cout << m_fDegree<<"µµ"<< endl;
	m_tAimInfo.fPosX = -cosf(m_fRadian);
	m_tAimInfo.fPosY = sinf(m_fRadian);

}


bool CGameObject::IsDead()
{
	return m_bIsDead;
}

float CGameObject::Lerp(float value1, float value2, float amount)
{
	return float(value1 + ((float)(value2 - value1) * amount));
}


void CGameObject::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fPosX - m_tInfo.fCX * 0.5f);
	m_tRect.top = LONG(m_tInfo.fPosY - m_tInfo.fCY * 0.5f);
	m_tRect.right = LONG(m_tInfo.fPosX + m_tInfo.fCX * 0.5f);
	m_tRect.bottom = LONG(m_tInfo.fPosY + m_tInfo.fCY * 0.5f);

}
