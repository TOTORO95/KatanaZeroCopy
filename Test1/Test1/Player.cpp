#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{
	SetPos(WinCX*0.5, WinCY*0.5);
	SetSize(35, 70);
	ZeroMemory(&m_tAimInfo, sizeof(INFO));
	SetObjType(PLAYER);
	m_fSpeed = 5.0f;
	m_fAtkRange = 70;
	m_fRadian = 0;
}

int CPlayer::Update()
{
	if (IsDead() == DEAD_OBJ)
		return DEAD_OBJ;

	KeyInput();
	UpdateRect();

	return ALLIVE_OBJ;
}
void CPlayer::KeyInput()
{
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_LEFT))
	{
		m_tInfo.fPosX -= m_fSpeed;
		//g_fScrollX -= m_fSpeed;

	}
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_RIGHT))
	{
		//g_fScrollX += m_fSpeed;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_SPACE))
	{
		m_bIsJump = true;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_LBUTTON))//공격
	{
		if(!g_tArea.bStart)
		SetAngle(g_tArea.ptStart.x, g_tArea.ptStart.y);
		cout << "cos    X=" << cosf(m_fRadian) << endl;
		cout << "sin    Y=" << sinf(m_fRadian) << endl;
		if(m_tInfo.fPosX>g_tArea.ptStart.x)
			m_tInfo.fPosX -= fabs(cosf(m_fRadian) * 30);
		else
			m_tInfo.fPosX += fabs(cosf(m_fRadian) * 30);

		if(m_tInfo.fPosY>g_tArea.ptStart.y)
			m_tInfo.fPosY -= fabs(sinf(m_fRadian) * 30);
		else
			m_tInfo.fPosY += fabs(sinf(m_fRadian) * 30);

		//m_tInfo.fPosX += cosf(m_fRadian)*10;
		//m_tInfo.fPosY -= sinf(m_fRadian)*10;
		//TODO: 공격방향에따른 이동방ㅇ향 결정!

		//Attack();
		g_tArea.bStart = true;
		
	}
	if (CKeyMgr::GetInstance()->KeyUp(KEY_LBUTTON))//
	{
		g_tArea.bStart = false;

	}
}

void CPlayer::Jump()
{
	// 지형 충돌
	float fY = m_tInfo.fPosY;
	//bool bIsColl = CLineMgr::GetInstance()->CollisionLine(this, &fY);

	if (m_bIsJump)
	{
		 //자유 낙하 공식
		 //y = 힘 * 가속도 * sin(90) - 중력(9.8) * 가속도^2 * 0.5
		float fLeftVal = m_fJumpForce * m_fJumpAcc;
		float fRightVal = GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;

		m_tInfo.fPosY -= fLeftVal - fRightVal;
		m_fJumpAcc += 0.3f;

		 //착지할 때
		//if (bIsColl && fLeftVal < fRightVal && m_tInfo.fY > fY - 50.f)
		if ( fLeftVal < fRightVal && m_tInfo.fPosY> fY - 50.f)
		{
			m_bIsJump = false;
			m_fJumpAcc = 0.f;
			m_tInfo.fPosY = fY - 50.f;
		}
	}
	//else if (bIsColl)
	//	m_tInfo.fY = fY - 50.f;
}

void CPlayer::Attack()
{
	if (m_fDegree >= -22.5 && m_fDegree < 22.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX - m_fAtkRange*0.5),(LONG)(m_tInfo.fPosY),(LONG)(m_tInfo.fPosX + m_fAtkRange*0.5), (LONG)(m_tInfo.fPosY + m_fAtkRange) };
	else if (m_fDegree >= 22.5 && m_fDegree < 67.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX),(LONG)(m_tInfo.fPosY), (LONG)(m_tInfo.fPosX + m_fAtkRange), (LONG)(m_tInfo.fPosY + m_fAtkRange) };
	else if (m_fDegree >= 67.5 && m_fDegree < 112.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX),(LONG)(m_tInfo.fPosY - m_fAtkRange*0.5), (LONG)(m_tInfo.fPosX + m_fAtkRange),(LONG)(m_tInfo.fPosY + m_fAtkRange*0.5f )};
	else if (m_fDegree >= 112.5 && m_fDegree < 157.5)
		m_tHitBox = { (LONG)m_tInfo.fPosX, (LONG)(m_tInfo.fPosY - m_fAtkRange),(LONG)(m_tInfo.fPosX + m_fAtkRange), (LONG)m_tInfo.fPosY };
	else if (m_fDegree >= 157.5	|| m_fDegree < -157.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX - m_fAtkRange*0.5), (LONG)(m_tInfo.fPosY-m_fAtkRange), (LONG)(m_tInfo.fPosX + m_fAtkRange*0.5), (LONG)m_tInfo.fPosY };
	else if (m_fDegree <= -112.5 && m_fDegree > -157.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX - m_fAtkRange), (LONG)(m_tInfo.fPosY - m_fAtkRange),(LONG)(m_tInfo.fPosX),(LONG)(m_tInfo.fPosY )};
	else if (m_fDegree <=-67.5 && m_fDegree > -112.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX - m_fAtkRange), (LONG)(m_tInfo.fPosY - m_fAtkRange*0.5), (LONG)(m_tInfo.fPosX),(LONG)(m_tInfo.fPosY+m_fAtkRange*0.5 )};
	else if (m_fDegree <= -22.5 && m_fDegree > -67.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX - m_fAtkRange), (LONG)(m_tInfo.fPosY), (LONG)(m_tInfo.fPosX), (LONG)(m_tInfo.fPosY + m_fAtkRange) };


		//else if (m_fDegree >= 135 && m_fDegree < 180)

}

void CPlayer::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(_hDC, m_tInfo.fPosX, m_tInfo.fPosY, nullptr);
	if (g_tArea.bStart)
	{
		LineTo(_hDC, g_tArea.ptStart.x, g_tArea.ptStart.y);
		Rectangle(_hDC, m_tHitBox.left, m_tHitBox.top, m_tHitBox.right, m_tHitBox.bottom);

		//hitbox 8방향 0~45 45~90 90~135 135~180
	}
}

void CPlayer::Release()
{
}

