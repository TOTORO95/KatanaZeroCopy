#include "stdafx.h"
#include "Monster.h"
#include "Bullet.h"

CMonster::CMonster()
{
}

CMonster::CMonster(MONSTER_TYPE eMonster_Type,float fposX, float fPosY)
{
	m_eObjType = MONSTER;
	m_tFixPos = { (LONG)fposX,(LONG)fPosY };
	SetPos(fposX, fPosY);
	SetSize(50, 50);
	m_fSpeed = 2.5;
	m_eDirection = OBJ_IDLE;
	ZeroMemory(&m_tDetectRect, sizeof(m_tDetectRect));
	m_wstrImageKey = L"Right";

	m_eMonsterType = eMonster_Type;
	m_bIsTargetSet = false;

	
	
}


CMonster::~CMonster()
{
}

void CMonster::Initialize()
{
	LoadBmp();
	InitMonster();
	m_iCount = 0;
	m_fCount = 0;
	m_fRadian=0;
	m_bisStop = false;
}

int CMonster::Update()
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

void CMonster::Render(HDC hdc)
{
	switch (m_eMonsterType)
	{
	case GRUNT:
		if (m_bIsDead)
		{
			GdiTransparentBlt(hdc, m_tRect.left - m_tInfo.fCX*0.5, m_tRect.top - m_tInfo.fCY*0.5, m_tInfo.fCX * 2, m_tInfo.fCY * 2,
				CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
				m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
				m_tFrame.dwFrameY,
				50, 50, RGB(0, 0, 0));
			return;
		}
		GdiTransparentBlt(hdc, m_tRect.left - m_tInfo.fCX*0.5, m_tRect.top - m_tInfo.fCY*0.5, m_tInfo.fCX * 2, m_tInfo.fCY * 2,
			CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
			m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
			m_tFrame.dwFrameY,
			50, 50, RGB(0, 0, 0));


		break;
	case GUNSTER:
		if (m_bIsDead)
		{
			GdiTransparentBlt(hdc, m_tRect.left - m_tInfo.fCX*0.5, m_tRect.top - m_tInfo.fCY, m_tInfo.fCX * 2, m_tInfo.fCY * 2,
				CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
				m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
				m_tFrame.dwFrameY,
				50, 50, RGB(0, 0, 0));

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
		break;
	case POMP:
		break;
	case HEADHUNTER:
		break;
	case MONSTER_END:
		break;
	default:
		break;
	}
	
	
	if (CKeyManager::GetInstance()->KeyPressing(KEY_O))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		Rectangle(hdc, m_tDetectRect.left, m_tDetectRect.top, m_tDetectRect.right, m_tDetectRect.bottom);
	}
}

void CMonster::Release()
{
}

void CMonster::LoadBmp()
{
	switch (m_eMonsterType)
	{
	case GRUNT://TODO: 그런트 몹 추가!!!
		CBmpManager::GetInstance()->LoadBmp(L"RGrunt", L"../Image/Monster/RGrunt.bmp");//800x550
		CBmpManager::GetInstance()->LoadBmp(L"LGrunt", L"../Image/Monster/LGrunt.bmp");
		CBmpManager::GetInstance()->LoadBmp(L"LSlash", L"../Image/Monster/LGruntSlash.bmp");//256x64
		CBmpManager::GetInstance()->LoadBmp(L"RSlash", L"../Image/Monster/RGruntSlash.bmp");//256x64
		m_wstrRImageKey = L"RGrunt";
		m_wstrLImageKey = L"LGrunt";
		break;
	case GUNSTER://700x400
		CBmpManager::GetInstance()->LoadBmp(L"RGunster", L"../Image/Monster/GunsterSheet.bmp");
		CBmpManager::GetInstance()->LoadBmp(L"LGunster", L"../Image/Monster/LGunsterSheet.bmp");
		CBmpManager::GetInstance()->LoadBmp(L"Gun", L"../Image/Monster/Gun36.bmp");//999x27

		m_wstrRImageKey = L"RGunster";
		m_wstrLImageKey = L"LGunster";
		break;
	case POMP:
		CBmpManager::GetInstance()->LoadBmp(L"Pomp", L"../Image/Monster/PompSheet.bmp");
		break;
	case HEADHUNTER:
		break;
	case MONSTER_END:
		break;
	default:
		break;
	}
}

