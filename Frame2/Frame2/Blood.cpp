#include "stdafx.h"
#include "Blood.h"


CBlood::CBlood()//32x32   20도마다있음 16개
{

}

CBlood::CBlood(POINT pos,float fdgree)
{
	SetPos(pos.x, pos.y);
	m_fAngle = fdgree;
	m_fRadian = fdgree/180*PI;
}


CBlood::~CBlood()
{
}
//TODO: BOSS만들차례 피는 좀더 손봐야하는데 나중에할일!!!!
void CBlood::Initialize()
{
	//cout << "피클래스" << endl;RFlatBlood
	CBmpManager::GetInstance()->LoadBmp(L"Blood", L"../Image/Monster/Blood.bmp");
	

	m_tBloodFrame.dwFrameCount = 3;
	m_tBloodFrame.dwFrameSpeed = 200;
	m_tBloodFrame.dwFrameStart = 0;
	m_tBloodFrame.dwFrameX = 32;
	m_tBloodFrame.dwFrameY = 32;
	m_tBloodFrame.dwOldTime = GetTickCount();
	m_bisStop = false;
	m_iBlood = 0;
	DirectionAni();
}

int CBlood::Update()
{
	if (m_bisStop)
		return DEAD_OBJ;
	UpdateWorldPos2();
	CGameObject::UpdateRect2();
	Animate();
	//cout << "blood" << endl;
	return NO_EVENT;
}

void CBlood::Render(HDC hdc)
{
	//cout <<"X="<< m_tRect.left<<"  Y="<< m_tRect.top << endl;
	 
	
	if (!m_bisStop)
	{
		GdiTransparentBlt(hdc, m_tRect.left+g_fScrollX-40, m_tRect.top+g_fScrollY-20, 60, 60,//원래48
			CBmpManager::GetInstance()->GetMemDC(L"Blood")
			, 32 * m_iBlood, m_tBloodFrame.dwFrameY*m_tBloodFrame.dwFrameStart, 32, 32, RGB(0, 0, 0));

	}
}

void CBlood::Release()
{
}

void CBlood::Animate()//1 0.2
{
	DWORD dwCurTime = GetTickCount();
	if (m_tBloodFrame.dwOldTime + m_tBloodFrame.dwFrameSpeed / (g_fTime+0.3) <= dwCurTime)
	{
		++m_tBloodFrame.dwFrameStart;
		m_tBloodFrame.dwOldTime = dwCurTime;
	}
	if (m_tBloodFrame.dwFrameStart == m_tBloodFrame.dwFrameCount)
	{
		m_tBloodFrame.dwFrameStart = 0;
		m_bisStop = true;
	}
}

void CBlood::DirectionAni()
{
	if (m_fAngle > -10)//0~10사이는 0  10~30은 1  30~50 2 
		m_iBlood = ((int)m_fAngle + 10) / 20;
	else//-10~-30               -170~-150 10(-160)   -150~-130(-140) 11
		m_iBlood = 9 + (9 + (m_fAngle - 10) / 20);

	m_iBlood += sinf(GetTickCount())*1.5;
	//cout << "iblood"<<m_iBlood << endl;
	

}
