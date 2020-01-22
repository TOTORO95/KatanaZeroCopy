#include "stdafx.h"
#include "HeadHunter.h"


CHeadHunter::CHeadHunter()
{
}

CHeadHunter::CHeadHunter(float fPosX, float fPosY)
{
	m_eObjType = MONSTER;
	m_tFixPos = { (LONG)fPosX,(LONG)fPosY };
	SetPos(fPosX, fPosY);
	SetSize(50, 50);
	m_fSpeed = 2.5;
	m_eDirection = OBJ_IDLE;
	ZeroMemory(&m_tDetectRect, sizeof(m_tDetectRect));
	m_wstrImageKey = L"LGunster";

	m_eMonsterType = HEADHUNTER;
	m_bIsTargetSet = false;
	m_iAttackRate = 100;
	m_bIsBettackEnd = false;
	m_tOldPos = { (LONG)fPosX,(LONG)fPosY };
	
}


CHeadHunter::~CHeadHunter()
{
}

void CHeadHunter::Initialize()
{
	CBmpManager::GetInstance()->LoadBmp(L"LGunster", L"../Image/Monster/LGunsterSheet.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"BossLaser", L"../Image/Monster/BossLaser3.bmp");//1280x120

	m_wstrRImageKey = L"RGunster";
	m_wstrLImageKey = L"LGunster";

	m_iDetectRange = 2000;
	m_fJumpAcc = 0;
	m_tFrame.dwFrameStart = 0;
	m_tFrame.dwFrameCount = 8;
	m_tFrame.dwFrameX = 50;
	m_tFrame.dwFrameY = 0;
	m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
	m_tFrame.dwOldTime = GetTickCount();
	m_HitRange = 1000;
	m_tLaserFrame.dwFrameCount = 10;
	m_tLaserFrame.dwFrameSpeed = 50;
	m_tLaserFrame.dwFrameStart = 0;
	m_tLaserFrame.dwFrameX = 1280;
	m_tLaserFrame.dwFrameY = 30;
	m_tLaserFrame.dwOldTime = GetTickCount();

	m_iCount = 0;
	m_fCount = 0;
	m_fRadian = 0;
	m_bisStop = false;
	m_fLaserRate = 0;
}

int CHeadHunter::Update()
{
	UpdateWorldPos2();
	UpdateRect2();
	UpdateDetectRect();
	Pattern();
	Move();
	Animate();
	ChangeState();
	cout << m_fAngle << endl;
	//cout <<"X="<< m_tTargetPos.x<< "Y="<<m_tTargetPos.y	 << endl;
	return NO_EVENT;
}

void CHeadHunter::Render(HDC hdc)
{

	//cout << "보스" <<m_WorldPos.x<<"y=" <<m_WorldPos.y<< endl;
	
	GdiTransparentBlt(hdc, m_tRect.left - m_tInfo.fCX*0.5, m_tRect.top - m_tInfo.fCY, m_tInfo.fCX * 2, m_tInfo.fCY * 2,
		CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
		m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
		m_tFrame.dwFrameY,
		50, 50, RGB(0, 0, 0));
	//레이져
	RightShot(hdc);

	if (CKeyManager::GetInstance()->KeyPressing(KEY_O))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		Rectangle(hdc, m_tDetectRect.left, m_tDetectRect.top, m_tDetectRect.right, m_tDetectRect.bottom);
	}
}

void CHeadHunter::Patroll()
{
}

void CHeadHunter::Release()
{
}


void CHeadHunter::Pattern()
{
}

void CHeadHunter::RightShot(HDC hdc)
{
	AimLine(hdc);

	GdiTransparentBlt(hdc, m_tRect.left - 1280, m_tRect.top + 10 + m_fCount, 1280, 15 - m_fCount * 2,
		CBmpManager::GetInstance()->GetMemDC(L"BossLaser"),
		0, m_tLaserFrame.dwFrameY*m_tLaserFrame.dwFrameStart,
		1280, 30, RGB(0, 0, 0));
}

void CHeadHunter::Animate()
{
	DWORD dwCurTime = GetTickCount();
	if (m_eCurState != STATE_DEAD)
	{

		if (m_tFrame.dwOldTime + m_tFrame.dwFrameSpeed / g_fTime <= dwCurTime)
		{
			++m_tFrame.dwFrameStart;
			m_tFrame.dwOldTime = dwCurTime;
		}

		if (m_tFrame.dwFrameStart == m_tFrame.dwFrameCount)
			m_tFrame.dwFrameStart = 0;


		if (m_tLaserFrame.dwOldTime + m_tLaserFrame.dwFrameSpeed / g_fTime <= dwCurTime)
		{
			m_fCount += 1;
			++m_tLaserFrame.dwFrameStart;
			m_tLaserFrame.dwOldTime = dwCurTime;
		}

		if (m_tLaserFrame.dwFrameStart == m_tLaserFrame.dwFrameCount)
		{
			m_tLaserFrame.dwFrameStart = 0;
			m_fCount = 0;
		}
	}

}

void CHeadHunter::AimLine(HDC hdc)
{

	HPEN pen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	HPEN open = (HPEN)SelectObject(hdc, pen);
	MoveToEx(hdc,m_WorldPos.x + cosf(m_fRadian)*30, m_WorldPos.y-10 - sinf(m_fRadian)*30, NULL);
	LineTo(hdc, m_WorldPos.x+cosf(m_fRadian)*1280, m_WorldPos.y-sinf(m_fRadian) * 1280);
	SelectObject(hdc, open);
	DeleteObject(pen);

}



void CHeadHunter::ChangeState()
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
			m_tFrame.dwFrameCount = 8;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 100;
			m_tFrame.dwFrameSpeed = 200; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_MELEE:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 4;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 150;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_DEAD:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 14;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 200;
			m_tFrame.dwFrameSpeed = 70; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_AIMING:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 1;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 250;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}

}
