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
	SetSize(50,50);
	ZeroMemory(&m_tAimInfo, sizeof(INFO));
	SetObjType(PLAYER);
	m_fSpeed = 5.0f;
	m_fAtkRange = 70;
	m_fRadian = 0;
	m_iCount = 0;
	m_iAnim = 0;
	m_fAtkPower = 60;
	m_bIsAttk = false;
	m_fJumpForce = 20.0f;
	m_bIsJump = false;
	m_fJumpAcc = 0;
	m_pImage = Image::FromFile(L"../Image/Player/Player6.bmp");
	m_LocInfo = m_tInfo;
}

int CPlayer::Update()
{
	m_iCount++;

	if (IsDead() == DEAD_OBJ)
		return DEAD_OBJ;
	
	KeyInput();
	
	Jump();
	ScrollOffset();
	if (GetIsAttk())
	{
		m_tInfo.fPosX += cosf(m_fRadian)*m_fAtkPower;
		m_tInfo.fPosY -= sinf(m_fRadian)*m_fAtkPower;
		if (m_iCount % 100)
		{
			m_bIsAttk = false;

		}
	}
	return ALLIVE_OBJ;
}
void CPlayer::Render(HDC _hDC)
{
	
	UpdateRect();

	HDC hMemDC = CBmpMgr::GetInstance()->GetMemDC(L"Player");
	NULL_CHECK(hMemDC);

	//Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	if (m_iCount % 13 == 0)
	{

		m_iAnim += 50;
		if (m_iAnim >= 550)
			m_iAnim = 0;
	}

	// Source DC에 그려진 비트맵을 Dest DC로 복사하는 함수. 이 때 지정한 색상을 제거할 수 있다.
	GdiTransparentBlt(_hDC, (m_tRect.left)- m_tInfo.fCX*0.5-g_fScrollX, m_tRect.top- m_tInfo.fCY * 0.5, (int)m_tInfo.fCX*2, (int)m_tInfo.fCY*2,
		hMemDC, m_iAnim, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY, RGB(0, 0, 0));


	MoveToEx(_hDC, m_tInfo.fPosX-g_fScrollX, m_tInfo.fPosY, nullptr);
	if (g_tArea.bStart)
	{
		LineTo(_hDC, g_tArea.ptStart.x, g_tArea.ptStart.y);
		Rectangle(_hDC, m_tHitBox.left, m_tHitBox.top, m_tHitBox.right, m_tHitBox.bottom);

	}
//TODO Render ,setAngle 확인
}
void CPlayer::KeyInput()
{
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_LEFT))
	{
		m_tInfo.fPosX -= m_fSpeed;
		//g_fScrollX -= m_fSpeed;
		m_LocInfo.fPosX -= m_fSpeed;

	}
	if (CKeyMgr::GetInstance()->KeyPressing(KEY_RIGHT))
	{
		m_tInfo.fPosX += m_fSpeed;

		m_LocInfo.fPosX += m_fSpeed;
		//g_fScrollX += m_fSpeed;
	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_SPACE))
	{
		m_bIsJump = true;
	}
	if (CKeyMgr::GetInstance()->KeyUp(KEY_SPACE))
	{
		m_bIsJump = false;

	}
	if (CKeyMgr::GetInstance()->KeyDown(KEY_LBUTTON))//공격
	{
		//if(!g_tArea.bStart)

			SetAngle(g_tArea.ptStart.x, g_tArea.ptStart.y);
	
		m_bIsAttk = true;
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
	float fY = m_tInfo.fPosY; //fY <= 바닥 높이
	bool bIsColl = CLineMgr::GetInstance()->CollisionLine(this, &fY);
	if (m_bIsJump)//상승
	{
		fLeftVal = m_fJumpForce * m_fJumpAcc;
		fRightVal = GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
		m_tInfo.fPosY -= fLeftVal - fRightVal;
		m_fJumpAcc += 0.3f;

		if (m_tInfo.fPosY > fY)
		{
			m_tInfo.fPosY = fY-m_tInfo.fCY*0.5f;
			m_fJumpAcc = 0;
		}
	}
	else//하강
	{
		//cout << "PosY= "<<m_tInfo.fPosY <<"바닥= " <<fY - m_tInfo.fCY*0.5f << endl;

		if (m_tInfo.fPosY >= fY - m_tInfo.fCY*0.5f-11)//바닥보다 아래에잇을때
		{
			m_tInfo.fPosY = fY - m_tInfo.fCY*0.5f;
			m_fJumpAcc = 0;
		}
		else //위에 
		{

			//cout << "dd" << fRightVal<<endl;
			fRightVal = GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;
			m_fJumpAcc += 0.3f;
			m_tInfo.fPosY +=  fRightVal;

		}
	}
	
	//if (m_bIsJump)
	//{
	//	 //자유 낙하 공식
	//	 //y = 힘 * 가속도 * sin(90) - 중력(9.8) * 가속도^2 * 0.5
	//	float fLeftVal = m_fJumpForce * m_fJumpAcc;
	//	float fRightVal = GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;


	//	m_tInfo.fPosY -= fLeftVal - fRightVal;

	//	 //착지할 때
	//	if (bIsColl && fLeftVal < fRightVal && m_tInfo.fPosY > fY - m_tInfo.fCY * 0.5f)
	//	{
	//		m_bIsJump = false;
	//		m_fJumpAcc = 0.f;
	//		m_tInfo.fPosY = fY - m_tInfo.fCY * 0.5f;
	//
	//	}
	//}
	//else if (bIsColl)
	//{
	//	m_tInfo.fPosY = fY - m_tInfo.fCY * 0.5f;
	//}
}

