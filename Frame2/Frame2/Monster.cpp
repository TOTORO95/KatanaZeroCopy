#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}

CMonster::CMonster(float fposX, float fPosY)
{
	m_tFixPos = { (LONG)fposX,(LONG)fPosY };
	SetPos(fposX, fPosY);
	//m_WorldPos.x = fposX;
	//m_WorldPos.y = fPosY;
	SetSize(50, 50);
	m_fSpeed = 1.5;
}


CMonster::~CMonster()
{
}

void CMonster::Initialize()
{

}

int CMonster::Update()
{
	UpdateWorldPos2();
	Pattern();
	UpdateRect2();
	m_iCount+=1;
	//cout << m_tInfo.fX<< "  " << m_tInfo.fY<< endl;
	//cout << m_WorldPos.x << "  " << m_WorldPos.y << endl;
	return NO_EVENT;
}

void CMonster::Render(HDC hdc)
{
	Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	
}

void CMonster::Release()
{
}

void CMonster::Attack()
{
}

void CMonster::BeAttack()
{
}

void CMonster::Pattern()
{
	//float fpos = fabs(m_tInfo.fX - m_tFixPos.x);
	if (sinf(m_iCount) >= 0)
	{
		m_tInfo.fX += m_fSpeed;
	}
	else
	{
		m_tInfo.fX-= m_fSpeed;
	}


}
