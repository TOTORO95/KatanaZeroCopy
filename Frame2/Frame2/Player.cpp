#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
	: m_bIsJump(false),
	m_fJumpForce(0.f),
	m_fJumpAcc(0.f),
	m_ePreState(STATE_END),
	m_eCurState(STATE_END)
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CPlayer::~CPlayer()
{
}
//TODO: 라인 따라서 움직이는거 ,아래로점프  구르기 구현해야함
void CPlayer::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_fAtkRange = 160.0f;
	m_fSpeed = 5.f;
	m_fAngle = 90.f;	// Degree	
	m_iCount = 0;
	m_fJumpForce = 15.0f;
	m_fAtkPower = 20;
	m_eCurState = STATE_IDLE;
	m_ePreState = m_eCurState;
	m_bIsDead = false;
	m_tFrame.dwFrameStart = 0;
	m_tFrame.dwFrameCount = 4;
	m_tFrame.dwFrameX = 0;
	m_tFrame.dwFrameY = 0;
	m_tFrame.dwFrameSpeed = 200; // 0.2초 간격
	m_tFrame.dwOldTime = GetTickCount();

	m_tAtkFrame.dwFrameCount = 5;
	m_tAtkFrame.dwFrameStart = 0;
	m_tAtkFrame.dwFrameX = 120;
	m_tAtkFrame.dwFrameY = 0;
	m_tAtkFrame.dwFrameSpeed = 50;
	m_tAtkFrame.dwOldTime = GetTickCount();

	m_bIsAttk = false;
	m_bIsFlat = false;
	m_wstrImageKey = L"Player_R";
	m_wstrImageKey2 = L"Slash";
	//m_wstrImageKey2 = L"RSlash";
}

int CPlayer::Update()
{
	KeyInput();
	Jump();
	if (GetIsAttk())
	{
		m_iCount++;
		Attack();
		//cout << m_iCount<<"X=힘" << sinf(m_fRadian)*m_fAtkPower << endl;
		m_tInfo.fX += cosf(m_fRadian)*m_fAtkPower*0.5;
		m_tInfo.fY -= sinf(m_fRadian)*m_fAtkPower;
			
		if (m_iCount % 10==0)
		{
			m_iCount = 0;
			m_bIsAttk = false;
			m_eCurState = STATE_IDLE;
			
		}

		
	}
	
	
	ChangeState();
	Animate();
	return NO_EVENT;
}

