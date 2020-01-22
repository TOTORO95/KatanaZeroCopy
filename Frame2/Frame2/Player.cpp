#include "stdafx.h"
#include "Player.h"

#include "AfterImage.h"

CPlayer::CPlayer()
	: m_bIsJump(false),m_bDJump(false)
{
	m_fJumpForce=0.f;
	m_fJumpAcc=0.f;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	m_ePreState=STATE_END;
	m_eCurState=STATE_END;

}

CPlayer::CPlayer(float fX, float fY)
	: m_bIsJump(false), m_bDJump(false)
{
	m_fJumpForce = 0.f;
	m_fJumpAcc = 0.f;
	ZeroMemory(&m_tFrame, sizeof(FRAME));
	m_ePreState = STATE_END;
	m_eCurState = STATE_END;
	SetPos(fX, fY);
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	m_eObjType = PLAYER;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_fAtkRange = 106.0;
	m_fSpeed = 5.f;
	m_fAngle = 90.f;	// Degree	
	m_iCount = 0;
	m_fJumpForce = 25.0f;
	m_fAtkPower = 20;
	m_flatY = m_tInfo.fY;
	m_bDown = false;

	m_eCurState = STATE_IDLE;
	m_ePreState = m_eCurState;
	m_bIsDead = false;
	m_tFrame.dwFrameStart = 0;
	m_tFrame.dwFrameCount = 4;
	m_tFrame.dwFrameX = 0;
	m_tFrame.dwFrameY = 0;
	m_tFrame.dwFrameSpeed = 200; // 0.2초 간격
	m_tFrame.dwOldTime = GetTickCount();
	m_bDJump = false;
	m_bIsAttk = false;
	m_WallJump = false;
	m_wstrImageKey = L"Player_R";
	
	m_wstrImageKey2 = L"Slash";
	m_tAtkFrame.dwFrameCount = 5;
	m_tAtkFrame.dwFrameStart = 0;
	m_tAtkFrame.dwFrameX = 106;
	m_tAtkFrame.dwFrameY = 0;
	m_tAtkFrame.dwFrameSpeed = 50;
	m_tAtkFrame.dwOldTime = GetTickCount();
	CObjectManager::GetInstance()->AddObject(AFTERIMAGE, CObjFactory<CAfterImage>::CreateObject(m_WorldPos.x, m_WorldPos.y));
}

int CPlayer::Update()
{

	//cout << "g_Y" << g_fScrollY << endl;
	//cout << "Player Local X=" << m_tInfo.fX << "   y= " << m_tInfo.fY << endl;

	KeyInput();
	UpdateWorldPos2();
	Move();
	Jump();
	WallJump();
	if (GetIsAttk())
	{
		m_eCurState = STATE_ATTACK;
		m_iCount++;
		m_tInfo.fX += cosf(m_fRadian)*m_fAtkPower*0.5;
		m_tInfo.fY -= sinf(m_fRadian)*m_fAtkPower*0.5;
		m_bDJump = false;
		m_WallJump = false;
		if (m_iCount % 10==0)
		{
			m_iCount = 0;
			m_bIsAttk = false;
			m_eCurState = STATE_IDLE;
			
		}

		//cout << "각= " << m_fAngle << endl;
	}
	Attack();
	ScrollOffset();
	ChangeState();
	Animate();
	return NO_EVENT;
}

