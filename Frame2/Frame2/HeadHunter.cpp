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
	SetSize(22, 44);
	m_fSpeed = 5;
	m_eDirection = OBJ_IDLE;
	ZeroMemory(&m_tDetectRect, sizeof(m_tDetectRect));
	m_wstrImageKey = L"LHeadHunter";

	m_eMonsterType = HEADHUNTER;
	m_bIsTargetSet = false;
	m_iAttackRate = 100;
	m_bIsBettackEnd = false;
	m_tOldPos = { (LONG)fPosX,(LONG)fPosY };
	m_iHP = 3;
}


CHeadHunter::~CHeadHunter()
{
}

void CHeadHunter::Initialize()
{
	// 1번째문 2번째문 3번째문	4번째문 높이450
	// 210     480		820		1060
	m_tGPatternPos[0] = { 1060,450 };
	m_tGPatternPos[1] = { 210,450 };
	m_tGPatternPos[2] = { 480,450 };
	m_tGPatternPos[3] = { 820,450 };

	InitBMP();
	m_iDetectRange = 2000;
	m_fJumpAcc = 0;
	m_tFrame.dwFrameStart = 0;
	m_tFrame.dwFrameCount = 12;
	m_tFrame.dwFrameX = 22;
	m_tFrame.dwFrameY = 44;
	m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
	m_tFrame.dwOldTime = GetTickCount();
	m_HitRange = 1000;
	m_eCurState = STATE_IDLE;
	m_iAimNum = 0;
	m_iCount = 0;
	m_fCount = 0;
	//m_fRadian = 0;
	m_iPatternNum = 0;
	m_bisStop = false;
	m_bIsAimEnd = false;
	m_fAimRate = 0;
	m_bIsInvincibility = false;
	m_iRecoveryTime = 0;
	m_bIsHide = false;
	for (auto &count : m_fFrameCount)
		count = 0;
	m_fLaserRate = 1;
}

int CHeadHunter::Update()
{
	//cout << m_fAngle << endl;
	//cout << "방향(0왼쪽 1오른쪽) = "<<m_eDirection << endl;
	//cout << "State=" <<m_eCurState << endl;
	//cout << m_iRecoveryTime << endl;
	UpdateWorldPos2();
	UpdateRect2();
	UpdateDetectRect();
	if (!m_bIsInvincibility)
	{
		if (fabsf(m_fAngle) >= 90)
			m_eDirection = OBJ_RIGHT;
		else
			m_eDirection = OBJ_LEFT;
	}
	DirectionAni();
	Move();
	RecoveryIncible();


	Pattern();
	ChangeState();
	Animate();
	
	//cout <<"X="<< m_tTargetPos.x<< "Y="<<m_tTargetPos.y	 << endl;
	return NO_EVENT;
}

