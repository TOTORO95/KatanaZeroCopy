#include "stdafx.h"
#include "Stage1.h"
#include "Player.h"

CStage1::CStage1()
{
}


CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	CLineManager::GetInstance()->Initialize();
	CBmpManager::GetInstance()->LoadBmp(L"Stage1BG", L"../Image/BackGround/Stage1BG.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_R", L"../Image/Player/Player_R.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_L", L"../Image/Player/Player_L.bmp");
	CObjectManager::GetInstance()->AddObject(PLAYER, CObjFactory<CPlayer>::CreateObject());

}

int CStage1::Update()
{
	CObjectManager::GetInstance()->Update();
	return NO_EVENT;
}

void CStage1::Render(HDC hDC)
{
	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Stage1BG");
	NULL_CHECK(hMemDC);
	GdiTransparentBlt(hDC, 0, 0, 2132, 800, hMemDC, 0, 0, 1600, 600, SRCCOPY);
	CLineManager::GetInstance()->Render(hDC);
	CObjectManager::GetInstance()->Render(hDC);

}

void CStage1::Release()
{
}
