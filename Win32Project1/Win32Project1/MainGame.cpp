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

	//m_Image = new Image(L"../Image/BackGround/bg.png", 0);
	//m_Image2 = new Image(L"../Image/PNG_GrassIntit.png", 0);
	CImageManager::GetInstance()->LoadImg(L"BG", L"../Image/bg.png");
	CImageManager::GetInstance()->LoadImg(L"Grass", L"../Image/PNG_GrassIntit.png");
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

	//HDC Backbuffer = CImageManager::GetInstance()->GetMemDC(L"BG");

	//HDC Backbuffer= 
	Graphics g(hdc);
	g.DrawImage(CImageManager::GetInstance()->GetMemImage(L"BG"),
		0,0,0, 0, WinCX, WinCY, Gdiplus::Unit::UnitPixel);
	
	//BitBlt(hdc, 0, 0, WinCX, WinCY, Backbuffer, 0, 0, SRCCOPY);

	
	//Rectangle(hdc, 0, 0, 50, 50);
	//g.DrawImage(m_Image2, 100, 100, 0,0, 106, 32, Gdiplus::Unit::UnitPixel);
	//g.DrawImage(m_Image, 0, 0, 0, 0, 1280, 700, Gdiplus::Unit::UnitPixel);
	//g.DrawImage()
	//Graphics g(Backbuffer);

	//g.DrawImage(CImageManager::GetInstance()->GetMemImage(L"BG"),
	//	,0, 0, WinCX, WinCY, Gdiplus::Unit::UnitPixel);
	//g.DrawImage(CImageManager::GetInstance()->GetMemDC(L"Grass"),
	//	0,0, m_GrassFrame.dwFrameX*m_GrassFrame.dwFrameStart, 0, 640, 360, Gdiplus::Unit::UnitPixel);
	

	//BitBlt(hdc, 0, 0, WinCX, WinCY, Backbuffer, 0, 0, SRCCOPY);
	//Graphics g(hdc);

	//BitBlt(hdc, 0, 0, WinCX, WinCY, Backbuffer, 0, 0, SRCCOPY);


}

void CMainGame::Release()
{
	ReleaseDC(g_hwnd, hdc);
	CImageManager::GetInstance()->DestroyInstance();

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


