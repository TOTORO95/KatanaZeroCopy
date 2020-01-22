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
	m_eObjType = BULLET;
	m_eBulletTag = MONSTER_BULLET;
	m_tEffectPos = { 0,0 };
	m_tOldPos = { 0,0 };
	m_fSpeed = 1;
	SetSize(10, 10);
	m_Reverce = false;
	m_frame.dwFrameCount = 5;
	m_frame.dwFrameSpeed = 100;
	m_frame.dwFrameStart = 0;
	m_frame.dwFrameX = 70;
	m_frame.dwFrameY = 0;
	m_frame.dwOldTime = GetTickCount();
	m_iCount = 0;
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
	m_tOldPos = { (LONG)m_WorldPos.x,(LONG)m_WorldPos.y };
	if (!m_Reverce)
	{
		if (m_fSpeed < 40)
			m_fSpeed+=3;
		//m_tOldPos.x += cosf(m_fRadian) * m_fSpeed;
		//m_tOldPos.x -= sinf(m_fRadian) * m_fSpeed;
		m_tInfo.fX+= cosf(m_fRadian) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fRadian) * m_fSpeed;
	}
	else
	{
		if (m_fSpeed < 40)
			m_fSpeed += 3;
		m_tInfo.fX -= cosf(m_fRadian) * m_fSpeed;
		m_tInfo.fY += sinf(m_fRadian) * m_fSpeed;
	}

	return NO_EVENT;
}

void CBullet::Render(HDC hdc)
{
	HPEN pen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	HPEN open = (HPEN)SelectObject(hdc, pen);
	MoveToEx(hdc, m_tOldPos.x, m_tOldPos.y, NULL);
	LineTo(hdc, m_tInfo.fX- g_fScrollX, m_tInfo.fY+ g_fScrollY);
	SelectObject(hdc, open);
	DeleteObject(pen);

	if (m_Reverce)
	{
		Animate();
		GdiTransparentBlt(hdc, m_tEffectPos.x-64, m_tEffectPos.y-64, 128, 128,
			CBmpManager::GetInstance()->GetMemDC(L"BulletReflect"),m_frame.dwFrameX*m_frame.dwFrameStart ,m_frame.dwFrameY , 70, 64, RGB(0, 0, 0));
	}
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
		m_tEffectPos = m_WorldPos;
	m_eBulletTag = PLAYER_BULLET;
	m_Reverce = true;
}

void CBullet::Animate()
{
	DWORD dwCurTime = GetTickCount();
	m_iCount++;
	if (m_frame.dwOldTime + m_frame.dwFrameSpeed / g_fTime <= dwCurTime)
	{
		++m_frame.dwFrameStart;
		m_frame.dwOldTime = dwCurTime;
	}
	if (m_iCount == 1)
	{
		m_OldScroll = { (LONG)g_fScrollX,(LONG)g_fScrollY };
	}
	if (m_iCount <= 5)
	{
		if (m_iCount &1)
		{
			g_fScrollX += sinf(GetTickCount()) * 10;
			g_fScrollY += cosf(GetTickCount()) * 10;
		}
		else
		{
			g_fScrollX = m_OldScroll.x;
			g_fScrollY = m_OldScroll.y;
		}

	}
	if (m_iCount == 5)
	{
		g_fScrollX = m_OldScroll.x;
		g_fScrollY = m_OldScroll.y;
	}

	if (m_frame.dwFrameStart == m_frame.dwFrameCount)
	{
		return;
	}

}
