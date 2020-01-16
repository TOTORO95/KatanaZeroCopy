#include "stdafx.h"
#include "BackGround.h"


CBackGround::CBackGround()
{

}


CBackGround::~CBackGround()
{
}

void CBackGround::Initialize()
{
	SetPos(WinCX*0.5, WinCY*0.5);
	SetSize(WinCX, WinCY);
	CBmpManager::GetInstance()->LoadBmp(L"Black", L"../Image/BackGround/BK.bmp");


}

int CBackGround::Update()
{
	UpdateWorldPos2();
	//cout <<"WorldPos"<< m_WorldPos.x<< " "<<  m_WorldPos.y << endl;
	
	//SetPos(m_WorldPos.x, m_WorldPos.y);
	UpdateRect2();
	//cout<<m_tRect

	return NO_EVENT;
}

void CBackGround::Render(HDC hdc)
{
	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Black");
	BitBlt(hdc, 0, 0, 2400, 1500, hMemDC,0,0, SRCCOPY);

	hMemDC= CBmpManager::GetInstance()->GetMemDC(L"bg");
	//HDC hBackDC= 
	NULL_CHECK(hMemDC);
	BitBlt(hdc, 0, 0, WinCX, WinCY, hMemDC, WinCX*0.5 - m_WorldPos.x, 0, SRCCOPY);


}

void CBackGround::Release()
{
}

