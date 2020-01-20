#include "stdafx.h"
#include "Fan.h"


CFan::CFan()
{
}

CFan::CFan(float fx, float fy)
{
	SetPos(fx, fy);
}


CFan::~CFan()
{
}

void CFan::Initialize()
{
	CBmpManager::GetInstance()->LoadBmp(L"Fan", L"../Image/Trap/Fan.bmp");//1221x96
	CBmpManager::GetInstance()->LoadBmp(L"Fanfg", L"../Image/Trap/Fanfg.bmp");//1221x96
	m_tFrame.dwFrameCount = 32;
	m_tFrame.dwFrameSpeed = 1;
	m_tFrame.dwFrameStart = 0;
	m_tFrame.dwFrameX = 37;
	m_tFrame.dwFrameY = 0;
	m_tFrame.dwOldTime = GetTickCount();
	
}

int CFan::Update()
{
	UpdateWorldPos2();
	UpdateRect2();
	Animate();
	return NO_EVENT;
}

void CFan::Render(HDC hdc)
{
	//cout << m_tRect.left <<"  " << m_tRect.top << endl;
	//cout << m_tFrame.dwFrameStart<< "       "  <<m_tFrame.dwFrameX << endl;

	//GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, 200, 600,
	//	CBmpManager::GetInstance()->GetMemDC(L"Fan"),
	//	m_tFrame.dwFrameStart*m_tFrame.dwFrameX, 0, 
	//	m_tFrame.dwFrameX, m_tFrame.dwFrameY, RGB(0, 0, 0));
	GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, 37*1.5,96*1.5,
		CBmpManager::GetInstance()->GetMemDC(L"Fan"),
		m_tFrame.dwFrameStart*m_tFrame.dwFrameX, 0, 
		37, 96, RGB(0,0,0));

	GdiTransparentBlt(hdc, m_tRect.left+25, m_tRect.top-18, 67, 172,
		CBmpManager::GetInstance()->GetMemDC(L"Fanfg"),
		0,0,
		67, 172, RGB(0, 0, 0));

}

void CFan::Release()
{
}

void CFan::Animate()
{

	DWORD dwCurTime = GetTickCount();
	if (m_tFrame.dwOldTime + m_tFrame.dwFrameSpeed / g_fTime <= dwCurTime)
	{
		++m_tFrame.dwFrameStart;
		m_tFrame.dwOldTime = dwCurTime;
	}

	if (m_tFrame.dwFrameStart == m_tFrame.dwFrameCount)
	{
		m_tFrame.dwFrameStart = 0;
	}
}