void CMonster::InitMonster()
{
	switch (m_eMonsterType)
	{
	case GRUNT:
		m_iDetectRange = 400;
		m_fJumpAcc = 0;
		m_tFrame.dwFrameStart = 0;
		m_tFrame.dwFrameCount = 8;
		m_tFrame.dwFrameX = 50;
		m_tFrame.dwFrameY = 0;
		m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
		m_tFrame.dwOldTime = GetTickCount();
		m_HitRange = 50;
		break;
	case GUNSTER:
		m_iDetectRange = 400;
		m_fJumpAcc = 0;
		m_tFrame.dwFrameStart = 0;
		m_tFrame.dwFrameCount = 8;
		m_tFrame.dwFrameX = 50;
		m_tFrame.dwFrameY = 0;
		m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
		m_tFrame.dwOldTime = GetTickCount();
		m_HitRange = 350;

		break;
	case POMP:
		break;
	case HEADHUNTER:
		break;
	case MONSTER_END:
		break;
	default:
		break;
	}
	
}

void CMonster::UpdateDetectRect()
{
	if (m_eDirection == OBJ_LEFT)
	{
		m_tDetectRect = { (LONG)(m_WorldPos.x - m_iDetectRange),
		(LONG)(m_WorldPos.y - m_iDetectRange*0.5),
		(LONG)(m_WorldPos.x+ (m_iDetectRange*0.5)),
		(LONG)m_tRect.bottom };
	}
	else if (m_eDirection == OBJ_RIGHT)
	{
		m_tDetectRect = { (LONG)(m_WorldPos.x- (m_iDetectRange*0.5)) ,
			(LONG)(m_WorldPos.y - m_iDetectRange*0.5),
			(LONG)(m_WorldPos.x + m_iDetectRange),
			(LONG)m_tRect.bottom };
	}

}

void CMonster::Move()
{
	if (!m_bIsColl)
	{
		if (m_fRightVal <= 8)
			m_fRightVal = 20 * m_fJumpAcc*m_fJumpAcc*0.5;
		m_fJumpAcc += 0.15;
		m_tInfo.fY += m_fRightVal;

	}
	if (m_bIsColl)
	{
		m_fRightVal = 0;
		m_fJumpAcc = 0;
		m_fLeftVal = 0;
	}

}

void CMonster::Attack()
{
	switch (m_eMonsterType)
	{
	case GRUNT:
		if (m_bIsTargetSet)
		{
			m_iCount++;
			if (m_iCount % 49 == 0)
				m_OldScroll = { (LONG)g_fScrollX,(LONG)g_fScrollY };
			if (m_iCount >= 50)
			{
				g_fScrollX += sinf(GetTickCount()) * 5;
				g_fScrollY += cosf(GetTickCount()) * 2.5;
				if (m_iCount >= 52)
				{
					g_fScrollX = m_OldScroll.x;
					g_fScrollY = m_OldScroll.y;

					m_iCount = 0;
					m_bIsTargetSet = false;

				}
			}
		}
		break;
	case GUNSTER:
		if (m_bIsTargetSet)
		{
			m_iCount++;
			if (m_iCount==49)
				m_OldScroll = { (LONG)g_fScrollX,(LONG)g_fScrollY };


			if ((int)m_iCount == 50)
				CObjectManager::GetInstance()->AddObject(BULLET, CObjFactory<CBullet>::CreateObject(m_tInfo.fX + cos(m_fRadian) * 30, m_tInfo.fY - sinf(m_fRadian) * 30, m_fRadian));

			if (m_iCount >= 50)
			{
				g_fScrollX += sinf(GetTickCount()) * 5;
				g_fScrollY += cosf(GetTickCount()) * 2.5;
				if (m_iCount >= 55)
				{
					g_fScrollX = m_OldScroll.x;
					g_fScrollY = m_OldScroll.y;

					m_iCount = 0;
					m_bIsTargetSet = false;

				}
			}

		}
		break;
	case POMP:
		break;
	case HEADHUNTER:
		break;
	case MONSTER_END:
		break;
	default:
		break;
	}

}