void CHeadHunter::Render(HDC hdc)
{
	//레이져
	//RightShot(hdc);

	//cout << "보스" <<m_WorldPos.x<<"y=" <<m_WorldPos.y<< endl;
	//if (m_eCurState != STATE_DEAD)
	//{
	//	GdiTransparentBlt(hdc, m_WorldPos.x - m_tFrame.dwFrameX*0.5, m_tRect.top - m_tFrame.dwFrameY*0.5, m_tFrame.dwFrameX*1.5, m_tFrame.dwFrameY*1.5,
	//		CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
	//		m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
	//		0,
	//		m_tFrame.dwFrameX, m_tFrame.dwFrameY, RGB(0, 0, 0));
	//}
	//else//죽엇을때
	//{
	//	GdiTransparentBlt(hdc, m_WorldPos.x - m_tFrame.dwFrameX*0.5, m_tRect.top + m_tFrame.dwFrameY*0.8, m_tFrame.dwFrameX*1.5, m_tFrame.dwFrameY*1.5,
	//		CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
	//		m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
	//		0,
	//		m_tFrame.dwFrameX, m_tFrame.dwFrameY, RGB(0, 0, 0));
	//}
	//AimLine(hdc);
	if (!m_bIsHide)
	{
		if (m_eCurState == STATE_AIMING)
		{
			AimAni(hdc);
		}
		else
		{
			GdiTransparentBlt(hdc, m_WorldPos.x - m_tFrame.dwFrameX*0.5, m_tRect.top - m_tFrame.dwFrameY*0.5, m_tFrame.dwFrameX*1.5, m_tFrame.dwFrameY*1.5,
				CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
				m_tFrame.dwFrameX*m_tFrame.dwFrameStart, 0,
				m_tFrame.dwFrameX, m_tFrame.dwFrameY, RGB(0, 0, 0));
		}
		if(m_bIsAimEnd)
			Laser(hdc, m_fAngle);


	}



	//if (m_bIsAimEnd == true)
	//{
	//	GdiTransparentBlt(hdc, m_WorldPos.x - m_tFrame.dwFrameX*0.5, m_tRect.top - m_tFrame.dwFrameY*0.5, m_tFrame.dwFrameX*1.5, m_tFrame.dwFrameY*1.5,
	//		CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
	//		m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
	//		0,
	//		m_tFrame.dwFrameX, m_tFrame.dwFrameY, RGB(0, 0, 0));
	//}
	//else
	//{
	//	//AimAni(hdc);
	//}
	if (CKeyManager::GetInstance()->KeyPressing(KEY_O))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		//Rectangle(hdc, m_tDetectRect.left, m_tDetectRect.top, m_tDetectRect.right, m_tDetectRect.bottom);
	}
}

void CHeadHunter::Patroll()
{
}

void CHeadHunter::BeAttack(POINT targetInfo)
{
	if (m_iHP>0 &&!m_bIsInvincibility)
	{
		m_iHP--;
		if (m_WorldPos.x < targetInfo.x)
			m_eDirection = OBJ_RIGHT;
		else
			m_eDirection = OBJ_LEFT;

		if (m_iHP != 0)
			m_eCurState = STATE_KNOCKBACK;
		else
			m_eCurState = STATE_DEAD;

		//cout <<"hp= "<<m_iHP << endl;
		SetAngle(targetInfo.x, targetInfo.y);
		m_fBloodAngle = m_fAngle;
		m_tOldPos = { (LONG)m_tInfo.fX, (LONG)m_tInfo.fY };
		//m_bIsDead = true;
		//m_bisStop = true;
		m_bIsInvincibility = true;
		m_fCount = 0;
	}
}

