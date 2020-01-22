#include "stdafx.h"
#include "BulletTime.h"


CBulletTime::CBulletTime()
{

}


CBulletTime::~CBulletTime()
{
}

void CBulletTime::Initialize()
{
	CBmpManager::GetInstance()->LoadBmp(L"BulletTime", L"../Image/BackGround/BulletTime.bmp");
	m_fBulletGage = 100.f;

	
	
	//Alpha부분
	m_iAlpha = 0;
	m_BlendFuntion.AlphaFormat = 0;
	m_BlendFuntion.BlendOp = AC_SRC_OVER;
	m_BlendFuntion.BlendFlags = 0;
	m_BlendFuntion.SourceConstantAlpha = m_iAlpha;//0~255  0투명 255불투명
}

int CBulletTime::Update()
{
	return NO_EVENT;
}

void CBulletTime::Render(HDC hdc)
{
	BulletTime(hdc);
}

void CBulletTime::Release()
{
}

void CBulletTime::BulletTime(HDC hdc)
{
	if (CKeyManager::GetInstance()->KeyPressing(KEY_SHIFT) && m_fBulletGage - 2>0)
	{
		if (m_iAlpha <= 150)
			m_iAlpha += 10;
		m_BlendFuntion.SourceConstantAlpha = m_iAlpha;
		AlphaBlend(hdc, 0, 0, WinCX, WinCY, CBmpManager::GetInstance()->GetMemDC(L"BulletTime"), 0, 0, 1280, 800, m_BlendFuntion);
		m_fBulletGage -= 0.7f;
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