void CPlayer::Render(HDC hdc)
{
	CGameObject::UpdateRect2();
	
	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey);
	NULL_CHECK(hMemDC);
	//Source DC에 그려진 비트맵을 Dest DC로 복사하는 함수.이 때 지정한 색상을 제거할 수 있다.
	if (CKeyManager::GetInstance()->KeyPressing(KEY_O))
	{
		Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		Rectangle(hdc, m_tHitBox.left, m_tHitBox.top, m_tHitBox.right, m_tHitBox.bottom);
	}
	GdiTransparentBlt(hdc,m_tRect.left- m_tInfo.fCX*0.5,m_tRect.top- m_tInfo.fCY*0.5,(int)m_tInfo.fCX*2,
		(int)m_tInfo.fCY*2,	hMemDC,
		m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
		m_tFrame.dwFrameY,
		m_tInfo.fCX,m_tInfo.fCY,RGB(0, 0, 0));

		hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey2);
		GdiTransparentBlt(hdc,m_WorldPos.x-106,m_WorldPos.y - 106,212,212,hMemDC,m_tAtkFrame.dwFrameX*m_tAtkFrame.dwFrameStart,
			m_tAtkFrame.dwFrameY,106,106,RGB(0, 0, 0));

	MoveToEx(hdc, m_WorldPos.x, m_WorldPos.y, nullptr);
	if (m_bIsAttk)
	{
		LineTo(hdc, g_tMouseInfo.ptStart.x, g_tMouseInfo.ptStart.y);
	}

}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{
	if (CKeyManager::GetInstance()->KeyPressing(KEY_SHIFT))
	{
		g_fTime = 0.2;
	}
	else
	{
		g_fTime = 1;
	}
	if (CKeyManager::GetInstance()->KeyDown(KEY_SPACE))
	{
		m_bIsJump = true;
		if(m_bDJump)
			m_WallJump = true;
		
		if (!m_bIsAttk)
			m_eCurState = STATE_JUMP;

	}
	if (CKeyManager::GetInstance()->KeyUp(KEY_SPACE))
	{
		m_bIsJump = false;
	}
	else
		m_eCurState = STATE_IDLE;

	if (CKeyManager::GetInstance()->KeyPressing(KEY_A))
	{
		m_wstrImageKey = L"Player_L";
		if (!m_bDJump)
		{
			m_tInfo.fX -= m_fSpeed;
			if (!m_bIsJump)
				m_eCurState = STATE_RUN;
		}
		else
			m_eCurState = STATE_WALLGRIP;
	}
	else if (CKeyManager::GetInstance()->KeyUp(KEY_A)||CKeyManager::GetInstance()->KeyUp(KEY_D))
	{
		m_bDJump = false;
		m_WallJump = false;
	}
	if (CKeyManager::GetInstance()->KeyPressing(KEY_D))
	{
		m_wstrImageKey = L"Player_R";
		if (!m_bDJump)
		{
			m_tInfo.fX += m_fSpeed;
			if (!m_bIsJump)
				m_eCurState = STATE_RUN;
		}
		else
			m_eCurState = STATE_WALLGRIP;
	}

	if (CKeyManager::GetInstance()->KeyUp(KEY_A)|| CKeyManager::GetInstance()->KeyUp(KEY_D))
	{
		m_bDJump = false;
		m_WallJump = false;
	}

	else if (CKeyManager::GetInstance()->KeyPressing(KEY_W))
	{
		m_tInfo.fY -= m_fSpeed;
		m_eCurState = STATE_RUN;
	}
	if (CKeyManager::GetInstance()->KeyPressing(KEY_S))//다운
	{
		if (m_bOnFlat)
			Roll();
		else
			m_bDown=true;
		
	}
	if (CKeyManager::GetInstance()->KeyDown(KEY_LBUTTON))//공격
	{
		//cout << m_WorldPos.x << endl;
		if (m_WorldPos.x > g_tMouseInfo.ptStart.x)
			m_wstrImageKey = L"Player_L";
		if (m_WorldPos.x <= g_tMouseInfo.ptStart.x)
			m_wstrImageKey = L"Player_R";
		
		SetAngle(g_tMouseInfo.ptStart.x, g_tMouseInfo.ptStart.y);
		m_bIsAttk = true;
		g_tMouseInfo.bStart = true;

	}
	if (CKeyManager::GetInstance()->KeyUp(KEY_S))//
		m_bDown = false;

	if (CKeyManager::GetInstance()->KeyUp(KEY_LBUTTON))//
		g_tMouseInfo.bStart = false;
}


void CPlayer::Attack()
{


	float fratio = 0.125f;
	if (GetIsAttk())
	{
		if (m_fAngle >= -22.5 && m_fAngle < 22.5)
			m_tHitBox = { (LONG)(m_WorldPos.x),(LONG)(m_WorldPos.y - m_fAtkRange*fratio),(LONG)(m_WorldPos.x + m_fAtkRange), (LONG)(m_WorldPos.y + m_fAtkRange*fratio) };
		else if (m_fAngle >= 22.5 && m_fAngle < 67.5)
			m_tHitBox = { (LONG)(m_WorldPos.x),(LONG)(m_WorldPos.y - m_fAtkRange*0.75), (LONG)(m_WorldPos.x + m_fAtkRange*0.75), (LONG)(m_WorldPos.y) };
		else if (m_fAngle >= 67.5 && m_fAngle < 112.5)
			m_tHitBox = { (LONG)(m_WorldPos.x - m_fAtkRange*fratio),(LONG)(m_WorldPos.y - m_fAtkRange), (LONG)(m_WorldPos.x + m_fAtkRange*fratio),(LONG)(m_WorldPos.y) };
		else if (m_fAngle >= 112.5 && m_fAngle < 157.5)
			m_tHitBox = { (LONG)(m_WorldPos.x - m_fAtkRange*0.75), (LONG)(m_WorldPos.y - m_fAtkRange*0.75),(LONG)(m_WorldPos.x), (LONG)m_WorldPos.y };
		else if (m_fAngle >= 157.5 || m_fAngle < -157.5)
			m_tHitBox = { (LONG)(m_WorldPos.x - m_fAtkRange), (LONG)(m_WorldPos.y - m_fAtkRange*fratio), (LONG)(m_WorldPos.x), (LONG)(m_WorldPos.y + m_fAtkRange*fratio) };
		else if (m_fAngle <= -112.5 && m_fAngle > -157.5)
			m_tHitBox = { (LONG)(m_WorldPos.x - m_fAtkRange*0.75), (LONG)(m_tInfo.fY),(LONG)(m_WorldPos.x),(LONG)(m_tInfo.fY + m_fAtkRange*0.75) };
		else if (m_fAngle <= -67.5 && m_fAngle > -112.5)
			m_tHitBox = { (LONG)(m_WorldPos.x - m_fAtkRange*fratio), (LONG)(m_WorldPos.y), (LONG)(m_WorldPos.x + m_fAtkRange*fratio),(LONG)(m_WorldPos.y + m_fAtkRange) };
		else if (m_fAngle <= -22.5 && m_fAngle > -67.5)
			m_tHitBox = { (LONG)(m_WorldPos.x), (LONG)(m_WorldPos.y), (LONG)(m_WorldPos.x + m_fAtkRange*0.75), (LONG)(m_WorldPos.y + m_fAtkRange*0.75) };
	}
	else
	{
		m_tHitBox = { 0,0,0,0 };
	}

}