void CHeadHunter::DirectionAni()
{
	switch (m_eCurState)
	{
	case STATE_IDLE:
		if (m_eDirection == OBJ_RIGHT)
			m_wstrImageKey = L"LHeadIdle";
		else
			m_wstrImageKey = L"RHeadIdle";
		break;
	case STATE_ROLL:
		if (m_eDirection == OBJ_RIGHT)
			m_wstrImageKey = L"LHeadIdle";
		else
			m_wstrImageKey = L"RHeadIdle";
		break;
	case STATE_KNOCKBACK:
		if (m_eDirection == OBJ_RIGHT)
			m_wstrImageKey = L"RKnockback";
		else
			m_wstrImageKey = L"LKnockback";
		break;
	case STATE_AIMING:
		if (m_eDirection == OBJ_RIGHT)
			m_wstrImageKey = L"LHeadAim";
		else
			m_wstrImageKey = L"RHeadAim";
		break;
	case STATE_DEAD:
			m_wstrImageKey = L"Dead";
		break;
	case STATE_LASER_SHOT:
		if (m_eDirection == OBJ_RIGHT)
			m_wstrImageKey = L"LPutbackLaserGun";
		else
			m_wstrImageKey = L"RPutbackLaserGun";
		break;
	case STATE_TELEPORT_VERTICAL_LASER:
			m_wstrImageKey = L"RHeadIdle";
		break;
	case STATE_TELEPORT_HORIZON_LASER:
		if (m_eDirection == OBJ_RIGHT)
			m_wstrImageKey = L"RGTeleportLaser";
		else
			m_wstrImageKey = L"LGTeleportLaser";
		break;
	case STATE_TELEPORT_SWIP_LASER:
		if (m_eDirection == OBJ_RIGHT)
			m_wstrImageKey = L"LTLaserSwip";
		else
			m_wstrImageKey = L"RTLaserSwip";
		break;
	case STATE_DASH_READY:
		if (m_eDirection == OBJ_RIGHT)
			m_wstrImageKey = L"LDashAttackReady";
		else
			m_wstrImageKey = L"RDashAttackReady";
		break;
	case STATE_DASH_ATTACK:
		if (m_eDirection == OBJ_RIGHT)
			m_wstrImageKey = L"LDashAttack";
		else
			m_wstrImageKey = L"RDashAttack";
		break;
	case STATE_PUTBACK_LASERGUN:
		if (m_eDirection == OBJ_RIGHT)
			m_wstrImageKey = L"LPutbackLaserGun";
		else
			m_wstrImageKey = L"RPutbackLaserGun";
		break;
	case STATE_TAKEOUT_LASERGUN:
		if (m_eDirection == OBJ_RIGHT)
			m_wstrImageKey = L"LTakeOutLaserGun";
		else
			m_wstrImageKey = L"RTakeOutLaserGun";
		break;
	case STATE_DASH_END:
		if (m_eDirection == OBJ_RIGHT)
			m_wstrImageKey = L"LTakeOutLaserGun";
		else
			m_wstrImageKey = L"RTakeOutLaserGun";
		break;
	default:
		break;
	}
	
}

void CHeadHunter::Release()
{
}


void CHeadHunter::Pattern()
{// 1번째문 2번째문 3번째문	4번째문 높이450
	// 210     480		820		1060
	if (m_eCurState == STATE_IDLE)
	{
		m_iPatternNum++;
		if (m_iPatternNum >= 50)
		{
			m_eCurState = STATE_TAKEOUT_LASERGUN;
		}
	}

	TakeOutGun();
	if (m_bIsHide)
	{
		int i = fabsl(sinf(GetTickCount())*1.5);
		SetPos((float)m_tGPatternPos[i].x, (float)m_tGPatternPos[i].y);
		m_bIsHide = false;
		m_bIsInvincibility = false;
		m_eCurState = STATE_IDLE;
	}
	//	break;
	//	case STATE_LASER_SHOT:
	//		m_eCurState = STATE_LASER_SHOT;
	//	default:
	//		break;
	//	}
	//}
}

void CHeadHunter::RightShot(HDC hdc)
{
	AimLine(hdc);
	Laser(hdc, m_fAngle);

}

void CHeadHunter::Animate()
{
	DWORD dwCurTime = GetTickCount();
	if (m_eCurState != STATE_DEAD)
	{
		if (m_eCurState)
		{
			if (m_tFrame.dwOldTime + m_tFrame.dwFrameSpeed / g_fTime <= dwCurTime)
			{
				++m_tFrame.dwFrameStart;
				m_tFrame.dwOldTime = dwCurTime;
			}

			if (m_tFrame.dwFrameStart == m_tFrame.dwFrameCount)
				m_tFrame.dwFrameStart = 0;
		}


		if (m_tHorizonLaserFrame.dwOldTime + m_tHorizonLaserFrame.dwFrameSpeed / g_fTime <= dwCurTime)
		{
			++m_tHorizonLaserFrame.dwFrameStart;
			m_tHorizonLaserFrame.dwOldTime = dwCurTime;
		}

		if (m_tHorizonLaserFrame.dwFrameStart == m_tHorizonLaserFrame.dwFrameCount)
		{
			m_tHorizonLaserFrame.dwFrameStart = 0;
			m_bIsAimEnd = false;

		}
	}
	else
	{
		if (m_bIsAimEnd)//TODO: 요기수정중 현제 레이저쏜후에  <- 이곳에 AimEnd 값 넣어주기 
		{
			if (m_tFrame.dwOldTime + m_tFrame.dwFrameSpeed / g_fTime <= dwCurTime)
			{
				++m_tFrame.dwFrameStart;
				m_tFrame.dwOldTime = dwCurTime;
			}

			if (m_tFrame.dwFrameStart == m_tFrame.dwFrameCount)
				m_tFrame.dwFrameStart = 0; // < - 요기 건들이기

		}

	}

}

