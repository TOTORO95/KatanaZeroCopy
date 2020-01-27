#include "stdafx.h"
#include "BossStage2.h"
#include "Player.h"
#include "BackGround.h"
#include "Terrain.h"
#include "Tile.h"
#include "Monster.h"
#include "Grunt.h"
#include "Gunster.h"
#include "Door.h"
#include "Fan.h"
#include "UserInterface.h"
#include "FrontGround.h"
#include "BulletTime.h"
#include "HeadHunter.h"
#include "Explosion.h"

CBossStage2::CBossStage2()
{
}


CBossStage2::~CBossStage2()
{
}

void CBossStage2::Initialize()
{
	g_fScrollX = 0;
	g_fScrollY = 0;
	m_iMonCount = 8;
	m_bIsNext = false;
	CBmpManager::GetInstance()->LoadBmp(L"bg4", L"../Image/BackGround/LastStage.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"bk", L"../Image/BackGround/BK.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_R", L"../Image/Player/Player_R.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_L", L"../Image/Player/Player_L.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"DSlash", L"../Image/Player/Player_DefaultSlash.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Slash", L"../Image/Player/Player_AllSlashSheet242.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Tile", L"../Image/Tile/Tile20.bmp");
	CObjectManager::GetInstance()->AddObject(BACKGROUND, CObjFactory<CBackGround>::CreateObject(L"bg4"));
	CObjectManager::GetInstance()->AddObject(TERRAIN, CObjFactory<CTerrain>::CreateObject());
	CObjectManager::GetInstance()->AddObject(PLAYER, CObjFactory<CPlayer>::CreateObject(300, 300));
	CObjectManager::GetInstance()->AddObject(UI, CObjFactory<CUserInterface>::CreateObject());
	CObjectManager::GetInstance()->AddObject(BULLETTIME, CObjFactory<CBulletTime>::CreateObject());
	CObjectManager::GetInstance()->AddObject(BOSS, CObjFactory<CHeadHunter>::CreateObject(1060, 620,2,HEADHUNTER));

	CGameObject* pTerrain = CObjectManager::GetInstance()->GetTerrain();
	NULL_CHECK(pTerrain);
	dynamic_cast<CTerrain*>(pTerrain)->LoadData(L"../Data/LastStage.dat");
	for (auto tile : dynamic_cast<CTerrain*>(pTerrain)->GetTiles())
	{
		if (tile->iDrawID != 0)
		{
			CObjectManager::GetInstance()->AddObject(TILE,
				CObjFactory<CTile>::CreateObject(tile->fX, tile->fY, tile->iDrawID));
		}
	}
	CObjectManager::GetInstance()->DeleteGroup(TERRAIN);
	pHeadHunter = CObjectManager::GetInstance()->GetObjList(BOSS).front();
	pBG = CObjectManager::GetInstance()->GetObjList(BACKGROUND).front();
	pPlayer = CObjectManager::GetInstance()->GetObjList(PLAYER).front();
}

int CBossStage2::Update()
{
	if (-200.f > g_fScrollX)
		g_fScrollX = -200.f;
	if (0.f > g_fScrollY)
		g_fScrollY = 0.f;
	if (float(TILE_COUNT_X * TILECX - WinCX) < g_fScrollX)
		g_fScrollX = float(TILE_COUNT_X * TILECX - WinCX);
	if (float(TILE_COUNT_Y * TILECY - WinCY) < g_fScrollY)
		g_fScrollY = float(TILE_COUNT_Y * TILECY - WinCY);


	CObjectManager::GetInstance()->Update();

	return NO_EVENT;
}

void CBossStage2::Render(HDC hDC)
{
	CObjectManager::GetInstance()->Render(hDC);

}
