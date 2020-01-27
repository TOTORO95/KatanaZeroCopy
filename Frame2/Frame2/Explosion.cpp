#include "stdafx.h"
#include "Explosion.h"


CExplosion::CExplosion()
{
}

CExplosion::CExplosion(float fx, float fy)
{
	SetPos(fx, fy);

}


CExplosion::~CExplosion()
{
}

void CExplosion::Initialize()
{
	CBmpManager::GetInstance()->LoadBmp(L"explosion", L"../Image/HeadHunter/Explosion/Explosion.bmp");
	m_tFrame.dwFrameCount = 9;//432x66
	m_tFrame.dwFrameSpeed = 70;
	m_tFrame.dwFrameStart = 0;
	m_tFrame.dwFrameX = 48;
	m_tFrame.dwFrameY = 56;
	m_tFrame.dwOldTime = GetTickCount();
	m_bIsEnd = false;
}

int CExplosion::Update()
{
	if (m_bIsEnd)
		return DEAD_OBJ;
	UpdateWorldPos2();
	CGameObject::UpdateRect2();
	Animate();
	return NO_EVENT;
}

void CExplosion::Render(HDC hdc)
{
	GdiTransparentBlt(hdc,m_WorldPos.x , m_WorldPos.y, 144, 168, CBmpManager::GetInstance()->GetMemDC(L"explosion"),
		m_tFrame.dwFrameStart*m_tFrame.dwFrameX, 0,
		m_tFrame.dwFrameX, m_tFrame.dwFrameY, RGB(0, 0, 0));
}


void CExplosion::Animate()
{
	DWORD dwCurTime = GetTickCount();
	if (m_tFrame.dwOldTime + m_tFrame.dwFrameSpeed / g_fTime <= dwCurTime)
	{
		++m_tFrame.dwFrameStart;
		m_tFrame.dwOldTime = dwCurTime;
	}

	if (m_tFrame.dwFrameStart == m_tFrame.dwFrameCount)
	{
		m_bIsEnd = true;
		
	}


}
void CExplosion::Release()
{
}