void CMonster::BeAttack(POINT targetInfo)
{
	if (m_WorldPos.x < targetInfo.x)
		m_wstrImageKey = m_wstrRImageKey;
	else
		m_wstrImageKey = m_wstrLImageKey;

	SetAngle(targetInfo.x, targetInfo.y);

	m_eCurState = STATE_DEAD;
	m_bIsDead = true;

}

void CMonster::KnockBack()
{
	m_tInfo.fX -= cosf(m_fRadian)*10;
	m_tInfo.fY += sinf(m_fRadian)*15;
}

void CMonster::Pattern()
{
	
	switch (m_eMonsterType)
	{
	case GRUNT:
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
				m_tInfo.fX += m_fSpeed / 2;
			else
				m_tInfo.fX -= m_fSpeed / 2;

		}
		else//적발견
		{
			float fx = fabsf(m_tTargetPos.x - m_WorldPos.x);
			if (fx <= m_HitRange)
			{
				m_eCurState = STATE_MELEE;
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
					m_tInfo.fX += m_fSpeed;
				}
				else
				{
					m_eDirection = OBJ_LEFT;
					m_wstrImageKey = m_wstrLImageKey;
					m_tInfo.fX -= m_fSpeed;
				}
			}

		}
		break;
	case GUNSTER:
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
				m_tInfo.fX += m_fSpeed / 2;
			else
				m_tInfo.fX -= m_fSpeed / 2;

		}
		else//적발견
		{
			float fx = fabsf(m_tTargetPos.x - m_WorldPos.x);
			if (fx <= m_HitRange)
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
					m_tInfo.fX += m_fSpeed;
				}
				else
				{
					m_eDirection = OBJ_LEFT;
					m_wstrImageKey = m_wstrLImageKey;
					m_tInfo.fX -= m_fSpeed;
				}
			}

		}
		break;
	case POMP:
		break;
	case HEADHUNTER:
		break;
	case MONSTER_END:
		break;
	default:
		break;
	}
	

}

void CMonster::Animate()
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

	}
	else//죽엇을때
	{
		if (m_tFrame.dwFrameStart < m_tFrame.dwFrameCount-1&&!m_bisStop)
		{
			if (m_fCount==0)
				m_OldScroll = { (LONG)g_fScrollX,(LONG)g_fScrollY };
			
			m_fCount++;
			//cout << "Time=" << g_fScrollX << "   " << g_fScrollY << endl;
			
			if (m_fCount>=2&& m_fCount<5)
			{
				g_fScrollX += sinf(GetTickCount()) * 6;
				g_fScrollY += cosf(GetTickCount()) * 6;
				KnockBack();
			}
			if (m_fCount>=5)
			{
				g_fScrollX = m_OldScroll.x;
				g_fScrollY = m_OldScroll.y;
			}
			if (m_tFrame.dwOldTime + m_tFrame.dwFrameSpeed / g_fTime <= dwCurTime)
			{
				++m_tFrame.dwFrameStart;
				m_tFrame.dwOldTime = dwCurTime;
				if(m_tFrame.dwFrameStart==m_tFrame.dwFrameCount-1)
					m_bisStop = true;
			}
		}
	}

}

void CMonster::ChangeState()
{
	switch (m_eMonsterType)
	{
	case GRUNT:
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
			case STATE_MELEE:
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
		break;
	case GUNSTER:
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
				m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
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
		break;
	case POMP:
		break;
	case HEADHUNTER:
		break;
	case MONSTER_END:
		break;
	default:
		break;
	}
	
}


void CMonster::SetTarget(POINT targetInfo,bool isTarget)
{
	m_tTargetPos = targetInfo;

	SetAngle(targetInfo.x, targetInfo.y);

	m_bIsTargetSet = isTarget;
}