void CPlayer::Render(HDC hdc)
{

	CGameObject::UpdateRect();
	//Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey);
	NULL_CHECK(hMemDC);
	//Source DC에 그려진 비트맵을 Dest DC로 복사하는 함수.이 때 지정한 색상을 제거할 수 있다.

	GdiTransparentBlt(hdc,
		m_tRect.left- m_tInfo.fCX*0.5,
		m_tRect.top- m_tInfo.fCY*0.5,
		(int)m_tInfo.fCX*2,
		(int)m_tInfo.fCY*2,
		hMemDC,
		m_tFrame.dwFrameX*m_tFrame.dwFrameStart,
		m_tFrame.dwFrameY,
		m_tInfo.fCX,
		m_tInfo.fCY,
		RGB(0, 0, 0));
	if (m_bIsAttk&&m_wstrImageKey == L"Player_R")
	{
		hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey2);
		GdiTransparentBlt(hdc,
			m_tInfo.fX-123,
			m_tInfo.fY - 123,
			246,
			246,
			hMemDC,
			m_tAtkFrame.dwFrameX*m_tAtkFrame.dwFrameStart,
			m_tAtkFrame.dwFrameY,
			123,
			123,
			RGB(0, 0, 0));
	}if (m_bIsAttk&&m_wstrImageKey == L"Player_L")
	{
		hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey2);
		GdiTransparentBlt(hdc,
			m_tInfo.fX - 123,
			m_tInfo.fY - 123,
			246,
			246,
			hMemDC,
			m_tAtkFrame.dwFrameX*m_tAtkFrame.dwFrameStart,
			m_tAtkFrame.dwFrameY,
			123,
			123,
			RGB(0, 0, 0));
	}
	//render에서 각도 보고 돌려주는 애니메이션 값 으로 확인
	/*if (m_wstrImageKey2 == L"RSlash")
	{
		hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey2);
		GdiTransparentBlt(hdc,
			m_tRect.left + m_tInfo.fCX*0.5 - 200,
			m_tRect.top - m_tInfo.fCY*0.5,
			246,
			60,
			hMemDC,
			m_tAtkFrame.dwFrameX*m_tAtkFrame.dwFrameStart,
			m_tAtkFrame.dwFrameY,
			123,
			30,
			RGB(0, 0, 0));
	}	
	if (m_wstrImageKey2 == L"LSlash")
	{
		hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey2);
		GdiTransparentBlt(hdc,
			m_tRect.left + m_tInfo.fCX*0.5-200,
			m_tRect.top - m_tInfo.fCY*0.5,
			246,
			60,
			hMemDC,
			m_tAtkFrame.dwFrameX*m_tAtkFrame.dwFrameStart,
			m_tAtkFrame.dwFrameY,
			123,
			30,
			RGB(0, 0, 0));
	}*/

	MoveToEx(hdc, m_tInfo.fX - g_fScrollX, m_tInfo.fY, nullptr);
	if (m_bIsAttk)
	{
		LineTo(hdc, g_tMouseInfo.ptStart.x, g_tMouseInfo.ptStart.y);
		//Rectangle(hdc, m_tHitBox.left, m_tHitBox.top, m_tHitBox.right, m_tHitBox.bottom);

	}
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{

	if (CKeyManager::GetInstance()->KeyDown(KEY_SPACE))
	{
		m_bIsJump = true;
	}
	if (CKeyManager::GetInstance()->KeyUp(KEY_SPACE))
	{
		m_bIsJump = false;
		if (!m_bIsAttk)
			m_eCurState = STATE_FALL;
	}
	else
		m_eCurState = STATE_IDLE;

	if (CKeyManager::GetInstance()->KeyPressing(KEY_A))
	{
		m_tInfo.fX -= m_fSpeed;
		m_wstrImageKey = L"Player_L";
		if (!m_bIsJump)
			m_eCurState = STATE_RUN;
	}
	else if (CKeyManager::GetInstance()->KeyPressing(KEY_D))
	{
		m_tInfo.fX += m_fSpeed;
		m_wstrImageKey = L"Player_R";
		if (!m_bIsJump)
			m_eCurState = STATE_RUN;
	}
	else if (CKeyManager::GetInstance()->KeyPressing(KEY_W))
	{
		m_tInfo.fY -= m_fSpeed;
		m_eCurState = STATE_RUN;
	}
	else if (CKeyManager::GetInstance()->KeyPressing(KEY_S))
	{
		m_tInfo.fY += m_fSpeed;
		m_eCurState = STATE_RUN;
	}//g_tMouseInfo
	if (CKeyManager::GetInstance()->KeyDown(KEY_LBUTTON))//공격
	{
		//if(!g_tArea.bStart)
		if (m_tInfo.fX > g_tMouseInfo.ptStart.x)
			m_wstrImageKey = L"Player_L";
		if (m_tInfo.fX <= g_tMouseInfo.ptStart.x)
			m_wstrImageKey = L"Player_R";

		SetAngle(g_tMouseInfo.ptStart.x, g_tMouseInfo.ptStart.y);

		m_bIsAttk = true;
		g_tMouseInfo.bStart = true;

	}
	if (CKeyManager::GetInstance()->KeyUp(KEY_LBUTTON))//
	{
		g_tMouseInfo.bStart = false;

	}
}

