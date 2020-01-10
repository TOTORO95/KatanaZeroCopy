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
	m_Image2 = new Image(L"../Image/PNG_Slash_Sheet.png", 0);
	hdc = GetDC(g_hwnd);
	m_ianim = 0;
	m_inum = 0;
}

void CMainGame::Update()
{
	m_ianim++;
	if(m_ianim%50==0)
	{
		m_inum++;
		if (m_inum >= 5)
			m_inum = 0;
	}
	
}

void CMainGame::Render()
{
	Graphics g(hdc);
	
	//Rectangle(hdc, 0, 0, 50, 50);
	
	g.DrawImage(m_Image, 0, 0, 0, 0, 1280, 700, Gdiplus::Unit::UnitPixel);
	g.DrawImage(m_Image2, 369,90 , 123 * m_inum,0, 123, 30, Gdiplus::Unit::UnitPixel);
	

}

void CMainGame::Release()
{
}


