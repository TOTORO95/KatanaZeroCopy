#include "stdafx.h"
#include "Terrain.h"


CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release();
}

void CTerrain::Initialize()
{
	m_iMaxX = (WinCX / 20)*1.5;//1280/20
	m_iMaxY = (WinCY / 20)*1.5;//800/20
	m_vecTile.reserve(m_iMaxX * m_iMaxY);

	TILE_INFO* pTile = nullptr;

	for (int i = 0; i < m_iMaxY; ++i)
	{
		for (int j = 0; j < m_iMaxX; ++j)
		{
			pTile = new TILE_INFO;

			pTile->fX = j * TILECX + TILECX * 0.5f;
			pTile->fY = i * TILECY + TILECY * 0.5f;
			pTile->iDrawID = 0;
			pTile->iOption = 0;

			m_vecTile.push_back(pTile);
		}
	}

}

int CTerrain::Update()
{
	return NO_EVENT;
}

void CTerrain::Render(HDC hDC)
{
	// 컬링 적용.
	// 컬링: 추려내기 기법. (최적화)

	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Tile");
	NULL_CHECK(hMemDC);
	
	int iRenderCount = 0;

	int iCullStartY = (int)g_fScrollY / TILECY;	//800/20    행번호
	int iCullStartX = (int)g_fScrollX / TILECX;	//1280 /20  열번호
	int iTileCountX = WinCX / TILECX; //1280/20 64+2
	int iTileCountY = WinCY / TILECY;	//800/20/ 40+8

	int iIndex = 0;

	for (int i = iCullStartY; i < iCullStartY + iTileCountY + 2; ++i)
	{
		for(int j = iCullStartX; j < iCullStartX + iTileCountX + 2; ++j)
		{
			iIndex = i * m_iMaxX + j;

			if(0 > iIndex || (int)m_vecTile.size() <= iIndex)
				continue;
			//int iLeft = int(m_vecTile[iIndex]->fX - TILECX * 0.5f);
			//int iTop = int(m_vecTile[iIndex]->fY - TILECY * 0.5f );

			int iLeft = int(m_vecTile[iIndex]->fX - TILECX * 0.5f - g_fScrollX);
			int iTop = int(m_vecTile[iIndex]->fY - TILECY * 0.5f - g_fScrollY);

			GdiTransparentBlt(hDC, iLeft, iTop, TILECX, TILECY, hMemDC, m_vecTile[iIndex]->iDrawID * TILECX, 0,
				TILECX, TILECY, RGB(0, 0, 0));

				//BitBlt(hDC, iLeft, iTop, TILECX, TILECY,
				//	hMemDC, m_vecTile[iIndex]->iDrawID * TILECX, 0, SRCCOPY);

			iRenderCount++;
		}
	}
	

	TCHAR sz[32] = L"";
	swprintf_s(sz, L"RenderCount: %d", iRenderCount);
	TextOut(hDC, 100, 100, sz, lstrlen(sz));


	///////////////////////////////////////////////////////////////////////////////

	//// 컬링 하기 전
	//
	//HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Tile");
	//NULL_CHECK(hMemDC);

	//int iRenderCount = 0;

	//for (size_t i = 0; i < m_vecTile.size(); ++i)
	//{
	//	int iLeft = int(m_vecTile[i]->fX - TILECX * 0.5f /*- g_fScrollX*/);
	//	int iTop = int(m_vecTile[i]->fY - TILECY * 0.5f /*- g_fScrollY*/);

	//	//GdiTransparentBlt(hDC, iLeft, iTop, TILECX, TILECY, hMemDC, 0, 0,
	//					//m_vecTile[i]->iDrawID * TILECX, TILECY, SRCCOPY);

	//	BitBlt(hDC, iLeft, iTop, TILECX, TILECY,
	//		hMemDC, m_vecTile[i]->iDrawID * TILECX, 0, SRCCOPY);

	//	iRenderCount++;
	//}

	//TCHAR sz[32] = L"";
	//swprintf_s(sz, L"RenderCount: %d", iRenderCount);
	//TextOut(hDC, 100, 100, sz, lstrlen(sz));
}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE_INFO*>);
	m_vecTile.clear();
}

void CTerrain::TileChange(const POINT& pt, int iDrawID, int iOption)
{
	// 마우스 픽킹
	int i = pt.y / TILECY; // 행
	int j = pt.x / TILECX; // 열
	int iIndex = i * m_iMaxX + j;

	if (0 > iIndex || (int)m_vecTile.size() <= iIndex)
		return;

	m_vecTile[iIndex]->iDrawID += iDrawID;
	m_vecTile[iIndex]->iOption += iOption;

	if (m_vecTile[iIndex]->iDrawID >= 5)
	{
		m_vecTile[iIndex]->iDrawID =0;
		m_vecTile[iIndex]->iOption =0;
	}
}

bool CTerrain::SaveData(const wstring& wstrFilePath)
{
	// WinAPI 파일 개방
	HANDLE hFile = CreateFile(
		wstrFilePath.c_str(), /* 파일 경로 */
		GENERIC_WRITE, /* 입출력 모드 */
		0, 
		0, 
		CREATE_ALWAYS, /* 파일 생성 방식 */
		FILE_ATTRIBUTE_NORMAL, /* 생성된 파일 특성 */
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return false;

	DWORD dwBytes = 0;

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		// WinAPI 파일 출력
		WriteFile(
			hFile,	/* 개방된 파일의 핸들 */
			m_vecTile[i], /* 출력할 데이터의 메모리 주소 */
			sizeof(TILE_INFO), /* 출력할 데이터의 크기 */
			&dwBytes, /* 얼마만큼 출력이 진행됐는지 바이트 수를 기록 */
			nullptr);
	}

	CloseHandle(hFile);

	return true;
}

bool CTerrain::LoadData(const wstring& wstrFilePath)
{
	// WinAPI 파일 개방
	HANDLE hFile = CreateFile(
		wstrFilePath.c_str(), /* 파일 경로 */
		GENERIC_READ, /* 입출력 모드 */
		0,
		0,
		OPEN_EXISTING, /* 파일 생성 방식 */
		FILE_ATTRIBUTE_NORMAL, /* 생성된 파일 특성 */
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return false;

	if (!m_vecTile.empty())
	{
		for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE_INFO*>);
		m_vecTile.clear();
	}

	TILE_INFO tInfo = {};
	DWORD dwBytes = 0;

	while (true)
	{
		// WinAPI 파일 입력
		ReadFile(
			hFile,	/* 개방된 파일의 핸들 */
			&tInfo, /* 입력 받을 데이터의 메모리 주소 */
			sizeof(TILE_INFO), /* 입력 받을 데이터의 크기 */
			&dwBytes, /* 입력할 데이터가 얼마나 남았는지 바이트 수를 기록 */
			nullptr);

		if (0 == dwBytes)
			break;

		m_vecTile.push_back(new TILE_INFO(tInfo));
	}

	CloseHandle(hFile);

	return true;
}