void CHeadHunter::TakeOutGun()
{
	if (m_eCurState == STATE_TAKEOUT_LASERGUN)
	{
		if (m_tFrame.dwFrameStart >= m_tFrame.dwFrameCount - 2)
		{
			m_eCurState = STATE_AIMING;
			m_iPatternNum = 0;

		}
	}
}

void CHeadHunter::Laser(HDC hdc,float fDgree)
{
	if (m_bIsAimEnd)
	{
		//cout << m_tHorizonLaserFrame.dwFrameStart << endl;
		RotateSizingImage(hdc, m_hBitLaser[m_tHorizonLaserFrame.dwFrameStart], 180 - fDgree, 1280, 7.5, m_WorldPos.x - 20, m_WorldPos.y - 20,
			m_fLaserRate - m_tHorizonLaserFrame.dwFrameStart*0.05);
		cout << m_tHorizonLaserFrame.dwFrameStart << endl;
		if (m_tHorizonLaserFrame.dwFrameStart == m_tHorizonLaserFrame.dwFrameCount - 1)
		{
			m_bIsAimEnd = false;
			m_eCurState = STATE_IDLE;
		}
	}
	

}

void CHeadHunter::AimLine(HDC hdc)
{
		HPEN pen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
		HPEN open = (HPEN)SelectObject(hdc, pen);
		MoveToEx(hdc,m_WorldPos.x + cosf(m_fRadian)*15+10, m_WorldPos.y- sinf(m_fRadian)*15 -11, NULL);
		LineTo(hdc, m_WorldPos.x+cosf(m_fRadian)*1280, m_WorldPos.y-sinf(m_fRadian) * 1280);
		SelectObject(hdc, open);
		DeleteObject(pen);

}

