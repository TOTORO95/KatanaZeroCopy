#include "stdafx.h"
#include "Gunster.h"
#include "Bullet.h"

CGunster::CGunster()
{
}

CGunster::CGunster(float fPosX, float fPosY, int iAtkRate)
{
	m_eObjType = MONSTER;
	m_tFixPos = { (LONG)fPosX,(LONG)fPosY };
	SetPos(fPosX, fPosY);
	SetSize(50, 50);
	m_fSpeed = 2.5;
	m_eDirection = OBJ_IDLE;
	ZeroMemory(&m_tDetectRect, sizeof(m_tDetectRect));
	m_wstrImageKey = L"Right";

	m_eMonsterType = GUNSTER;
	m_bIsTargetSet = false;
	m_iAttackRate = iAtkRate;
	m_bIsBettackEnd = false;
}


CGunster::~CGunster()
{
}

void CGunster::Initialize()
{
	CBmpManager::GetInstance()->LoadBmp(L"RGunster", L"../Image/Monster/GunsterSheet.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LGunster", L"../Image/Monster/LGunsterSheet.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Gun", L"../Image/Monster/Gun36.bmp");//999x27

	m_wstrRImageKey = L"RGunster";
	m_wstrLImageKey = L"LGunster";

	m_iDetectRange = 400;
	m_fJumpAcc = 0;
	m_tFrame.dwFrameStart = 0;
	m_tFrame.dwFrameCount = 8;
	m_tFrame.dwFrameX = 50;
	m_tFrame.dwFrameY = 0;
	m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
	m_tFrame.dwOldTime = GetTickCount();
	m_HitRange = 350;


	m_iCount = 0;
	m_fCount = 0;
	m_fRadian = 0;
	m_bisStop = false;

}

int CGunster::Update()
{
	if (m_bIsDead)
	{
		//cout << m_fCount << endl;
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

void CGunster::Render(HDC hdc)
{
	if (m_bIsDead)
	{
		GdiTransparentBlt(hdc, m_tRect.left - m_tInfo.fCX*0.5, m_tRect.top - m_tInfo.fCY, m_tInfo.fCX * 2, m_tInfo.fCY * 2,
			CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
			m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
			m_tFrame.dwFrameY,
			50, 50, RGB(0, 0, 0));
		if (!m_bIsBettackEnd)
		{
			if (m_wstrImageKey == L"RGunster")
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
	GdiTransparentBlt(hdc, m_tRect.left - m_tInfo.fCX*0.5, m_tRect.top - m_tInfo.fCY, m_tInfo.fCX * 2, m_tInfo.fCY * 2,
		CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
		m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
		m_tFrame.dwFrameY,
		50, 50, RGB(0, 0, 0));
	if (m_eCurState == STATE_AIMING)
	{
		if (m_fAngle >= 0)
		{
			GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, 54, 54,
				CBmpManager::GetInstance()->GetMemDC(L"Gun"),
				27 * ((int)m_fAngle / 10), 0,
				27, 27, RGB(0, 0, 0));
		}
		else
		{
			GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, 54, 54,
				CBmpManager::GetInstance()->GetMemDC(L"Gun"),
				27 * (18 - ((int)-m_fAngle / 10)) + 486, 0,
				27, 27, RGB(0, 0, 0));
			//int)(11-(-m_fAngle + 7.5) / 15
		}

	}

	if (CKeyManager::GetInstance()->KeyPressing(KEY_O))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		Rectangle(hdc, m_tDetectRect.left, m_tDetectRect.top, m_tDetectRect.right, m_tDetectRect.bottom);
	}
}

void CGunster::Patroll()
{
	if (!m_bIsDead)
		m_fCount++;

	if (!m_bIsTargetSet)
	{
		if (sinf(m_fCount / 180 * PI) >= 0)
		{
			m_eDirection = OBJ_RIGHT;
			m_wstrImageKey = m_wstrRImageKey;
		}
		else
		{
			m_eDirection = OBJ_LEFT;
			m_wstrImageKey = m_wstrLImageKey;
		}
		m_eCurState = STATE_WALK;
		if (m_eDirection == OBJ_RIGHT)
			m_tInfo.fX += m_fSpeed *0.5;
		else
			m_tInfo.fX -= m_fSpeed *0.5;

	}
	else//적발견
	{
		float fx = fabsf(m_tTargetPos.x - m_WorldPos.x);
		if (fx > m_iDetectRange) //400
		{
			m_bIsTargetSet = false;
		}
		if (fx <= m_HitRange)// 500 
		{
			m_eCurState = STATE_AIMING;
			if (m_WorldPos.x <= m_tTargetPos.x)
			{
				m_eDirection = OBJ_RIGHT;
				m_wstrImageKey = m_wstrRImageKey;
			}
			else
			{
				m_eDirection = OBJ_LEFT;
				m_wstrImageKey = m_wstrLImageKey;
			}
			Attack();
		}
		else
		{
			m_eCurState = STATE_RUN;

			if (m_WorldPos.x <= m_tTargetPos.x)
			{
				m_eDirection = OBJ_RIGHT;
				m_wstrImageKey = m_wstrRImageKey;
				m_tInfo.fX += m_fSpeed*1.5;
			}
			else
			{
				m_eDirection = OBJ_LEFT;
				m_wstrImageKey = m_wstrLImageKey;
				m_tInfo.fX -= m_fSpeed*1.5;
			}
		}

	}

}

void CGunster::Release()
{
}

void CGunster::Attack()
{
	if (m_bIsTargetSet)
	{
		m_iCount++;
		if (m_iCount == m_iAttackRate-1)
			m_OldScroll = { (LONG)g_fScrollX,(LONG)g_fScrollY };
		if ((int)m_iCount == m_iAttackRate)
			CObjectManager::GetInstance()->AddObject(BULLET, CObjFactory<CBullet>::CreateObject(m_WorldPos.x + cos(m_fRadian) * 30+g_fScrollX, m_WorldPos.y - sinf(m_fRadian) * 30- g_fScrollY, m_fRadian));
			//CObjectManager::GetInstance()->AddObject(BULLET, CObjFactory<CBullet>::CreateObject(m_tInfo.fX + cos(m_fRadian) * 30, m_tInfo.fY - sinf(m_fRadian) * 30 - g_fScrollY, m_fRadian));

		if (m_iCount >= m_iAttackRate)
		{
			g_fScrollX += sinf(GetTickCount()) * 7.5;
			g_fScrollY += cosf(GetTickCount()) * 3.75;
			if (m_iCount >= m_iAttackRate+5)
			{
				g_fScrollX = m_OldScroll.x;
				g_fScrollY = m_OldScroll.y;

				m_iCount = 0;
				m_bIsTargetSet = false;

			}
		}

	}
}

void CGunster::ChangeState()
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


