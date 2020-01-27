#include "stdafx.h"
#include "Monster2.h"
#include "Bullet.h"
#include "Blood.h"
CMonster2::CMonster2()
{
	CBmpManager::GetInstance()->LoadBmp(L"RFB", L"../Image/Monster/RFlatBlood.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LFB", L"../Image/Monster/LFlatBlood.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"BFB", L"../Image/Monster/FlatBlood90.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"URFB", L"../Image/Monster/FlatBlood45.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"ULFB", L"../Image/Monster/FlatBlood135.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LImpact", L"../Image/Monster/LImpact2.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"RImpact", L"../Image/Monster/RImpact2.bmp");
	m_tBeattackFrame.dwFrameCount = 5;
	m_tBeattackFrame.dwFrameSpeed = 100;
	m_tBeattackFrame.dwFrameStart = 0;
	m_tBeattackFrame.dwFrameX = 50;
	m_tBeattackFrame.dwFrameY = 0;
	m_tBeattackFrame.dwOldTime = GetTickCount();
	m_bIsBettackEnd = false;

	CBmpManager::GetInstance()->LoadBmp(L"Blood", L"../Image/Monster/Blood.bmp");
	m_tBloodFrame.dwFrameCount = 3;
	m_tBloodFrame.dwFrameSpeed = 100;
	m_tBloodFrame.dwFrameStart = 0;
	m_tBloodFrame.dwFrameX = 32;
	m_tBloodFrame.dwFrameY = 32;
	m_tBloodFrame.dwOldTime = GetTickCount();
}

CMonster2::CMonster2(MONSTER_TYPE eMonster_Type, float fposX, float fPosY)
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


CMonster2::~CMonster2()
{
}

void CMonster2::Initialize()
{

	LoadBmp();
	InitMonster();
	m_iCount = 0;
	m_fCount = 0;
	m_fRadian = 0;
	m_bisStop = false;
}

int CMonster2::Update()
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

void CMonster2::Render(HDC hdc)
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

void CMonster2::Release()
{
}

