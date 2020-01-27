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
	m_Trigger = false;
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
		cout << m_WorldPos.y << endl;
		HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey);
		NULL_CHECK(hMemDC);
		BitBlt(hdc, 0, 0, WinCX, WinCY, hMemDC, WinCX*0.5 - m_WorldPos.x, 0-m_WorldPos.y+386, SRCCOPY);
	}
	if (m_wstrImageKey == L"bg")
	{
		HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Black");
		BitBlt(hdc, 0, 0, 3000, 1500, hMemDC,0,0, SRCCOPY);
		
		hMemDC= CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey);
		NULL_CHECK(hMemDC);
		BitBlt(hdc, 0, 0, WinCX, WinCY, hMemDC, WinCX*0.5 - m_WorldPos.x, 0 -m_WorldPos.y + 400, SRCCOPY);
	}
	else if (m_wstrImageKey == L"bg2")
	{
		HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Black");
		BitBlt(hdc, 0, 0, 3000, 2000, hMemDC, 0, 0, SRCCOPY);

		hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey);//1900x15
		NULL_CHECK(hMemDC);
		BitBlt(hdc, 0, 0, WinCX, WinCY, hMemDC, WinCX*0.5 - m_WorldPos.x, 700 - m_WorldPos.y, SRCCOPY);
	}
	else if (m_wstrImageKey == L"bg3"||m_wstrImageKey==L"bg3-1")
	{
		if (m_Trigger)
		{
			m_wstrImageKey = L"bg3-1";
			HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Black");//640 400
			BitBlt(hdc, 0, 0, 3000, 2000, hMemDC, 0, 0, SRCCOPY);

			hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey);//1200x800
			NULL_CHECK(hMemDC);
			BitBlt(hdc, 0, 0, WinCX, WinCY, hMemDC, WinCX*0.5 - m_WorldPos.x, 0 - m_WorldPos.y + 386, SRCCOPY);

		}
		else
		{
			HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Black");//640 400
			BitBlt(hdc, 0, 0, 3000, 2000, hMemDC, 0, 0, SRCCOPY);

			hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey);//1200x800
			NULL_CHECK(hMemDC);
			BitBlt(hdc, 0, 0, WinCX, WinCY, hMemDC, WinCX*0.5 - m_WorldPos.x, 0 - m_WorldPos.y + 386, SRCCOPY);

		}
	}
	else if (m_wstrImageKey == L"bg4")
	{
		HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Black");//640 400
		BitBlt(hdc, 0, 0, 3000, 2000, hMemDC, 0, 0, SRCCOPY);

		hMemDC = CBmpManager::GetInstance()->GetMemDC(m_wstrImageKey);//1200x720
		NULL_CHECK(hMemDC);
		BitBlt(hdc, 0, 0, WinCX, 720, hMemDC, WinCX*0.5 - m_WorldPos.x, 0 - m_WorldPos.y + 386, SRCCOPY);

	}
}

void CBackGround::Release()
{
}