void CPlayer::Attack()
{
	cout << m_fDegree <<"도 " << endl;

	if (m_fDegree >= -22.5 && m_fDegree < 22.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX),(LONG)(m_tInfo.fPosY- m_fAtkRange*0.5),(LONG)(m_tInfo.fPosX + m_fAtkRange), (LONG)(m_tInfo.fPosY + m_fAtkRange*0.5) };
	else if (m_fDegree >= 22.5 && m_fDegree < 67.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX),(LONG)(m_tInfo.fPosY- m_fAtkRange), (LONG)(m_tInfo.fPosX + m_fAtkRange), (LONG)(m_tInfo.fPosY) };
	else if (m_fDegree >= 67.5 && m_fDegree < 112.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX - m_fAtkRange*0.5),(LONG)(m_tInfo.fPosY - m_fAtkRange), (LONG)(m_tInfo.fPosX + m_fAtkRange*0.5),(LONG)(m_tInfo.fPosY) };
	else if (m_fDegree >= 112.5 && m_fDegree < 157.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX - m_fAtkRange), (LONG)(m_tInfo.fPosY - m_fAtkRange),(LONG)(m_tInfo.fPosX), (LONG)m_tInfo.fPosY };
	else if (m_fDegree >= 157.5 || m_fDegree < -157.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX - m_fAtkRange), (LONG)(m_tInfo.fPosY - m_fAtkRange*0.5), (LONG)(m_tInfo.fPosX), (LONG)(m_tInfo.fPosY+ m_fAtkRange*0.5) };
	else if (m_fDegree <= -112.5 && m_fDegree > -157.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX - m_fAtkRange), (LONG)(m_tInfo.fPosY),(LONG)(m_tInfo.fPosX),(LONG)(m_tInfo.fPosY + m_fAtkRange) };
	else if (m_fDegree <= -67.5 && m_fDegree > -112.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX - m_fAtkRange*0.5), (LONG)(m_tInfo.fPosY), (LONG)(m_tInfo.fPosX+ m_fAtkRange*0.5),(LONG)(m_tInfo.fPosY + m_fAtkRange) };
	else if (m_fDegree <= -22.5 && m_fDegree > -67.5)
		m_tHitBox = { (LONG)(m_tInfo.fPosX), (LONG)(m_tInfo.fPosY), (LONG)(m_tInfo.fPosX + m_fAtkRange), (LONG)(m_tInfo.fPosY + m_fAtkRange) };

}


void CPlayer::Release()
{
}

void CPlayer::ScrollOffset()
{
	// 플레이어가 화면에서 일정 범위를 벗어났을 때 스크롤을 움직인다.
	if (WinCX * 0.5f + 200.f <= m_tInfo.fPosX - g_fScrollX)
	{
		g_fScrollX += m_fSpeed;
		m_LocInfo.fPosX += m_fSpeed;
	}
	if (WinCX* 0.5f - 200.f >= m_tInfo.fPosX - g_fScrollX)
	{
		g_fScrollX -= m_fSpeed;
		m_LocInfo.fPosX += m_fSpeed;
	}
}
