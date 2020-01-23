#include "stdafx.h"
#include "UserInterface.h"


CUserInterface::CUserInterface()
{
}


CUserInterface::~CUserInterface()
{
}

void CUserInterface::Initialize()
{
	//UI부분
	//m_iAlpha = 0;
	//m_BlendFuntion.AlphaFormat = 0;
	//m_BlendFuntion.BlendOp = AC_SRC_OVER;
	//m_BlendFuntion.BlendFlags = 0;
	//m_BlendFuntion.SourceConstantAlpha = m_iAlpha;//0~255  0투명 255불투명
	CBmpManager::GetInstance()->LoadBmp(L"BulletTime", L"../Image/BackGround/BulletTime.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"HUDTimer", L"../Image/UI/HUD_Timer.bmp");//112x19
	CBmpManager::GetInstance()->LoadBmp(L"TimerGage", L"../Image/UI/TimerGage.bmp");//94x11
	CBmpManager::GetInstance()->LoadBmp(L"HUDUI", L"../Image/UI/HUD_UI.bmp");//640x23
	CBmpManager::GetInstance()->LoadBmp(L"BatteryGage", L"../Image/UI/BatteryRedGage.bmp");//77x19
	CBmpManager::GetInstance()->LoadBmp(L"Battery", L"../Image/UI/BatteryBlueGage.bmp");//54x10
	CBmpManager::GetInstance()->LoadBmp(L"BulletReflect", L"../Image/Player/BulletReflect.bmp");
	m_fGameTimer = 0.f;
	m_fBulletGage = 100.f;
}

int CUserInterface::Update()
{
	m_fGameTimer += 2.0f / g_fTime;
	if (CKeyManager::GetInstance()->KeyPressing(KEY_SHIFT) && m_fBulletGage - 2>0)
	{
		m_fBulletGage -= 0.7f;
	}
	else
	{
		
		if (m_fBulletGage < 100)
			m_fBulletGage += 1.0f;
		else if (m_fBulletGage > 100)
			m_fBulletGage = 100;
	}
	return NO_EVENT;
}

void CUserInterface::Render(HDC hdc)
{
	//BulletTime(hdc);
	RenderUI(hdc);
}

void CUserInterface::Release()
{
}
//
//void CUserInterface::BulletTime(HDC hdc)
//{
//	if (CKeyManager::GetInstance()->KeyPressing(KEY_SHIFT) && m_fBulletGage - 2>0)
//	{
//		if (m_iAlpha <= 150)
//			m_iAlpha += 10;
//		m_BlendFuntion.SourceConstantAlpha = m_iAlpha;
//		AlphaBlend(hdc, 0, 0, WinCX, WinCY, CBmpManager::GetInstance()->GetMemDC(L"BulletTime"), 0, 0, 1280, 800, m_BlendFuntion);
//		m_fBulletGage -= 0.7f;
//	}
//	else
//	{
//		if (m_iAlpha>0)
//			m_iAlpha -= 10;
//		//cout << "bullettime" << endl;
//
//		if (m_iAlpha < 0)
//			m_iAlpha = 0;
//
//		m_BlendFuntion.SourceConstantAlpha = m_iAlpha;
//		if (m_iAlpha != 0)
//			AlphaBlend(hdc, 0, 0, WinCX, WinCY, CBmpManager::GetInstance()->GetMemDC(L"BulletTime"), 0, 0, 1280, 800, m_BlendFuntion);
//
//		if (m_fBulletGage < 100)
//			m_fBulletGage += 1.0f;
//		else if (m_fBulletGage > 100)
//			m_fBulletGage = 100;
//	}
//}

void CUserInterface::RenderUI(HDC hdc)
{
	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"HUDUI");
	NULL_CHECK(hMemDC);
	GdiTransparentBlt(hdc, 0, 0, 1280, 46, hMemDC, 0, 0, 640, 23, RGB(0, 0, 0));
	hMemDC = CBmpManager::GetInstance()->GetMemDC(L"HUDTimer");
	GdiTransparentBlt(hdc, WinCX*0.435, 0, 224, 38, hMemDC, 0, 0, 112, 19, RGB(0, 0, 0));
	hMemDC = CBmpManager::GetInstance()->GetMemDC(L"TimerGage");
	GdiTransparentBlt(hdc, WinCX*0.462, 4, 188.f - (m_fGameTimer / 188.f), 22, hMemDC, 0, 0, 94, 11, RGB(0, 0, 0));
	hMemDC = CBmpManager::GetInstance()->GetMemDC(L"BatteryGage");
	GdiTransparentBlt(hdc, WinCX*0.025, 0, 154, 38, hMemDC, 0, 0, 77, 19, RGB(0, 0, 0));
	hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Battery");
	int fGageVal = (m_fBulletGage + 2) / 10;

	GdiTransparentBlt(hdc, WinCX*0.0429, 8, 11 * fGageVal, 20, hMemDC, 0, 0, 5 * fGageVal, 10, SRCCOPY);

}
