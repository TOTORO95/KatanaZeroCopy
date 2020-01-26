#include "stdafx.h"
#include "BossScene1.h"
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
CBossScene1::CBossScene1()
{

}


CBossScene1::~CBossScene1()
{
}

void CBossScene1::Initialize()
{
	g_fScrollX = 0;
	g_fScrollY = 0;
	m_iMonCount = 8;
	m_bIsNext = false;
	CBmpManager::GetInstance()->LoadBmp(L"bg3", L"../Image/BackGround/BossStage1.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"bk", L"../Image/BackGround/BK.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_R", L"../Image/Player/Player_R.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_L", L"../Image/Player/Player_L.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"DSlash", L"../Image/Player/Player_DefaultSlash.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Slash", L"../Image/Player/Player_AllSlashSheet242.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Tile", L"../Image/Tile/Tile20.bmp");

	CObjectManager::GetInstance()->AddObject(BACKGROUND, CObjFactory<CBackGround>::CreateObject(L"bg3"));
	// 1번째문 2번째문 3번째문	4번째문 높이450
	// 210     480		820		1060
	CObjectManager::GetInstance()->AddObject(TERRAIN, CObjFactory<CTerrain>::CreateObject());
	CObjectManager::GetInstance()->AddObject(PLAYER, CObjFactory<CPlayer>::CreateObject(900, 300));
	CObjectManager::GetInstance()->AddObject(UI, CObjFactory<CUserInterface>::CreateObject());
	CObjectManager::GetInstance()->AddObject(BULLETTIME, CObjFactory<CBulletTime>::CreateObject());
	//CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CGunster>::CreateObject(1060, 450));
	m_iSpawn = 0;
	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CHeadHunter>::CreateObject(1060, 450));



	CGameObject* pTerrain = CObjectManager::GetInstance()->GetTerrain();
	NULL_CHECK(pTerrain);


	//if (dynamic_cast<CTerrain*>(pTerrain)->LoadData(L"../Data/Stage1.dat"))
	//	MessageBox(nullptr, L"불러오기 성공!", L"", MB_OK);
	//else
	//	MessageBox(nullptr, L"불러오기 실패!", L"", MB_OK);

	dynamic_cast<CTerrain*>(pTerrain)->LoadData(L"../Data/BossStage1.dat");

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

int CBossScene1::Update()
{
	
	CObjectManager::GetInstance()->Update();
	//타일 객체생성 완료 이제 충돌 처리 할차례
	if (-200.f > g_fScrollX)
		g_fScrollX = -200.f;
	if (0.f > g_fScrollY)
		g_fScrollY = 0.f;
	if (float(TILE_COUNT_X * TILECX - WinCX) < g_fScrollX)
		g_fScrollX = float(TILE_COUNT_X * TILECX - WinCX);
	if (float(TILE_COUNT_Y * TILECY - WinCY) < g_fScrollY)
		g_fScrollY = float(TILE_COUNT_Y * TILECY - WinCY);
	//m_iSpawn++;
	//if (m_iSpawn % 200 == 0)
	//{
	//	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CGunster>::CreateObject(210, 450));
	//	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CGunster>::CreateObject(1060, 450));
	//}


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

void CBossScene1::Render(HDC hDC)
{
	CObjectManager::GetInstance()->Render(hDC);
}

void CBossScene1::Release()
{
	CObjectManager::GetInstance()->Release();
}
