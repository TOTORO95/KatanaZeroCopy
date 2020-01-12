#include "stdafx.h"
#include "EditMap.h"
#include "Player.h"
#include "Terrain.h"

CEditMap::CEditMap()
{
}


CEditMap::~CEditMap()
{
}

void CEditMap::Initialize()
{
	CBmpManager::GetInstance()->LoadBmp(L"BG", L"../Image/BackGround/bg1.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Tile", L"../Image/Tile/Tile.bmp");
	CObjectManager::GetInstance()->AddObject(TERRAIN, CObjFactory<CTerrain>::CreateObject(TERRAIN, 1280.f, 600.f));
	CObjectManager::GetInstance()->AddObject(TERRAIN, CObjFactory<CTerrain>::CreateObject(TERRAIN, 1280.f, 600.f));
	CBmpManager::GetInstance()->LoadBmp(L"Player_R", L"../Image/Player/Player_R.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_L", L"../Image/Player/Player_L.bmp");
	CObjectManager::GetInstance()->AddObject(PLAYER, CObjFactory<CPlayer>::CreateObject());

	GetClientRect(g_hWnd, &m_rect);
}

int CEditMap::Update()
{
	CObjectManager::GetInstance()->Update();

	cout << "Edit Scene" << endl;

	return NO_EVENT;
}

void CEditMap::Render(HDC hDC)
{
	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"BG");
	FillRect(hDC, &m_rect, CreateSolidBrush(RGB(255, 255, 255)));
	GdiTransparentBlt(hDC, 0, 0, 1600, 600, hMemDC, 0, 0, 1296, 485, SRCCOPY);
	CObjectManager::GetInstance()->Render(hDC);

}
