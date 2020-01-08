#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"

float g_fScrollX = 0.f;


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
	m_ObjpList[PLAYER].push_back(AbsFactory<CPlayer>::CreateObject());
	CLineMgr::GetInstance()->Initialize();


	CBmpMgr::GetInstance()->LoadBmp(L"BackGound", L"../Image/BackGround/BigClub.bmp");

	CBmpMgr::GetInstance()->LoadBmp(L"Player", L"../Image/Player/Player6.bmp");


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
	HDC hMemDC = CBmpMgr::GetInstance()->GetMemDC(L"BackGound");
	NULL_CHECK(hMemDC);

	//// Source DC�� �׷��� ��Ʈ���� Dest DC�� �����ϴ� �Լ�.
	BitBlt(m_hdc, 0, 0, WinCX, WinCY, hMemDC, 0+g_fScrollX, 0, SRCCOPY);

	//Rectangle(m_hdc, 0, 0, WinCX, WinCY);
	for (int i = 0; i < OBJ_END; i++)
	{
		for (auto pObj : m_ObjpList[i])
		{
			if (pObj->IsDead() == DEAD_OBJ)
				continue;

			pObj->Render(m_hdc);
		}
	}

	CLineMgr::GetInstance()->Render(m_hdc);
	TCHAR strMouse[64] = {};
	TCHAR strMouse2[64] = {};
	//wsprintf �����ڵ� ���ڿ��� ������Լ�
	wsprintf(strMouse, TEXT("MousePos X= %d Y= %d"), g_tArea.ptStart.x, g_tArea.ptStart.y);
	wsprintf(strMouse2, TEXT("MousePos X= %d Y= %d"),g_Point.x, g_Point.y);
	//lstrlen �����ڵ� ���ڿ��� ���̸� ���
	TextOut(m_hdc, 600, 30, strMouse, lstrlen(strMouse));
	TextOut(m_hdc, 600, 60, strMouse2, lstrlen(strMouse2));

}

void CMainGame::Release()
{
	CKeyMgr::GetInstance()->DestroyInstance();
	CBmpMgr::GetInstance()->DestroyInstance();
}
