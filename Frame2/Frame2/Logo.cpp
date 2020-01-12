#include "stdafx.h"
#include "Logo.h"


/*
 *	SCENE_TITLE,
	SCENE_STAGE1,
	SCENE_STAGE2,
	BOSS_STAGE,
	SCENE_END
*/
CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	// Logo Image
	CBmpManager::GetInstance()->LoadBmp(L"Logo",
		L"../Image/Logo/Logo.bmp");
}

int CLogo::Update()
{
	if (CKeyManager::GetInstance()->KeyDown(KEY_F))
	{
		CSceneManager::GetInstance()->SceneChange(SCENE_TITLE);
		return CHANGE_SCENE;
	}

	return NO_EVENT;
}

void CLogo::Render(HDC hDC)
{
	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Logo");
	NULL_CHECK(hMemDC);
	BitBlt(hDC, 0, 0, WinCX, WinCY, hMemDC, 0, 0, SRCCOPY);
}

void CLogo::Release()
{
}
