#include "stdafx.h"
#include "Title.h"


CTitle::CTitle()
{
}


CTitle::~CTitle()
{
}

void CTitle::Initialize()
{
	CBmpManager::GetInstance()->LoadBmp(L"TitleBG", L"../Image/Logo/Title_BG.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"TitleGrass", L"../Image/Logo/Title_Plants1.bmp");

}

int CTitle::Update()
{
	//if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	//{
	//	CSceneMgr::GetInstance()->SceneChange(SCENE_MENU);
	//	return CHANGE_SCENE;
	//}
	return NO_EVENT;
}

void CTitle::Render(HDC hDC)
{//TODO: 현재 타이틀 나무 애니메이션 제작 그다음 게임스테이지시작!
	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"TitleBG");
	NULL_CHECK(hMemDC);
	BitBlt(hDC, 0, 0, WinCX, WinCY, hMemDC, 0, 0, SRCCOPY);
	hMemDC = CBmpManager::GetInstance()->GetMemDC(L"TitleGrass");
	NULL_CHECK(hMemDC);

	GdiTransparentBlt(hDC, 0,210, 1280, 800, hMemDC,
		0, 0, 640, 340, RGB(56, 36, 79));



}

void CTitle::Release()
{
}