void CPlayer::Jump()
{
	// 지형 충돌
	
	float fY = m_tInfo.fY; //fY <= 바닥 높이
	bool bIsColl = CLineManager::GetInstance()->CollisionLine(this, &fY);
	if (m_bIsJump)//상승
	{
		if (m_eCurState !=STATE_ATTACK)
		m_eCurState = STATE_JUMP;

		m_fLeftVal = m_fJumpForce * m_fJumpAcc;
		m_fRightVal = GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
		m_tInfo.fY -= m_fLeftVal - m_fRightVal;
		if (m_fRightVal >= 20)
			m_fRightVal = 20;
		m_fJumpAcc += 0.15f;

		if (m_tInfo.fY > fY)
		{
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
			m_fJumpAcc = 0;
		}

	}
	else//하강
	{
		//cout << "PosY= "<<m_tInfo.fPosY <<"바닥= " <<fY - m_tInfo.fCY*0.5f << endl;

		if (m_tInfo.fY >= (fY - m_tInfo.fCY*0.5f - 11))//바닥보다 아래에잇을때
		{
			m_tInfo.fY = fY - m_tInfo.fCY*0.5f;
			m_fJumpAcc = 0;
			m_bIsFlat = true;
			//cout << "착지" << endl;
		}
		else //위에 
		{
		if (m_eCurState!=STATE_ATTACK)
			m_eCurState = STATE_FALL;

			m_fRightVal = GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
			if (m_fRightVal >= 20)
				m_fRightVal = 20;
			//cout << "라벨"<<m_fRightVal << endl;
			m_fJumpAcc += 0.15f;
			m_tInfo.fY += m_fRightVal;

		}
	}
}

void CPlayer::Attack()
{
	//cout << m_fAngle << "도 " << endl;
	m_eCurState = STATE_ATTACK;

	float fratio = 0.25f;
	if (m_fAngle >= -22.5 && m_fAngle < 22.5)
		m_tHitBox = { (LONG)(m_tInfo.fX),(LONG)(m_tInfo.fY - m_fAtkRange*fratio),(LONG)(m_tInfo.fX + m_fAtkRange), (LONG)(m_tInfo.fY + m_fAtkRange*fratio) };
	else if (m_fAngle >= 22.5 && m_fAngle < 67.5)
		m_tHitBox = { (LONG)(m_tInfo.fX),(LONG)(m_tInfo.fY - m_fAtkRange), (LONG)(m_tInfo.fX + m_fAtkRange), (LONG)(m_tInfo.fY) };
	else if (m_fAngle >= 67.5 && m_fAngle < 112.5)
		m_tHitBox = { (LONG)(m_tInfo.fX - m_fAtkRange*fratio),(LONG)(m_tInfo.fY - m_fAtkRange), (LONG)(m_tInfo.fX + m_fAtkRange*fratio),(LONG)(m_tInfo.fY) };
	else if (m_fAngle >= 112.5 && m_fAngle < 157.5)
		m_tHitBox = { (LONG)(m_tInfo.fX - m_fAtkRange), (LONG)(m_tInfo.fY - m_fAtkRange),(LONG)(m_tInfo.fX), (LONG)m_tInfo.fY };
	else if (m_fAngle >= 157.5 || m_fAngle < -157.5)
		m_tHitBox = { (LONG)(m_tInfo.fX - m_fAtkRange), (LONG)(m_tInfo.fY - m_fAtkRange*fratio), (LONG)(m_tInfo.fX), (LONG)(m_tInfo.fY + m_fAtkRange*fratio) };
	else if (m_fAngle <= -112.5 && m_fAngle > -157.5)
		m_tHitBox = { (LONG)(m_tInfo.fX - m_fAtkRange), (LONG)(m_tInfo.fY),(LONG)(m_tInfo.fX),(LONG)(m_tInfo.fY + m_fAtkRange) };
	else if (m_fAngle <= -67.5 && m_fAngle > -112.5)
		m_tHitBox = { (LONG)(m_tInfo.fX - m_fAtkRange*fratio), (LONG)(m_tInfo.fY), (LONG)(m_tInfo.fX + m_fAtkRange*fratio),(LONG)(m_tInfo.fY + m_fAtkRange) };
	else if (m_fAngle <= -22.5 && m_fAngle > -67.5)
		m_tHitBox = { (LONG)(m_tInfo.fX), (LONG)(m_tInfo.fY), (LONG)(m_tInfo.fX + m_fAtkRange), (LONG)(m_tInfo.fY + m_fAtkRange) };

}

