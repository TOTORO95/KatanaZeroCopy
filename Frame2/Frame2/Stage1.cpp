#include "stdafx.h"
#include "Stage1.h"
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
CStage1::CStage1()
{
}


CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	//CLineManager::GetInstance()->Initialize();
	m_iMonCount = 4;
	m_bIsNext = false;
	CBmpManager::GetInstance()->LoadBmp(L"bg", L"../Image/BackGround/Stage1BG.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"fg", L"../Image/BackGround/Stage1FG2.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"bk", L"../Image/BackGround/BK.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_R", L"../Image/Player/Player_R.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_L", L"../Image/Player/Player_L.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"DSlash", L"../Image/Player/Player_DefaultSlash.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Slash", L"../Image/Player/Player_AllSlashSheet242.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Tile", L"../Image/Tile/Tile20.bmp");
	CObjectManager::GetInstance()->AddObject(BACKGROUND, CObjFactory<CBackGround>::CreateObject(L"bg"));


	CObjectManager::GetInstance()->AddObject(TERRAIN, CObjFactory<CTerrain>::CreateObject());
	CObjectManager::GetInstance()->AddObject(PLAYER, CObjFactory<CPlayer>::CreateObject(100, 500));
	CObjectManager::GetInstance()->AddObject(UI, CObjFactory<CUserInterface>::CreateObject());
	CObjectManager::GetInstance()->AddObject(BULLETTIME, CObjFactory<CBulletTime>::CreateObject());
	CObjectManager::GetInstance()->AddObject(FG, CObjFactory<CFrontGround>::CreateObject());
	
	CObjectManager::GetInstance()->AddObject(DOOR, CObjFactory<CDoor>::CreateObject(298, 288, 40, 57));


	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CGunster>::CreateObject(1400, 300));
	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CGunster>::CreateObject(500, 300));
	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CGunster>::CreateObject(1000, 300));
	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CGunster>::CreateObject(900, 520));
	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CGrunt>::CreateObject(580, 530));

	CGameObject* pTerrain = CObjectManager::GetInstance()->GetTerrain();
	NULL_CHECK(pTerrain);
	

	//if (dynamic_cast<CTerrain*>(pTerrain)->LoadData(L"../Data/Stage1.dat"))
	//	MessageBox(nullptr, L"불러오기 성공!", L"", MB_OK);
	//else
	//	MessageBox(nullptr, L"불러오기 실패!", L"", MB_OK);

	dynamic_cast<CTerrain*>(pTerrain)->LoadData(L"../Data/Stage1.dat");

	for (auto tile : dynamic_cast<CTerrain*>(pTerrain)->GetTiles())
	{
		if (tile->iDrawID !=0)
		{
			CObjectManager::GetInstance()->AddObject(TILE,
				CObjFactory<CTile>::CreateObject(tile->fX, tile->fY, tile->iDrawID));
		}
	}
	CObjectManager::GetInstance()->DeleteGroup(TERRAIN);
	m_pMonList	= CObjectManager::GetInstance()->GetObjList(MONSTER);
	m_pDoor	= CObjectManager::GetInstance()->GetObjList(DOOR);


}

int CStage1::Update()
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

void CStage1::Render(HDC hDC)
{
	//HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Stage1BG");
	//NULL_CHECK(hMemDC);
	//GdiTransparentBlt(hDC, 0, 0, 2132, 800, hMemDC, 0, 0, 1600, 600, SRCCOPY);
	//CLineManager::GetInstance()->Render(hDC);

	//불릿타임 몬스터 플레이어 트랩 fg ui  
	CObjectManager::GetInstance()->Render(hDC);
/*
	GdiTransparentBlt(hDC, 0- g_fScrollX, 0, 1600,600,CBmpManager::GetInstance()->GetMemDC(L"fg")
		, 0, 0, 1600, 600, RGB(0,0,0));*/
	//Rectangle(hDC, 280, 260, 320, 320);
	//BitBlt(hDC, 278-g_fScrollX, 258-g_fScrollY, 40, 60,
	//	CBmpManager::GetInstance()->GetMemDC(L"bk"), 0, 0, SRCCOPY);

	////CLineManager::GetInstance()->Render(hDC);
	//TCHAR strMouse[64] = {};
	////wsprintf 유니코드 문자열을 만드는함수
	//wsprintf(strMouse, TEXT("MousePos X= %d Y= %d"), g_tMouseInfo.ptStart.x, g_tMouseInfo.ptStart.y);
	////lstrlen 유니코드 문자열의 길이를 출력
	//TextOut(hDC, 600, 30, strMouse, lstrlen(strMouse));

}

void CStage1::Release()
{
	CObjectManager::GetInstance()->Release();
}
