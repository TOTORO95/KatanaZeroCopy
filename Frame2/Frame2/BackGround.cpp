#include "stdafx.h"
#include "BackGround.h"

CBackGround::CBackGround()
{

}

CBackGround::CBackGround(wstring backGround)
{
	m_wstrImageKey = backGround;

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
	if (m_wstrImageKey == L"edit")
	{
		HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey);
		NULL_CHECK(hMemDC);
		BitBlt(hdc, 0, 0, WinCX, WinCY, hMemDC, WinCX*0.5 - m_WorldPos.x, 700 - m_WorldPos.y, SRCCOPY);
	}
	if (m_wstrImageKey == L"bg")
	{
		HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Black");
		BitBlt(hdc, 0, 0, 3000, 1500, hMemDC,0,0, SRCCOPY);

		hMemDC= CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey);
		NULL_CHECK(hMemDC);
		BitBlt(hdc, 0, 0, WinCX, WinCY, hMemDC, WinCX*0.5 - m_WorldPos.x, 0 - m_WorldPos.y + 400, SRCCOPY);
	}
	else if (m_wstrImageKey == L"bg2")
	{
		HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Black");
		BitBlt(hdc, 0, 0, 3000, 2000, hMemDC, 0, 0, SRCCOPY);

		hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey);//1900x15
		NULL_CHECK(hMemDC);
		BitBlt(hdc, 0, 0, WinCX, WinCY, hMemDC, WinCX*0.5 - m_WorldPos.x, 700 - m_WorldPos.y, SRCCOPY);
	}


}

void CBackGround::Release()
{
}