void CHeadHunter::InitBMP()
{
	//Idle
	CBmpManager::GetInstance()->LoadBmp(L"RHeadIdle", L"../Image/HeadHunter/Idle/RIdle.bmp");//264x44
	CBmpManager::GetInstance()->LoadBmp(L"LHeadIdle", L"../Image/HeadHunter/Idle/LIdle.bmp");
	//Aim
	CBmpManager::GetInstance()->LoadBmp(L"RHeadAim", L"../Image/HeadHunter/Laser/GLaserAim/RGLaserAim.bmp");//741x52
	CBmpManager::GetInstance()->LoadBmp(L"LHeadAim", L"../Image/HeadHunter/Laser/GLaserAim/LGLaserAim.bmp");
	//Teleport Vertical Laser
	CBmpManager::GetInstance()->LoadBmp(L"RHeadAim", L"../Image/HeadHunter/Laser/TLaserShot/TLaser.bmp");//224x45
	//Teleport HorizonLaser
	CBmpManager::GetInstance()->LoadBmp(L"RGTeleportLaser", L"../Image/HeadHunter/Laser/RGTeleportLaser.bmp");//1280x300
	CBmpManager::GetInstance()->LoadBmp(L"LGTeleportLaser", L"../Image/HeadHunter/Laser/LGTeleportLaser.bmp");//1280x300
	//Teleport Swip
	CBmpManager::GetInstance()->LoadBmp(L"RTLaserSwip", L"../Image/HeadHunter/Laser/TLaserSwip/RTLaserSwipFull.bmp");//1475x46
	CBmpManager::GetInstance()->LoadBmp(L"LTLaserSwip", L"../Image/HeadHunter/Laser/TLaserSwip/LTLaserSwipFull.bmp");//1475x46
	//LaserShot
	CBmpManager::GetInstance()->LoadBmp(L"LeftLaserShot", L"../Image/HeadHunter/Laser/LeftLaserShot.bmp");//304x43
	CBmpManager::GetInstance()->LoadBmp(L"RightLaserShot", L"../Image/HeadHunter/Laser/RightLaserShot.bmp");//304x43

	//Ready LaserGun 
	CBmpManager::GetInstance()->LoadBmp(L"RTakeOutLaserGun", L"../Image/HeadHunter/Laser/RTakeOutLaserGun.bmp");//304x43
	CBmpManager::GetInstance()->LoadBmp(L"LTakeOutLaserGun", L"../Image/HeadHunter/Laser/LTakeOutLaserGun.bmp");//304x43
	//Putback LaserGun
	CBmpManager::GetInstance()->LoadBmp(L"RPutbackLaserGun", L"../Image/HeadHunter/Laser/RPutbackLaserGun.bmp");//304x43
	CBmpManager::GetInstance()->LoadBmp(L"LPutbackLaserGun", L"../Image/HeadHunter/Laser/LPutbackLaserGun.bmp");//304x43
	//Laser
	CBmpManager::GetInstance()->LoadBmp(L"HorizonLaser", L"../Image/HeadHunter/HorizonLaser.bmp");//1280x300
	CBmpManager::GetInstance()->LoadBmp(L"VerticalLaser", L"../Image/HeadHunter/VerticalLaser.bmp");//300x1280
	//KnockBack
	CBmpManager::GetInstance()->LoadBmp(L"RKnockback", L"../Image/HeadHunter/Knockback/RKnockbackfull.bmp");//980x53
	CBmpManager::GetInstance()->LoadBmp(L"LKnockback", L"../Image/HeadHunter/Knockback/LKnockbackfull.bmp");//980x53
	//DashAttackReady
	CBmpManager::GetInstance()->LoadBmp(L"RDashAttackReady", L"../Image/HeadHunter/DashAttack/RDashAttackReady.bmp");//456x43
	CBmpManager::GetInstance()->LoadBmp(L"LDashAttackReady", L"../Image/HeadHunter/DashAttack/LDashAttackReady.bmp");//456x43
	//DashAttack
	CBmpManager::GetInstance()->LoadBmp(L"RDashAttackSlow", L"../Image/HeadHunter/DashAttack/RDashAttackSlow.bmp");//42x29
	CBmpManager::GetInstance()->LoadBmp(L"LDashAttackSlow", L"../Image/HeadHunter/DashAttack/LDashAttackSlow.bmp");//42x29
	CBmpManager::GetInstance()->LoadBmp(L"RDashAttack", L"../Image/HeadHunter/DashAttack/RDashAttack.bmp");//51x25
	CBmpManager::GetInstance()->LoadBmp(L"LDashAttack", L"../Image/HeadHunter/DashAttack/LDashAttack.bmp");//51x25

	//DashAttackEnd
	CBmpManager::GetInstance()->LoadBmp(L"RDashAttackEnd", L"../Image/HeadHunter/DashAttack/RDashAttackEnd.bmp");//500x47
	CBmpManager::GetInstance()->LoadBmp(L"LDashAttackEnd", L"../Image/HeadHunter/DashAttack/LDashAttackEnd.bmp");//500x47
	//PutBackLaserGun
	CBmpManager::GetInstance()->LoadBmp(L"LPutbackLaserGun", L"../Image/HeadHunter/DashAttack/LPutbackLaserGun.bmp");//500x47
	CBmpManager::GetInstance()->LoadBmp(L"RPutbackLaserGun", L"../Image/HeadHunter/DashAttack/RPutbackLaserGun.bmp");//500x47
	//TakeOutLaserGun
	CBmpManager::GetInstance()->LoadBmp(L"LTakeOutLaserGun", L"../Image/HeadHunter/DashAttack/LTakeOutLaserGun.bmp");//500x47
	CBmpManager::GetInstance()->LoadBmp(L"RTakeOutLaserGun", L"../Image/HeadHunter/DashAttack/RTakeOutLaserGun.bmp");//500x47


	//DEAD																										 //DEAD
	CBmpManager::GetInstance()->LoadBmp(L"Dead", L"../Image/HeadHunter/Dead/Dead.bmp");//1064x21
	CBmpManager::GetInstance()->LoadBmp(L"Dead_Nohead", L"../Image/HeadHunter/Dead/Dead_Nohead.bmp");//360x22
	CBmpManager::GetInstance()->LoadBmp(L"head_hurtground", L"../Image/HeadHunter/Dead/head_hurtground.bmp");//360x14
	LoadBmp(m_hBitLaser[0], L"../Image/HeadHunter/Laser/Beam/Beam1.bmp");
	LoadBmp(m_hBitLaser[1], L"../Image/HeadHunter/Laser/Beam/Beam2.bmp");
	LoadBmp(m_hBitLaser[2], L"../Image/HeadHunter/Laser/Beam/Beam3.bmp");
	LoadBmp(m_hBitLaser[3], L"../Image/HeadHunter/Laser/Beam/Beam4.bmp");
	LoadBmp(m_hBitLaser[4], L"../Image/HeadHunter/Laser/Beam/Beam5.bmp");
	LoadBmp(m_hBitLaser[5], L"../Image/HeadHunter/Laser/Beam/Beam6.bmp");
	LoadBmp(m_hBitLaser[6], L"../Image/HeadHunter/Laser/Beam/Beam1.bmp");

	m_tHorizonLaserFrame.dwFrameCount = 7;
	m_tHorizonLaserFrame.dwFrameSpeed = 100;
	m_tHorizonLaserFrame.dwFrameStart = 0;
	m_tHorizonLaserFrame.dwFrameX = 1280;
	m_tHorizonLaserFrame.dwFrameY = 30;
	m_tHorizonLaserFrame.dwOldTime = GetTickCount();
	 

}



