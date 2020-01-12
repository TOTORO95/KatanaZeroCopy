#include "stdafx.h"
#include "MainGame.h"


CMainGame::CMainGame()
{

}


CMainGame::~CMainGame()
{
}

void CMainGame::Initialize()
{
	CBmpManager::GetInstance()->LoadBmp(L"BG", L"../Image/bg.bmp");
	//m_Image = new Image(L"../Image/BackGround/bg.png", 0);
	//m_Image2 = new Image(L"../Image/PNG_GrassIntit.png", 0);
	m_GrassFrame.dwFrameStart = 0;
	m_GrassFrame.dwFrameCount = 11;
	m_GrassFrame.dwFrameSpeed = 100;
	m_GrassFrame.dwFrameX = 640;
	m_GrassFrame.dwFrameY = 0;
	m_GrassFrame.dwOldTime = GetTickCount();

	hdc = GetDC(g_hwnd);
}

void CMainGame::Update()
{
	GrassAnimate();
}

void CMainGame::Render()
{

	//HDC Backbuffer = CBmpManager::GetInstance()->GetMemDC(L"BG");
	GdiTransparentBlt(hdc, 0, 0, 1280, 485, CBmpManager::GetInstance()->GetMemDC(L"BG"), 0, 0, 1280, 485, RGB(0, 0, 0));
	//HDC Backbuffer= 
	//BitBlt(hdc, 0, 0, WinCX, WinCY, Backbuffer, 0, 0, SRCCOPY);
	

	
	Rectangle(hdc, 0, 0, 50, 50);


}

void CMainGame::Release()
{
	ReleaseDC(g_hwnd, hdc);

}

void CMainGame::GrassAnimate()
{
	DWORD dwCurTime = GetTickCount();

	if (m_GrassFrame.dwOldTime + m_GrassFrame.dwFrameSpeed <= dwCurTime)
	{
		++m_GrassFrame.dwFrameStart;
		m_GrassFrame.dwOldTime = dwCurTime;
	}

	if (m_GrassFrame.dwFrameStart == m_GrassFrame.dwFrameCount)
		m_GrassFrame.dwFrameStart = 0;

}


