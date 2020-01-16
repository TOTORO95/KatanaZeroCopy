#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
float g_fScrollX = 0.f;
float g_fScrollY = 0.f;
CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	srand(unsigned(time(nullptr)));

	m_hdc = GetDC(g_hWnd);

	// Backbuffer Image
	CBmpManager::GetInstance()->LoadBmp(L"Backbuffer",
		L"../Image/Logo/BackGround.bmp");

	CSceneManager::GetInstance()->SceneChange(SCENE_LOGO);
}

void CMainGame::Update()
{
	CKeyManager::GetInstance()->Update();
	CSceneManager::GetInstance()->Update();
	
}

void CMainGame::Render()
{

	// 더블 버퍼링
	// 보이지 않는 후면버퍼에 이미지 교체 작업을 진행하고 
	// 후면버퍼에 그려진 모든 결과물을 전면버퍼에 한번만 뿌려준다.
	// 화면 깜빡임을 해소할 수 있다!
	
	HDC hBackBuffer = CBmpManager::GetInstance()->GetMemDC(L"Backbuffer");
	NULL_CHECK(hBackBuffer);

	CSceneManager::GetInstance()->Render(hBackBuffer);

	// 후면버퍼의 결과물을 전면버퍼로 복사한다.
	BitBlt(m_hdc, 0, 0, WinCX, WinCY, hBackBuffer, 0, 0, SRCCOPY);


}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hdc);

	CSceneManager::GetInstance()->DestroyInstance();
	CObjectManager::GetInstance()->DestroyInstance();
	CKeyManager::GetInstance()->DestroyInstance();
	CBmpManager::GetInstance()->DestroyInstance();
}
