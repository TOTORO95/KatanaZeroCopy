#include "stdafx.h"
#include "Stage1.h"
#include "Player.h"
#include "BackGround.h"
#include "Terrain.h"
#include "Tile.h"
#include "Monster.h"
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
	m_iMonCount = 3;
	m_bIsNest = false;
	CBmpManager::GetInstance()->LoadBmp(L"bg", L"../Image/BackGround/Stage1BG.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"bk", L"../Image/BackGround/BK.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_R", L"../Image/Player/Player_R.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Player_L", L"../Image/Player/Player_L.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"DSlash", L"../Image/Player/Player_DefaultSlash.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Slash", L"../Image/Player/Player_AllSlashSheet242.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"Tile", L"../Image/Tile/Tile20.bmp");
	CObjectManager::GetInstance()->AddObject(BACKGROUND, CObjFactory<CBackGround>::CreateObject());
	CObjectManager::GetInstance()->AddObject(TERRAIN, CObjFactory<CTerrain>::CreateObject());
	CObjectManager::GetInstance()->AddObject(PLAYER, CObjFactory<CPlayer>::CreateObject());

	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CMonster>::CreateObject(1280, 300, GUNSTER));
	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CMonster>::CreateObject(500, 530, GUNSTER));
	CObjectManager::GetInstance()->AddObject(MONSTER, CObjFactory<CMonster>::CreateObject(800, 530, GRUNT));

	CGameObject* pTerrain = CObjectManager::GetInstance()->GetTerrain();
	NULL_CHECK(pTerrain);

	if (dynamic_cast<CTerrain*>(pTerrain)->LoadData(L"../Data/Stage1.dat"))
		MessageBox(nullptr, L"불러오기 성공!", L"", MB_OK);
	else
		MessageBox(nullptr, L"불러오기 실패!", L"", MB_OK);


	for (auto tile : dynamic_cast<CTerrain*>(pTerrain)->GetTiles())
	{
		//RECT *temp = new RECT((int)(tile->fX-TILECX*0.5), );
		if (tile->iDrawID !=0)
		{
			
			CObjectManager::GetInstance()->AddObject(TILE,
				CObjFactory<CTile>::CreateObject(tile->fX, tile->fY, tile->iDrawID));
		}
	}
	CObjectManager::GetInstance()->DeleteGroup(TERRAIN);

	m_iAlpha = 0;
	m_BlendFuntion.AlphaFormat = 0;
	m_BlendFuntion.BlendOp = AC_SRC_OVER;
	m_BlendFuntion.BlendFlags = 0;
	m_BlendFuntion.SourceConstantAlpha = m_iAlpha;//0~255  0투명 255불투명

}

int CStage1::Update()
{
	CObjectManager::GetInstance()->Update();
	//타일 객체생성 완료 이제 충돌 처리 할차례
	if (0.f > g_fScrollX)
		g_fScrollX = 0.f;
	if (0.f > g_fScrollY)
		g_fScrollY = 0.f;
	if (float(TILE_COUNT_X * TILECX - WinCX) < g_fScrollX)
		g_fScrollX = float(TILE_COUNT_X * TILECX - WinCX);
	if (float(TILE_COUNT_Y * TILECY - WinCY) < g_fScrollY)
		g_fScrollY = float(TILE_COUNT_Y * TILECY - WinCY);
	


 	OBJECT_LIST tMonList=CObjectManager::GetInstance()->GetObjList(MONSTER);
	int iMC = 0;
	for (auto pMon : tMonList)
	{
		if (pMon->GetStop())
			iMC++;
		if (iMC == m_iMonCount)
		{
			m_bIsNest = true;
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


	CObjectManager::GetInstance()->Render(hDC);

	m_BlendFuntion.SourceConstantAlpha=m_iAlpha = 200;
	AlphaBlend(hDC, 278 - g_fScrollX, 258 - g_fScrollY, 40, 60,
		CBmpManager::GetInstance()->GetMemDC(L"bk"), 0, 0, 1280, 800, m_BlendFuntion);

	m_tDoor= {278 , 258,318 ,318};
	Rectangle(hDC, m_tDoor.left- g_fScrollX ,
		m_tDoor.top - g_fScrollY,
		m_tDoor.right - g_fScrollX,
		m_tDoor.bottom - g_fScrollY);

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
}