void CHeadHunter::KnockBack()
{
}

void CHeadHunter::ChangeState()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE_IDLE://264x44
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 12;
			m_tFrame.dwFrameX = 22;
			m_tFrame.dwFrameY = 44;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_KNOCKBACK:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 14;
			m_tFrame.dwFrameX = 70;
			m_tFrame.dwFrameY = 53;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_TELEPORT_HORIZON_LASER:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 8;
			m_tFrame.dwFrameX = 41;
			m_tFrame.dwFrameY = 35;
			m_tFrame.dwFrameSpeed = 200; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_TELEPORT_VERTICAL_LASER:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 4;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 150;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_AIMING://추가함
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 19;
			m_tFrame.dwFrameX = 39;
			m_tFrame.dwFrameY = 52;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_LASER_SHOT://1064
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 8;
			m_tFrame.dwFrameX = 38;
			m_tFrame.dwFrameY = 43;
			m_tFrame.dwFrameSpeed = 140; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_DEAD://1064
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 19;
			m_tFrame.dwFrameX = 56;
			m_tFrame.dwFrameY = 21;
			m_tFrame.dwFrameSpeed = 140; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_TAKEOUT_LASERGUN://1064
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 8;
			m_tFrame.dwFrameX =38;
			m_tFrame.dwFrameY = 43;
			m_tFrame.dwFrameSpeed = 140; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;

		default:
			break;
		}
		m_ePreState = m_eCurState;
	}

}

void CHeadHunter::VerticalLaser()
{

}

