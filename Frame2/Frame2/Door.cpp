#include "stdafx.h"
#include "Door.h"


CDoor::CDoor()
{
}

CDoor::CDoor(float fx, float fy, float fcx, float fcy)
{
	SetPos(fx, fy);
	SetSize(fcx, fcy);
}


CDoor::~CDoor()
{
}

void CDoor::Initialize()
{
	m_fAlpha = 0;
	m_bIsNext = false;
	m_BlendFuntion.AlphaFormat = 0;
	m_BlendFuntion.BlendOp = AC_SRC_OVER;
	m_BlendFuntion.BlendFlags = 0;
	m_BlendFuntion.SourceConstantAlpha = m_fAlpha;//0~255  0투명 255불투명
	m_tHitBox = { 0,0,0,0 };

}

int CDoor::Update()
{
	UpdateWorldPos2();
	UpdateRect2();

	m_fAlpha += 0.1;
	if (m_fAlpha >= 360)
		m_fAlpha = 0;

	m_BlendFuntion.SourceConstantAlpha= fabsl(sinf(m_fAlpha)*125);
	return NO_EVENT;
}

void CDoor::Render(HDC hdc)
{
	//Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	if (m_bIsNext)
	{
	
		AlphaBlend(hdc, m_tRect.left,m_tRect.top, 40, 60,
			CBmpManager::GetInstance()->GetMemDC(L"bk"), 0, 0, 1280, 800, m_BlendFuntion);
		m_tHitBox = { m_tRect.left,m_tRect.top,m_tRect.right,m_tRect.bottom };
	}

}

void CDoor::Release()
{
}
