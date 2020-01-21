#include "stdafx.h"
#include "LaserTrap.h"


LaserTrap::LaserTrap()
{
}

LaserTrap::LaserTrap(float fx, float fy, float fLaserRange)
{
	SetPos(fx, fy);
	m_fAtkRange = fLaserRange;
}


LaserTrap::~LaserTrap()
{
}

void LaserTrap::Initialize()
{
	CBmpManager::GetInstance()->LoadBmp(L"LaserOn", L"../Image/Trap/LaserOn.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LaserOff", L"../Image/Trap/LaserOff.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Laser", L"../Image/Trap/Laser.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LaserShot", L"../Image/Trap/LaserShot.bmp");

	m_tFrame.dwFrameCount = 3;
	m_tFrame.dwFrameSpeed = 30;
	m_tFrame.dwFrameStart = 0;
	m_tFrame.dwFrameX = 9;
	m_tFrame.dwFrameY = 500;
	m_tFrame.dwOldTime = GetTickCount();

	m_tAtkFrame.dwFrameCount = 5;
	m_tAtkFrame.dwFrameSpeed = 30;
	m_tAtkFrame.dwFrameStart = 0;
	m_tAtkFrame.dwFrameX = 9;
	m_tAtkFrame.dwFrameY = 500;
	m_tAtkFrame.dwOldTime = GetTickCount();
	m_iCount = 0;
}

int LaserTrap::Update()
{
	UpdateWorldPos2();
	UpdateRect2();
	Animate();





	return NO_EVENT;
}

void LaserTrap::Render(HDC hdc)
{
	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, 18, 16,
		CBmpManager::GetInstance()->GetMemDC(L"LaserOn"), 
		0, 0, 9, 8, RGB(0, 0, 0));
	
	if (m_bIsColl)
	{
		GdiTransparentBlt(hdc, m_WorldPos.x+7 , m_WorldPos.y + 16, 5, m_fAtkRange,
			CBmpManager::GetInstance()->GetMemDC(L"LaserShot"),
			m_tAtkFrame.dwFrameStart*m_tAtkFrame.dwFrameX, 0, 9, 500, RGB(0, 0, 0));

	}
	else
	{
		GdiTransparentBlt(hdc, m_WorldPos.x+7 , m_WorldPos.y + 16, 3, m_fAtkRange,
			CBmpManager::GetInstance()->GetMemDC(L"Laser"),
			m_tFrame.dwFrameStart*m_tFrame.dwFrameX, 0, 9, 500, RGB(0, 0, 0));

	}


	//PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT ,PS_DASHDOTDOT
	/*HPEN pen = (HPEN)CreatePen(PS_DOT, 0, RGB(255, 0, 0));
	HPEN open = (HPEN)SelectObject(hdc, pen);
	MoveToEx(hdc, m_WorldPos.x+9, m_WorldPos.y+16, NULL);
	LineTo(hdc, m_WorldPos.x + 9, m_WorldPos.y+530);

	SelectObject(hdc, open);
	DeleteObject(pen);*/
}

void LaserTrap::Release()
{
}

void LaserTrap::Animate()
{
	DWORD dwCurTime = GetTickCount();
	if (m_tFrame.dwOldTime + m_tFrame.dwFrameSpeed / g_fTime <= dwCurTime)
	{
		++m_tFrame.dwFrameStart;
		m_tFrame.dwOldTime = dwCurTime;
	}

	if (m_tFrame.dwFrameStart == m_tFrame.dwFrameCount)
		m_tFrame.dwFrameStart = 0;
	if (m_bIsColl)
	{
		m_iCount++;
		if (m_iCount == 1)
		{
			m_OldScroll = { (LONG)g_fScrollX,(LONG)g_fScrollY };
		}
		if (m_iCount < 10)
		{
			g_fScrollX += sinf(GetTickCount()) * 5;
			g_fScrollY += cosf(GetTickCount()) * 2.5;
		}
		if (m_iCount == 10)
		{
			g_fScrollX = m_OldScroll.x;
			g_fScrollY = m_OldScroll.y;
		}
		if (m_tAtkFrame.dwOldTime + m_tAtkFrame.dwFrameSpeed / g_fTime <= dwCurTime)
		{
			++m_tAtkFrame.dwFrameStart;
			m_tAtkFrame.dwOldTime = dwCurTime;
		}

		if (m_tAtkFrame.dwFrameStart == m_tAtkFrame.dwFrameCount)
		{
			m_tAtkFrame.dwFrameStart = 0;
			m_iCount = 0;
			m_bIsColl = false;
		}
	}
}