void CMonster2::LoadBmp()
{
	switch (m_eMonsterType)
	{
	case GRUNT:
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

void CMonster2::InitMonster()
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
		m_tFrame.dwFrameSpeed = 100; // 0.2초 간격o
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

void CMonster2::UpdateDetectRect()
{
	if (m_eMonsterType != HEADHUNTER)
	{
		if (m_eDirection == OBJ_LEFT)
		{
			m_tDetectRect = { (LONG)(m_WorldPos.x - m_iDetectRange),
				(LONG)(m_WorldPos.y - m_iDetectRange*0.5),
				(LONG)(m_WorldPos.x + (m_iDetectRange*0.5)),
				(LONG)m_tRect.bottom };
		}
		else if (m_eDirection == OBJ_RIGHT)
		{
			m_tDetectRect = { (LONG)(m_WorldPos.x - (m_iDetectRange*0.5)) ,
				(LONG)(m_WorldPos.y - m_iDetectRange*0.5),
				(LONG)(m_WorldPos.x + m_iDetectRange),
				(LONG)m_tRect.bottom };
		}
	}
	else
	{
		//cout << "headhunterrect" << endl;
		m_tDetectRect = { (LONG)(m_WorldPos.x - m_iDetectRange),
			(LONG)(m_WorldPos.y - m_iDetectRange*0.5),
			(LONG)(m_WorldPos.x + m_iDetectRange),
			(LONG)(m_tRect.bottom + m_iDetectRange*0.5) };
	}

}

void CMonster2::Move()
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

void CMonster2::Attack()
{

}

void CMonster2::BeAttack(POINT targetInfo)
{
	if (!m_bIsDead)
	{
		if (m_WorldPos.x < targetInfo.x)
			m_wstrImageKey = m_wstrRImageKey;
		else
			m_wstrImageKey = m_wstrLImageKey;

		SetAngle(targetInfo.x, targetInfo.y);
		m_fBloodAngle = m_fAngle;
		m_tOldPos = { (LONG)m_tInfo.fX, (LONG)m_tInfo.fY };
		m_eCurState = STATE_DEAD;
		m_bIsDead = true;
		//m_bisStop = true;
		m_fCount = 0;
		//cout <<" OldPos="<< m_tOldPos.x << endl;
	}
}
void CMonster2::KnockBack()
{
	m_tInfo.fX -= cosf(m_fRadian) * 30;
	m_tInfo.fY += sinf(m_fRadian) * 15;
}

void CMonster2::Pattern()
{

	switch (m_eMonsterType)
	{
	case GRUNT:
		Patroll();
		break;
	case GUNSTER:
		Patroll();
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
void CMonster2::Patroll()
{
	if (!m_bIsDead)
		m_fCount++;

	if (!m_bIsTargetSet)
	{
		if (m_tOldPos.x > WinCX*0.5)
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
		else
		{
			if (sinf(-m_fCount / 180 * PI) >= 0)
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
	}
	else//적발견
	{
		float fx = fabsf(m_tTargetPos.x - m_WorldPos.x);
		if (fx >= m_iDetectRange)
		{
			m_bIsTargetSet = false;
		}
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
}
void CMonster2::Animate()
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
		//피
		//if (m_tBloodFrame.dwOldTime + m_tBloodFrame.dwFrameSpeed / g_fTime <= dwCurTime)
		//{
		//	++m_tBloodFrame.dwFrameStart;
		//	m_tBloodFrame.dwOldTime = dwCurTime;
		//}

		//if (m_tBloodFrame.dwFrameStart == m_tBloodFrame.dwFrameCount)
		//	m_tBloodFrame.dwFrameStart = 0;
		//

		if (m_tFrame.dwFrameStart < m_tFrame.dwFrameCount - 1 && !m_bisStop)
		{
			if ((int)m_fCount % 2 == 0 && m_fCount<20)
			{
				CObjectManager::GetInstance()->AddObject(BLOOD,
					CObjFactory<CBlood>::CreateObject(m_WorldPos, m_fBloodAngle));

			}
			if (m_fCount == 0)
			{
				m_OldScroll = { (LONG)g_fScrollX,(LONG)g_fScrollY };
				g_fTime = 0.5;
			}m_fCount++;
			if (m_fCount == 4)
				g_fTime = 1;
			if (m_fCount < 6)
			{
				if ((int)m_fCount & 1)
				{
					g_fScrollX += sinf(GetTickCount()) * 15;
					g_fScrollY += cosf(GetTickCount()) * 15;
					KnockBack();
				}
				else
				{
					g_fScrollX = m_OldScroll.x;
					g_fScrollY = m_OldScroll.y;
				}

			}
			else if (m_fCount == 6)
			{
				g_fScrollX = m_OldScroll.x;
				g_fScrollY = m_OldScroll.y;
			}
			if (m_tFrame.dwOldTime + m_tFrame.dwFrameSpeed / g_fTime <= dwCurTime)
			{
				++m_tFrame.dwFrameStart;
				m_tFrame.dwOldTime = dwCurTime;
				if (m_tFrame.dwFrameStart == m_tFrame.dwFrameCount - 1)
				{
					m_bisStop = true;

				}
			}
			//이펙트
			if (m_tBeattackFrame.dwOldTime + m_tBeattackFrame.dwFrameSpeed / g_fTime <= dwCurTime)
			{
				++m_tBeattackFrame.dwFrameStart;
				m_tBeattackFrame.dwOldTime = dwCurTime;
			}

			if (m_tBeattackFrame.dwFrameStart == m_tBeattackFrame.dwFrameCount && !m_bIsBettackEnd)
			{
				m_tBeattackFrame.dwFrameStart = 0;
				m_bIsBettackEnd = true;
			}
		}

	}
}

void CMonster2::ChangeState()
{


}

//void CMonster2::BloodAni()
//{
//	if (m_fBloodAngle >-10)//0~10사이는 0  10~30은 1  30~50 2 
//		m_iBlood = ((int)m_fBloodAngle + 10) / 20;
//	else//-10~-30               -170~-150 10(-160)   -150~-130(-140) 11
//		m_iBlood = 9 + (9 + (m_fBloodAngle - 10) / 20);
//
//}


void CMonster2::SetTarget(POINT targetInfo, bool isTarget)
{
	m_tTargetPos = targetInfo;

	SetAngle(targetInfo.x, targetInfo.y);

	m_bIsTargetSet = isTarget;
}
