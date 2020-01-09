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
	CBmpManager::GetInstance()->LoadBmp(L"RSlash", L"../Image/Player/Player_RSlash.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LSlash", L"../Image/Player/Player_LSlash.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Slash", L"../Image/Player/Player_AllSlash2.bmp");

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
	CObjectManager::GetInstance()->Render(hDC);
	CLineManager::GetInstance()->Render(hDC);

	//CLineManager::GetInstance()->Render(hDC);
	TCHAR strMouse[64] = {};
	//wsprintf 유니코드 문자열을 만드는함수
	wsprintf(strMouse, TEXT("MousePos X= %d Y= %d"), g_tMouseInfo.ptStart.x, g_tMouseInfo.ptStart.y);
	//lstrlen 유니코드 문자열의 길이를 출력
	TextOut(hDC, 600, 30, strMouse, lstrlen(strMouse));

}

void CStage1::Release()
{
}
