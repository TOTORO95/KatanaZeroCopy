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

	m_Image = new Image(L"../Image/BackGround/bg.png", 0);
	m_Image2 = new Image(L"../Image/Slash/0.png", 0);
	hdc = GetDC(g_hwnd);
}

void CMainGame::Update()
{

}

void CMainGame::Render()
{
	Graphics g(hdc);

	//Rectangle(hdc, 0, 0, 50, 50);
	g.DrawImage(m_Image, 0, 0, 0, 0, 1280, 700, Gdiplus::Unit::UnitPixel);
	g.DrawImage(m_Image2, 100, 100, 0,0, 106, 32, Gdiplus::Unit::UnitPixel);
	

}

void CMainGame::Release()
{
}