void CHeadHunter::AimAni(HDC hdc)
{
	if (m_eCurState == STATE_AIMING)
	{
		m_fAimRate++;
		if (m_eDirection == OBJ_LEFT)
			m_wstrImageKey = L"RHeadAim";
		else
			m_wstrImageKey = L"LHeadAim";
		if (m_fAngle >= 90 && m_fAngle <= 180)
		{
			m_iAimNum = 9 + (20 - (m_fAngle + 5) / 9);
		}
		else if (m_fAngle < 90 && m_fAngle >= 0)
		{
			m_iAimNum = 9 + ((m_fAngle + 5) / 9);
		}
		AimLine(hdc);
		GdiTransparentBlt(hdc, m_WorldPos.x - m_tFrame.dwFrameX*0.5, m_tRect.top - m_tFrame.dwFrameY*0.5-5, m_tFrame.dwFrameX*1.5, m_tFrame.dwFrameY*1.5,
			CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey),
			39 * m_iAimNum, 0, 39, 52, RGB(0, 0, 0));
		if (m_fAimRate >= 60)
		{
			m_bIsAimEnd = true;
			m_fAimRate = 0;
			m_eCurState = STATE_LASER_SHOT;
		}

	}
	
}

void CHeadHunter::RecoveryIncible()
{
	if (m_bIsInvincibility&&!m_bIsHide)
	{
		if (m_tFrame.dwFrameStart >= m_tFrame.dwFrameCount - 1)
		{
			m_bIsHide = true;
		}
		//cout << m_tFrame.dwFrameStart << endl;
		if (m_tFrame.dwFrameStart<=7)
		{
			if (m_eDirection == OBJ_RIGHT)
				m_tInfo.fX -= 3;
			else
				m_tInfo.fX += 3;
		}

	}
}

bool CHeadHunter::LoadBmp(HBITMAP & hmp, const wstring & wstrFilePath)
{
	// 비트맵 읽어오기.
	hmp = (HBITMAP)LoadImage(nullptr, wstrFilePath.c_str(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hmp == nullptr)
		return false;

	return true;
}

BOOL CHeadHunter::RotateSizingImage(HDC hdc, HBITMAP hBmp, float fDgree, int ixRotateAxis, int iyRotateAxis, int ixDisplay, int iyDisplay, float dblSizeRatio, HBITMAP hMaskBmp, int ixMask, int iyMask)
{
	int i;
	BITMAP bm;
	GetObject(hBmp, sizeof(BITMAP), &bm);
	POINT apt[3] = { 0 };
	float fWidth = (double)bm.bmWidth*dblSizeRatio;
	float fHeight = (double)bm.bmHeight*dblSizeRatio;
	float ixRotate = (int)((float)ixRotateAxis*dblSizeRatio); // 크기가 변하는 것 고려
	float iyRotate = (int)((float)iyRotateAxis*dblSizeRatio);



	float fRadian, flx, fly, fxDest, fyDest, cosVal, sinVal;
	fRadian = fDgree*PI / 180.0f;
	cosVal = cos(fRadian), sinVal = sin(fRadian);

	// 1. 회전축을 기준으로 상대좌표를 구하고 
	// 2. 회전후 위치좌표(상대좌표)를 얻은 후
	// 3. 얻은 값을 원래의 좌표에 적용.
	for (i = 0; i < 3; i++) {
		if (i == 0) { flx = -ixRotate, fly = -iyRotate; }    // left up  꼭지점 부분
		else if (i == 1) { flx = fWidth - ixRotate, fly = -iyRotate; }  // right up 꼭지점 부분
		else if (i == 2) { flx = -ixRotate, fly = fHeight - iyRotate; } // left low 꼭지점 부분
		fxDest = flx*cosVal - fly*sinVal;
		fyDest = flx*sinVal + fly*cosVal;
		fxDest += ixRotate, fyDest += iyRotate;
		apt[i].x = ixDisplay - (long)ixRotate + (long)fxDest;
		apt[i].y = iyDisplay - (long)iyRotate + (long)fyDest;
	}

	HDC hMemdc;
	HBITMAP hOldBmp;
	hMemdc = CreateCompatibleDC(hdc);
	hOldBmp = (HBITMAP)SelectObject(hMemdc, hBmp);
	BOOL iRes = PlgBlt(hdc, apt, hMemdc, 0, 0, bm.bmWidth, bm.bmHeight, hMaskBmp, ixMask, iyMask);
	SelectObject(hMemdc, hOldBmp);
	DeleteDC(hMemdc);
	return iRes;
}
