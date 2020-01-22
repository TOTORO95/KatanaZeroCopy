#include "stdafx.h"
#include "FrontGround.h"


CFrontGround::CFrontGround()
{
}

CFrontGround::CFrontGround(float x, float y)
{
	SetPos(x, y);
}


CFrontGround::~CFrontGround()
{
}

void CFrontGround::Initialize()
{
	//CBmpManager::GetInstance()->GetMemDC()
}

int CFrontGround::Update()
{
	return NO_EVENT;
}

void CFrontGround::Render(HDC hdc)
{
	GdiTransparentBlt(hdc, 0 - g_fScrollX, 0, 1600, 600, CBmpManager::GetInstance()->GetMemDC(L"fg")
		, 0, 0, 1600, 600, RGB(0, 0, 0));
}

void CFrontGround::Release()
{
}
