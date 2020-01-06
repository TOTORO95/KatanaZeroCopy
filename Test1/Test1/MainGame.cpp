#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	g_tArea.bStart = false;
	m_hdc = GetDC(g_hWnd);
	m_ObjpList[PLAYER].push_back( AbsFactory<CPlayer>::CreateObject());

}

void CMainGame::Update()
{
	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto pObj : m_ObjpList[i])
		{
			if (pObj->IsDead() == DEAD_OBJ)
				continue;

			pObj->Update();
		}
	}
	CKeyMgr::GetInstance()->Update();

}

void CMainGame::Render()
{
	Rectangle(m_hdc, 0, 0, WinCX, WinCY);
	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto pObj : m_ObjpList[i])
		{
			if (pObj->IsDead() == DEAD_OBJ)
				continue;

			pObj->Render(m_hdc);
		}
	}

	TCHAR strMouse[64] = {};
	TCHAR strMouse2[64] = {};
	//wsprintf 유니코드 문자열을 만드는함수
	wsprintf(strMouse, TEXT("MousePos X= %d Y= %d"), g_tArea.ptStart.x, g_tArea.ptStart.y);
	wsprintf(strMouse2, TEXT("MousePos X= %d Y= %d"), g_tArea.ptEnd.x, g_tArea.ptEnd.y);
	//lstrlen 유니코드 문자열의 길이를 출력
	TextOut(m_hdc, 600, 30, strMouse, lstrlen(strMouse));
	TextOut(m_hdc, 600, 60, strMouse2, lstrlen(strMouse2));

}

void CMainGame::Release()
{
	CKeyMgr::GetInstance()->DestroyInstance();

}
