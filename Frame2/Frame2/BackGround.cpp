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
	SetPos(0, 0);
}

int CBackGround::Update()
{
	return NO_EVENT;
}

void CBackGround::Render(HDC hdc)
{
	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"bg");
	NULL_CHECK(hMemDC);
	BitBlt(hdc, m_tInfo.fX-g_fScrollX, m_tInfo.fY,WinCX+ g_fScrollX,WinCY, hMemDC, 0, 0, SRCCOPY);
}

void CBackGround::Release()
{
}
