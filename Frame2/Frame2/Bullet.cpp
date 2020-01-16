#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}

CBullet::CBullet(float x, float y,POINT targetpos)
{
	SetPos(x, y);
	
	SetPosVector(targetpos);
}


CBullet::~CBullet()
{
}

void CBullet::Initialize()
{
	
	m_tOldPos = { 0,0 };
	m_fSpeed = 15;
	SetSize(15, 15);
	m_Reverce = false;
	m_frame.dwFrameCount = 5;
	m_frame.dwFrameSpeed = 100;
	m_frame.dwFrameStart = 0;
	m_frame.dwFrameX = 70;
	m_frame.dwFrameY = 0;
	m_frame.dwOldTime = GetTickCount();
}

int CBullet::Update()
{
	UpdateWorldPos();
	UpdateRect2();

	if (m_bIsDead)
		return DEAD_OBJ;

	if (-1000 > m_WorldPos.x || -1000 > m_WorldPos.y ||
		(float)2000 <m_WorldPos.x || (float)1500 <m_WorldPos.y)
		return DEAD_OBJ;
	cout << m_fRadian << endl;
	if (!m_Reverce)
	{
		m_tInfo.fX += cosf(m_fRadian) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fRadian) * m_fSpeed;
	}
	else
	{
		m_tInfo.fX -= cosf(m_fRadian) * m_fSpeed;
		m_tInfo.fY += sinf(m_fRadian) * m_fSpeed;
	}
	cout << m_fRadian << endl;
	return NO_EVENT;
}

void CBullet::Render(HDC hdc)
{
	Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	if (m_Reverce)
	{
		Animate();
		GdiTransparentBlt(hdc, m_tOldPos.x-64, m_tOldPos.y-64, 128, 128,
			CBmpManager::GetInstance()->GetMemDC(L"BulletReflect"),m_frame.dwFrameX*m_frame.dwFrameStart ,m_frame.dwFrameY , 70, 64, RGB(0, 0, 0));
	}
		//cout << "애니 출력"<< m_frame.dwFrameX*m_frame.dwFrameStart << endl;
}

void CBullet::Release()
{
}

void CBullet::SetPosVector(POINT targetPos)
{
	SetAngle(targetPos.x, targetPos.y);
	m_posVector.x = cosf(m_fRadian);
	m_posVector.y = sinf(m_fRadian);

}

void CBullet::ReflectionBullet()
{
	if (!m_Reverce)
		m_tOldPos = m_WorldPos;
	m_Reverce = true;
}

void CBullet::Animate()
{
	DWORD dwCurTime = GetTickCount();

	if (m_frame.dwOldTime + m_frame.dwFrameSpeed / g_fTime <= dwCurTime)
	{
		++m_frame.dwFrameStart;
		m_frame.dwOldTime = dwCurTime;
	}
	if (m_frame.dwFrameStart < 2)
	{
		g_fScrollX += sinf(GetTickCount()) * 5;
		g_fScrollY += cosf(GetTickCount()) * 2.5;
	}

	//cout <<"애니 카운트"<< m_frame.dwFrameCount << endl;
	if (m_frame.dwFrameStart == m_frame.dwFrameCount)
	{
		g_fScrollY = 0;
		return;
	}

}