void CPlayer::ScrollOffset()
{
	// 플레이어가 화면에서 일정 범위를 벗어났을 때 스크롤을 움직인다.
	if (WinCX * 0.5f + 200.f <= m_tInfo.fX - g_fScrollX)
		g_fScrollX += m_fSpeed;
	if (WinCX * 0.5f - 200.f >= m_tInfo.fX - g_fScrollX)
		g_fScrollX -= m_fSpeed;

}

void CPlayer::Animate()
{
	DWORD dwCurTime = GetTickCount();

	if (m_tFrame.dwOldTime + m_tFrame.dwFrameSpeed <= dwCurTime)
	{
		++m_tFrame.dwFrameStart;
		m_tFrame.dwOldTime = dwCurTime;
	}

	if (m_tFrame.dwFrameStart == m_tFrame.dwFrameCount)
		m_tFrame.dwFrameStart = 0;
	
	if (m_tAtkFrame.dwOldTime + m_tAtkFrame.dwFrameSpeed <= dwCurTime)
	{
		++m_tAtkFrame.dwFrameStart;
		m_tAtkFrame.dwOldTime = dwCurTime;
	}

	if (m_tAtkFrame.dwFrameStart == m_tAtkFrame.dwFrameCount)
		m_tFrame.dwFrameStart = 0;

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
			m_tFrame.dwFrameY = 200;
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
		/*	m_tAtkFrame.dwFrameCount = 5;
			m_tAtkFrame.dwFrameStart = 0;
			m_tAtkFrame.dwFrameX = 123;
			m_tAtkFrame.dwFrameY = 0;
			m_tAtkFrame.dwFrameSpeed = 100;
			m_tAtkFrame.dwOldTime = GetTickCount();*/
			break;

		}

		m_ePreState = m_eCurState;
	}
}

void CPlayer::AniDirection()
{
	DWORD dwCurTime = GetTickCount();
	if (m_fAngle >= -12.5 && m_fAngle < 12.5)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 0;
		m_tAtkFrame.dwFrameSpeed = 50;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= 12.5 && m_fAngle < 35)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 123;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= 35 && m_fAngle < 57.5)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 246;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= 57.5 && m_fAngle < 80)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 369;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= 80 && m_fAngle < 102.5)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 492;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= 102.5 && m_fAngle < 125)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 615;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= 125 && m_fAngle < 147.5)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 738;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= 147.5 && m_fAngle < 170)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 861;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= 170 || m_fAngle < -170)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 984;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= -170 && m_fAngle < -157.5)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 1107;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= -157.5 && m_fAngle < -135)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 1230;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= -135 && m_fAngle < -112.5)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 1353;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= -112.5 && m_fAngle < -90)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 1476;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= -90 && m_fAngle < -77.5)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 1599;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= -77.5 && m_fAngle < -45)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 1722;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= -45 && m_fAngle < -22.5)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 1845;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
	else if (m_fAngle >= -22.5 && m_fAngle < 0)
	{
		m_tAtkFrame.dwFrameCount = 5;
		m_tAtkFrame.dwFrameStart = 0;
		m_tAtkFrame.dwFrameX = 123;
		m_tAtkFrame.dwFrameY = 1968;
		m_tAtkFrame.dwFrameSpeed = 100;
		m_tAtkFrame.dwOldTime = GetTickCount();
	}
}
