#include "stdafx.h"
#include "Monster.h"
#include "Bullet.h"

CMonster::CMonster()
{
	CBmpManager::GetInstance()->LoadBmp(L"LImpact", L"../Image/Monster/LImpact2.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"RImpact", L"../Image/Monster/RImpact2.bmp");//TODO: bmp ����ȵ� ������ �ִϸ��̼� Ȯ�� !collisionrect katana�� �浹ó������
	m_tBeattackFrame.dwFrameCount = 5;
	m_tBeattackFrame.dwFrameSpeed = 100;
	m_tBeattackFrame.dwFrameStart = 0;
	m_tBeattackFrame.dwFrameX = 50;
	m_tBeattackFrame.dwFrameY = 0;
	m_tBeattackFrame.dwOldTime = GetTickCount();
	m_bIsBettackEnd = false;
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
		m_tFrame.dwFrameSpeed = 100; // 0.2�� ����
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
		m_tFrame.dwFrameSpeed = 100; // 0.2�� ����o
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
	//case GRUNT:
	//	if (m_bIsTargetSet)
	//	{
	//		m_iCount++;
	//		if (m_iCount % 49 == 0)
	//			m_OldScroll = { (LONG)g_fScrollX,(LONG)g_fScrollY };
	//		if (m_iCount >= 50)
	//		{
	//			g_fScrollX += sinf(GetTickCount()) * 5;
	//			g_fScrollY += cosf(GetTickCount()) * 2.5;
	//			if (m_iCount >= 52)
	//			{
	//				g_fScrollX = m_OldScroll.x;
	//				g_fScrollY = m_OldScroll.y;

	//				m_iCount = 0;
	//				m_bIsTargetSet = false;

	//			}
	//		}
	//	}
	//	break;
	//case GUNSTER:
	//	if (m_bIsTargetSet)
	//	{
	//		m_iCount++;
	//		if (m_iCount==49)aaaaa
	//			m_OldScroll = { (LONG)g_fScrollX,(LONG)g_fScrollY };


	//		if ((int)m_iCount == 50)
	//			CObjectManager::GetInstance()->AddObject(BULLET, CObjFactory<CBullet>::CreateObject(m_tInfo.fX + cos(m_fRadian) * 30, m_tInfo.fY - sinf(m_fRadian) * 30, m_fRadian));

	//		if (m_iCount >= 50)
	//		{
	//			g_fScrollX += sinf(GetTickCount()) * 5;
	//			g_fScrollY += cosf(GetTickCount()) * 2.5;
	//			if (m_iCount >= 55)
	//			{
	//				g_fScrollX = m_OldScroll.x;
	//				g_fScrollY = m_OldScroll.y;

	//				m_iCount = 0;
	//				m_bIsTargetSet = false;

	//			}
	//		}

	//	}
	//	break;
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
	if (!m_bIsDead)
	{
		if (m_WorldPos.x < targetInfo.x)
			m_wstrImageKey = m_wstrRImageKey;
		else
			m_wstrImageKey = m_wstrLImageKey;

		SetAngle(targetInfo.x, targetInfo.y);



		m_eCurState = STATE_DEAD;
		m_bIsDead = true;
		//m_bisStop = true;
		m_fCount = 0;
	}
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
void CMonster::Patroll()
{
	if(!m_bIsDead)
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
			m_tInfo.fX += m_fSpeed / 2;
		else
			m_tInfo.fX -= m_fSpeed / 2;

	}
	else//���߰�
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
	else//�׾�����
	{
		if (m_tFrame.dwFrameStart < m_tFrame.dwFrameCount - 1 && !m_bisStop)
		{
			if (m_fCount == 0)
			{
				m_OldScroll = { (LONG)g_fScrollX,(LONG)g_fScrollY };
				g_fTime = 0.5;
			}m_fCount++;
			if (m_fCount==4)
				g_fTime = 1;
			//cout<<m_fCount<<endl;
			if (m_fCount >= 1 && m_fCount<6)
			{
				g_fScrollX += sinf(GetTickCount()) * 4;
				g_fScrollY += cosf(GetTickCount()) * 4;
				KnockBack();
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
					m_bisStop = true;
			
			}
			//����Ʈ
			if (m_tBeattackFrame.dwOldTime + m_tBeattackFrame.dwFrameSpeed / g_fTime <= dwCurTime)
			{
				++m_tBeattackFrame.dwFrameStart;
				m_tBeattackFrame.dwOldTime = dwCurTime;
			}

			if (m_tBeattackFrame.dwFrameStart == m_tBeattackFrame.dwFrameCount&&!m_bIsBettackEnd)
			{
				cout << "11" << endl;
				m_tBeattackFrame.dwFrameStart = 0;
				m_bIsBettackEnd = true;
			}
		}

	}
}

void CMonster::ChangeState()
{
	
	
}


void CMonster::SetTarget(POINT targetInfo,bool isTarget)
{
	m_tTargetPos = targetInfo;

	SetAngle(targetInfo.x, targetInfo.y);

	m_bIsTargetSet = isTarget;
}