void CPlayer::Move()
{

	//cout << "점프" << m_fLeftVal << "    " << m_fRightVal << endl;
	if (!m_bDJump)
	{
		if (!m_bIsColl && !m_bIsJump)
		{
			if (m_fRightVal < 9)
			{
				m_fRightVal = m_fJumpForce*m_fJumpAcc*m_fJumpAcc*0.5;
				m_fJumpAcc += 0.15;

			}
			else
				m_fRightVal = 9;
			m_eCurState = STATE_FALL;
			m_tInfo.fY += m_fRightVal;

		}
		if (m_bIsColl)
		{
			m_fRightVal = 0;
			m_fJumpAcc = 0;
			m_fLeftVal = 0;
		}
	}
}

void CPlayer::Roll()
{
	m_eCurState = STATE_ROLL;
	if(m_wstrImageKey==L"Player_R")
		m_tInfo.fX += m_fSpeed*1.2;
	else if (m_wstrImageKey == L"Player_L")
		m_tInfo.fX -= m_fSpeed * 1.2;


}

void CPlayer::Jump()
{
	
	if (m_bIsJump)
	{
		if (!m_bDJump)
		{
			m_eCurState = STATE_JUMP;
			if (m_fLeftVal == 0)
				m_tInfo.fY -= 5;

			m_bIsColl = false;
			if (m_fLeftVal < 60)
			{
				m_fLeftVal = (m_fJumpForce)*m_fJumpAcc;
				if(m_fRightVal<65)
					m_fRightVal = m_fJumpForce*m_fJumpAcc*m_fJumpAcc*0.5;
				m_fJumpAcc += 0.15f;
				//cout << m_fRightVal << endl;
			}

			m_tInfo.fY -= m_fLeftVal- m_fRightVal;

		}
	}

}
void CPlayer::WallJump()
{
	
	if (m_WallJump)
	{
		m_eCurState = STATE_WALLJUMP;
		m_iCount++;
		if(m_iDirection==0)
		m_tInfo.fX += cosf(30 / 180 * PI)*m_fAtkPower*0.5;
		else
			m_tInfo.fX -= cosf(30 / 180 * PI)*m_fAtkPower*0.5;
		m_tInfo.fY -=6;
		
		if (m_iCount % 20 == 0)
		{
			m_iCount = 0;
			m_bDJump = false;
			m_WallJump = false;
			m_bIsJump = false;
			m_eCurState = STATE_FALL;
		}
	}

}
void CPlayer::ScrollOffset()
{
	//플레이어가 화면에서 일정 범위를 벗어났을 때 스크롤을 움직인다.
	if (WinCX *0.9 <= m_WorldPos.x)
	{
		g_fScrollX += m_fSpeed*2;
	}
	if (WinCX *0.1 >= m_WorldPos.x)
	{
		g_fScrollX -= m_fSpeed*2;
	}
	if (WinCY *0.75 <= m_WorldPos.y)
	{
		g_fScrollY += m_fSpeed * 2;
	}
	if (WinCY *0.2 >= m_WorldPos.y)
	{
		g_fScrollY -= m_fSpeed * 2;
	}
	if (CKeyManager::GetInstance()->KeyPressing(KEY_R))
	{
		g_fScrollX += sinf(GetTickCount()) * 5;
		g_fScrollY += sinf(GetTickCount()) * 5;

	}
	if (CKeyManager::GetInstance()->KeyUp(KEY_R))
	{
		g_fScrollY = 0;
	}
}


