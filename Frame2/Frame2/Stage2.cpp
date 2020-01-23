#include "stdafx.h"
#include "Stage2.h"
#include "Player.h"
#include "BackGround.h"
#include "UserInterface.h"
#include "Terrain.h"
#include "Tile.h"
#include "Monster.h"
#include "Grunt.h"
#include "Gunster.h"
#include "Door.h"
#include "Fan.h"
#include "LaserTrap.h"
#include "BulletTime.h"
CStage2::CStage2()
{
}


CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{
	//CLineManager::GetInstance()->Initialize();
	m_iMonCount = 2;
	m_bIsNext = false;
	CBmpManager::GetInstance()->LoadBmp(L"bg2", L"../Image/BackGround/Stage2bg.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"bk", L"../Image/BackGround/BK.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_R", L"../Image/Player/Player_R.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_L", L"../Image/Player/Player_L.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"DSlash", L"../Image/Player/Player_DefaultSlash.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Slash", L"../Image/Player/Player_AllSlashSheet242.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Tile", L"../Image/Tile/Tile20.bmp");
	
	//Player,BackGround,UI(Essential)
	CObjectManager::GetInstance()->AddObject(BACKGROUND, CObjFactory<CBackGround>::CreateObject(L"bg2"));
	CObjectManager::GetInstance()->AddObject(TERRAIN, CObjFactory<CTerrain>::CreateObject());
	CObjectManager::GetInstance()->AddObject(UI, CObjFactory<CUserInterface>::CreateObject());
	CObjectManager::GetInstance()->AddObject(DOOR, CObjFactory<CDoor>::CreateObject(298, 288, 40, 57));
	CObjectManager::GetInstance()->AddObject(PLAYER, CObjFactory<CPlayer>::CreateObject(200, 800));
	CObjectManager::GetInstance()->AddObject(BULLETTIME, CObjFactory<CBulletTime>::CreateObject());

	//Trap
	CObjectManager::GetInstance()->AddObject(TRAP, CObjFactory<CFan>::CreateObject(1578, 100));
	CObjectManager::GetInstance()->AddObject(TRAP, CObjFactory<LaserTrap>::CreateObject(TRAP,500, 380,515));
	CObjectManager::GetInstance()->AddObject(TRAP, CObjFactory<LaserTrap>::CreateObject(TRAP,1120, 80,445));



	//Monster
	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CGrunt>::CreateObject(1100, 530));
	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CGunster>::CreateObject(800, 520,30));
	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CGunster>::CreateObject(1578,150,10));

	CGameObject* pTerrain = CObjectManager::GetInstance()->GetTerrain();
	NULL_CHECK(pTerrain);

	//Load Tile
	dynamic_cast<CTerrain*>(pTerrain)->LoadData(L"../Data/Stage2.dat");

	for (auto tile : dynamic_cast<CTerrain*>(pTerrain)->GetTiles())
	{
		if (tile->iDrawID != 0)
		{
			CObjectManager::GetInstance()->AddObject(TILE,
				CObjFactory<CTile>::CreateObject(tile->fX, tile->fY, tile->iDrawID));
		}
	}
	CObjectManager::GetInstance()->DeleteGroup(TERRAIN);
	m_pMonList = CObjectManager::GetInstance()->GetObjList(MONSTER);
	m_pDoor = CObjectManager::GetInstance()->GetObjList(DOOR);



}

int CStage2::Update()
{
	CObjectManager::GetInstance()->Update();
	//타일 객체생성 완료 이제 충돌 처리 할차례
	if (-200.f > g_fScrollX)
		g_fScrollX = -200.f;
	if (-200.f > g_fScrollY)
		g_fScrollY = -200.f;
	if (float(TILE_COUNT_X * TILECX - WinCX) < g_fScrollX)
		g_fScrollX = float(TILE_COUNT_X * TILECX - WinCX);
	if (float(TILE_COUNT_Y * TILECY - WinCY) < g_fScrollY)
		g_fScrollY = float(TILE_COUNT_Y * TILECY - WinCY);


	int iMC = 0;
	for (auto pMon : m_pMonList)
	{
		if (pMon->GetStop())
			iMC++;
		if (iMC == m_iMonCount)
		{
			dynamic_cast<CDoor*>(m_pDoor.front())->SetNext(true);
			if (dynamic_cast<CDoor*>(m_pDoor.front())->GetisCOll())
			{
				cout << "씬전환" << endl;
				CSceneManager::GetInstance()->SceneChange(SCENE_STAGE2);
				return CHANGE_SCENE;

			}

		}
	}

	return NO_EVENT;
}

void CStage2::Render(HDC hDC)
{
	CObjectManager::GetInstance()->Render(hDC);
}

void CStage2::Release()
{
	CObjectManager::GetInstance()->Release();
}
