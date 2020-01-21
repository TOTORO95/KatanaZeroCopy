#include "stdafx.h"
#include "Grunt.h"

CGrunt::CGrunt()
{

}

CGrunt::CGrunt(float fposX, float fPosY)
{
	m_eObjType = MONSTER;
	m_tFixPos = { (LONG)fposX,(LONG)fPosY };
	SetPos(fposX, fPosY);
	SetSize(50, 50);
	m_fSpeed = 2.5;
	m_eDirection = OBJ_IDLE;
	ZeroMemory(&m_tDetectRect, sizeof(m_tDetectRect));
	m_wstrImageKey = L"Right";

	m_eMonsterType = GRUNT;
	m_bIsTargetSet = false;
	m_iCount = 0;
	m_iAttackRate = 50;
}


CGrunt::~CGrunt()
{
}

void CGrunt::Initialize()
{
	CBmpManager::GetInstance()->LoadBmp(L"RGrunt", L"../Image/Monster/RGrunt.bmp");//800x550
	CBmpManager::GetInstance()->LoadBmp(L"LGrunt", L"../Image/Monster/LGrunt.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LSlash", L"../Image/Monster/LGruntSlash.bmp");//256x64
	CBmpManager::GetInstance()->LoadBmp(L"RSlash", L"../Image/Monster/RGruntSlash.bmp");//256x64


	m_wstrRImageKey = L"RGrunt";
	m_wstrLImageKey = L"LGrunt";


	m_iDetectRange = 400;
	m_fJumpAcc = 0;
	m_tFrame.dwFrameStart = 0;
	m_tFrame.dwFrameCount = 8;
	m_tFrame.dwFrameX = 50;
	m_tFrame.dwFrameY = 0;
	m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
	m_tFrame.dwOldTime = GetTickCount();
	m_HitRange = 50;

	m_iCount = 0;
	m_fCount = 0;
	m_fRadian = 0;
	m_bisStop = false;
}

int CGrunt::Update()
{
	if (m_bIsDead)
	{
		UpdateWorldPos2();
		UpdateRect2();
		//m_eCurState = STATE_DEAD;
		Move();
		ChangeState();
		Animate();
		return NO_EVENT;
	}
	UpdateWorldPos2();
	Pattern();
	UpdateRect2();
	UpdateDetectRect();
	Animate();
	ChangeState();
	Move();

	return NO_EVENT;
}

void CGrunt::Render(HDC hdc)
{
	if (m_bIsDead)
	{
		GdiTransparentBlt(hdc, m_tRect.left - m_tInfo.fCX*0.5, m_tRect.top - m_tInfo.fCY*0.5, m_tInfo.fCX * 2, m_tInfo.fCY * 2,
			CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
			m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
			m_tFrame.dwFrameY,
			50, 50, RGB(0, 0, 0));
		if (!m_bIsBettackEnd)
		{
			if (m_wstrImageKey == L"RGrunt")
			{
				GdiTransparentBlt(hdc, m_tRect.left - 25, m_tRect.top - 25,
					75, 75,
					CBmpManager::GetInstance()->GetMemDC(L"LImpact"),
					m_tBeattackFrame.dwFrameX*m_tBeattackFrame.dwFrameStart,
					m_tBeattackFrame.dwFrameY,
					50, 50, RGB(0, 0, 0));
			}
			else
			{
				GdiTransparentBlt(hdc, m_tRect.left - 25, m_tRect.top - 25,
					75, 75,
					CBmpManager::GetInstance()->GetMemDC(L"RImpact"),
					m_tBeattackFrame.dwFrameX*m_tBeattackFrame.dwFrameStart,
					m_tBeattackFrame.dwFrameY,
					50, 50, RGB(0, 0, 0));
			}
		}
		return;
	}
	GdiTransparentBlt(hdc, m_tRect.left - m_tInfo.fCX*0.5, m_tRect.top - m_tInfo.fCY*0.5, m_tInfo.fCX * 2, m_tInfo.fCY * 2,
		CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
		m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
		m_tFrame.dwFrameY,
		50, 50, RGB(0, 0, 0));
	if (CKeyManager::GetInstance()->KeyPressing(KEY_O))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		Rectangle(hdc, m_tDetectRect.left, m_tDetectRect.top, m_tDetectRect.right, m_tDetectRect.bottom);
	}

}

void CGrunt::Release()
{
}

void CGrunt::Attack()
{
		if (m_bIsTargetSet)
		{
			m_iCount++;
			if (m_iCount % m_iAttackRate-1 == 0)
				m_OldScroll = { (LONG)g_fScrollX,(LONG)g_fScrollY };
			if (m_iCount >= m_iAttackRate)
			{
				g_fScrollX += sinf(GetTickCount()) * 5;
				g_fScrollY += cosf(GetTickCount()) * 2.5;
				if (m_iCount >= m_iAttackRate+2)
				{
					g_fScrollX = m_OldScroll.x;
					g_fScrollY = m_OldScroll.y;

					m_iCount = 0;
					m_bIsTargetSet = false;

				}
			}
		}


}

void CGrunt::ChangeState()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE_IDLE:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 8;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 0;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_RUN:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 10;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 50;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_WALK:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 10;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 100;
			m_tFrame.dwFrameSpeed = 200; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_AIMING:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 8;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 150;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_DEAD:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 16;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 200;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}


