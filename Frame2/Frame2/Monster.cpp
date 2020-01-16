#include "stdafx.h"
#include "Monster.h"
#include "Bullet.h"

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
	m_iDetectRange = 500;
	m_eDirection = OBJ_IDLE;
	ZeroMemory(&m_tDetectRect, sizeof(m_tDetectRect));
	m_bIsTargetSet = false;
}


CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	
	m_fRadian=0;
}

int CMonster::Update()
{
	m_iCount+=1;
	UpdateWorldPos2();
	Pattern();
	UpdateRect2();
	UpdateDetectRect();

	if (m_bIsTargetSet)
	{
		if(m_iCount % 100 == 0)
			CObjectManager::GetInstance()->AddObject(BULLET, CObjFactory<CBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY, m_fRadian))	;

		m_bIsTargetSet = false;

	}

	return NO_EVENT;
}

void CMonster::Render(HDC hdc)
{
	Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	if (CKeyManager::GetInstance()->KeyPressing(KEY_O))
	{
		Rectangle(hdc, m_tDetectRect.left, m_tDetectRect.top, m_tDetectRect.right, m_tDetectRect.bottom);
	}
}

void CMonster::Release()
{
}

void CMonster::UpdateDetectRect()
{
	if (m_eDirection == OBJ_LEFT)
		m_tDetectRect = { (LONG)(m_WorldPos.x - m_iDetectRange),(LONG)(m_WorldPos.y - m_iDetectRange*0.5),(LONG)m_WorldPos.x,(LONG)m_tRect.bottom };
	else if (m_eDirection == OBJ_RIGHT)
	{
		m_tDetectRect = { (LONG)(m_WorldPos.x) ,
			(LONG)(m_WorldPos.y - m_iDetectRange*0.5),
			(LONG)(m_WorldPos.x + m_iDetectRange),
			(LONG)m_tRect.bottom };
	}

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
		m_eDirection = OBJ_RIGHT;
		m_tInfo.fX += m_fSpeed;
	}
	else
	{
		m_eDirection = OBJ_LEFT;
		m_tInfo.fX-= m_fSpeed;

	}


}


void CMonster::SetTarget(POINT targetInfo,bool isTarget)
{
	//m_tTargetPos = { (LONG)targetInfo.fX,(LONG)targetInfo.fY };
	SetAngle(targetInfo.x, targetInfo.y);
	//cout << m_fAngle << endl;

	m_bIsTargetSet = isTarget;
}
