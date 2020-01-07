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
	cout << m_fDegree << " 도" << endl;
	m_tAimInfo.fPosX = -cosf(m_fRadian);
	m_tAimInfo.fPosY = sinf(m_fRadian);

}

void CGameObject::SetAngle(float _x, float _y)
{
	//float fx = _x-m_tInfo.fPosX ;
	//float fy = _y-m_tInfo.fPosY ;
	//m_fRadian = atan2f(fx,fy);

	//m_fDegree = m_fRadian / PI * 180;
	//cout << m_fDegree<<"도"<< endl;
	//m_tAimInfo.fPosX = -cosf(m_fRadian);
	//m_tAimInfo.fPosY = sinf(m_fRadian);
	// 

	float w = _x - m_tInfo.fPosX + g_fScrollX;
	float h = _y - m_tInfo.fPosY;
	float d = sqrtf(w * w + h * h);

	// 라디안 단위.
	m_fRadian = acosf(w / d);
	// acosf 함수가 구한 끼인각의 범위는 0 ~ 180도 이기에 다음과 같은 예외처리!
	if (m_tInfo.fPosY < _y)
		m_fRadian *= -1.f;

	m_fDegree = m_fRadian / PI * 180;
	cout << m_fDegree << " 도" << endl;


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
