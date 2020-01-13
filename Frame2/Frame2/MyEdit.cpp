#include "stdafx.h"
#include "MyEdit.h"
#include "Terrain.h"
#include "BackGround.h"
CMyEdit::CMyEdit()
{
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize()
{
	// Tile Image
	CBmpManager::GetInstance()->LoadBmp(L"Tile", L"../Image/Tile/Tile20.bmp");

	// BackGround Image
	CBmpManager::GetInstance()->LoadBmp(L"bg", L"../Image/BackGround/Stage1BG.bmp");
	CObjectManager::GetInstance()->AddObject(BACKGROUND, CObjFactory<CBackGround>::CreateObject());

	// Terrain
	CObjectManager::GetInstance()->AddObject(TERRAIN, CObjFactory<CTerrain>::CreateObject());
}

int CMyEdit::Update()
{
	CObjectManager::GetInstance()->Update();
	KeyInput();		

	// ��ũ�� ���� ����
	if (0.f > g_fScrollX)
		g_fScrollX = 0.f;
	if (0.f > g_fScrollY)
		g_fScrollY = 0.f;
	if (float(TILE_COUNT_X * TILECX - WinCX) < g_fScrollX)
		g_fScrollX = float(TILE_COUNT_X * TILECX - WinCX);
	if (float(TILE_COUNT_Y * TILECY - WinCY) < g_fScrollY)
		g_fScrollY = float(TILE_COUNT_Y * TILECY - WinCY);	

	return NO_EVENT;
}

void CMyEdit::Render(HDC hDC)
{
	//HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"bg");
	//NULL_CHECK(hMemDC);
	//BitBlt(hDC, 0, 0, WinCX, WinCY, hMemDC, 0, 0, SRCCOPY);

	CObjectManager::GetInstance()->Render(hDC);
}

void CMyEdit::Release()
{
}

void CMyEdit::KeyInput()
{
	if (CKeyManager::GetInstance()->KeyPressing(KEY_A))
		g_fScrollX -= 10.f;
	if (CKeyManager::GetInstance()->KeyPressing(KEY_D))
		g_fScrollX += 10.f;
	if (CKeyManager::GetInstance()->KeyPressing(KEY_W))
		g_fScrollY -= 10.f;
	if (CKeyManager::GetInstance()->KeyPressing(KEY_S))
		g_fScrollY += 10.f;

	if (CKeyManager::GetInstance()->KeyUp(KEY_LBUTTON))
	{
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		// ���� ���콺 ��ǥ�� �׻� Ŭ���̾�Ʈ ������ ��ǥ�̱⿡
		// ���콺�� ��ũ���� �ݴ�� �������־�� �Ѵ�.
		pt.x += (LONG)g_fScrollX;
		pt.y += (LONG)g_fScrollY;
		cout << "���콺 ������=" << pt.x << endl;
		cout << "���콺 ������=" << pt.y << endl;
		CGameObject* pTerrain = CObjectManager::GetInstance()->GetTerrain();
		NULL_CHECK(pTerrain);

		dynamic_cast<CTerrain*>(pTerrain)->TileChange(pt, 1);
	}

	if (CKeyManager::GetInstance()->KeyUp(KEY_RETURN))
	{
		CGameObject* pTerrain = CObjectManager::GetInstance()->GetTerrain();
		NULL_CHECK(pTerrain);

		if (dynamic_cast<CTerrain*>(pTerrain)->SaveData(L"../Data/Tile.dat"))
			MessageBox(nullptr, L"���� ����!", L"", MB_OK);
		else
			MessageBox(nullptr, L"���� ����!", L"", MB_OK);
	}

	if (CKeyManager::GetInstance()->KeyUp(KEY_F))
	{
		CGameObject* pTerrain = CObjectManager::GetInstance()->GetTerrain();
		NULL_CHECK(pTerrain);

		if (dynamic_cast<CTerrain*>(pTerrain)->LoadData(L"../Data/Tile.dat"))
			MessageBox(nullptr, L"�ҷ����� ����!", L"", MB_OK);
		else
			MessageBox(nullptr, L"�ҷ����� ����!", L"", MB_OK);
	}
}

