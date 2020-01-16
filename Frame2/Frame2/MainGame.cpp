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

	// ���� ���۸�
	// ������ �ʴ� �ĸ���ۿ� �̹��� ��ü �۾��� �����ϰ� 
	// �ĸ���ۿ� �׷��� ��� ������� ������ۿ� �ѹ��� �ѷ��ش�.
	// ȭ�� �������� �ؼ��� �� �ִ�!
	
	HDC hBackBuffer = CBmpManager::GetInstance()->GetMemDC(L"Backbuffer");
	NULL_CHECK(hBackBuffer);

	CSceneManager::GetInstance()->Render(hBackBuffer);

	// �ĸ������ ������� ������۷� �����Ѵ�.
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