void CPlayer::Animate()
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

		if (m_tAtkFrame.dwOldTime + m_tAtkFrame.dwFrameSpeed / g_fTime <= dwCurTime)
		{
			++m_tAtkFrame.dwFrameStart;
			m_tAtkFrame.dwOldTime = dwCurTime;
		}


		if (m_tAtkFrame.dwFrameStart == m_tAtkFrame.dwFrameCount)
			m_tFrame.dwFrameStart = 0;
		if (m_eCurState == STATE_ROLL&&m_tFrame.dwFrameStart < 5)
			m_bRoll = true;
		else
			m_bRoll = false;


	}
	else
	{
		if (m_tFrame.dwFrameStart < m_tFrame.dwFrameCount - 1)
		{
			KnockBack();
			g_fScrollX += sinf(GetTickCount()) * 10;
			g_fScrollY += cosf(GetTickCount()) * 10;
		}
		else
		{
			g_fScrollY = 0;
			if (m_tFrame.dwOldTime + m_tFrame.dwFrameSpeed / g_fTime <= dwCurTime)
			{
				++m_tFrame.dwFrameStart;
				m_tFrame.dwOldTime = dwCurTime;
			}
		}
	}

	

}

void CPlayer::ChangeState()
{
	// FSM (Finite State Machine, 유한 상태 기계)
	// 오브젝트는 한번에 하나의 상태만 가질 수 있다.
	//cout << "State="<< m_eCurState<< endl;
	 
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case STATE_IDLE:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 11;
			m_tFrame.dwFrameX =50;
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
		case STATE_JUMP:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 4;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 200;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_FALL:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 4;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 250;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_ATTACK:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 7;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 150;
			m_tFrame.dwFrameSpeed = 50; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			AniDirection();

			break;
		case STATE_ROLL:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 7;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 100;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_WALLGRIP:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 1;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 500;
			m_tFrame.dwFrameSpeed = 100; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_WALLJUMP:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 11;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 400;
			m_tFrame.dwFrameSpeed = 50; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		case STATE_DEAD:
			m_tFrame.dwFrameStart = 0;
			m_tFrame.dwFrameCount = 6;
			m_tFrame.dwFrameX = 50;
			m_tFrame.dwFrameY = 450;
			m_tFrame.dwFrameSpeed = 50; // 0.2초 간격
			m_tFrame.dwOldTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void CPlayer::AniDirection()
{
	DWORD dwCurTime = GetTickCount();
	m_tAtkFrame.dwFrameCount = 5;
	m_tAtkFrame.dwFrameStart = 0;
	m_tAtkFrame.dwFrameX = 106;
	m_tAtkFrame.dwFrameSpeed = 50;
	m_tAtkFrame.dwOldTime = GetTickCount();
	//cout << m_fAngle << endl;
	if (m_fAngle >= 0)
		m_tAtkFrame.dwFrameY = 106*(int)((m_fAngle+7.5)/15);
	else if (m_fAngle < 0)
		m_tAtkFrame.dwFrameY = 106 * (int)(11-(-m_fAngle + 7.5) / 15)+1378;//106 10.5   -3      10.5  15  0 12

}

void CPlayer::BulletTime(HDC hdc)
{

	if (CKeyManager::GetInstance()->KeyPressing(KEY_SHIFT)&&m_fBulletGage-2>0)
	{
		if (m_iAlpha <= 150)
			m_iAlpha += 10;
		m_BlendFuntion.SourceConstantAlpha = m_iAlpha;
		AlphaBlend(hdc, 0, 0, WinCX, WinCY, CBmpManager::GetInstance()->GetMemDC(L"BulletTime"), 0, 0, 1280, 800, m_BlendFuntion);
		m_fBulletGage -= 2.f;
	}
	else
	{
		if (m_iAlpha>0)
			m_iAlpha -= 10;
		//cout << "bullettime" << endl;

		if (m_iAlpha < 0)
			m_iAlpha = 0;

		m_BlendFuntion.SourceConstantAlpha = m_iAlpha;
		if (m_iAlpha != 0)
			AlphaBlend(hdc, 0, 0, WinCX, WinCY, CBmpManager::GetInstance()->GetMemDC(L"BulletTime"), 0, 0, 1280, 800, m_BlendFuntion);
		
		if (m_fBulletGage < 100)
			m_fBulletGage += 1.0f;
		else if (m_fBulletGage > 100)
			m_fBulletGage = 100;
	}
}


void CPlayer::KnockBack()
{
	m_tInfo.fX -= cosf(m_fRadian) * 10;
	m_tInfo.fY += sinf(m_fRadian) * 15;
}

void CPlayer::BeAttack(POINT targetInfo)
{
	if (m_WorldPos.x < targetInfo.x)
		m_wstrImageKey = L"Player_R";
	else
		m_wstrImageKey = L"Player_L";

	SetAngle(targetInfo.x, targetInfo.y);
	m_eCurState = STATE_DEAD;
	//m_bIsDead = true;
}
