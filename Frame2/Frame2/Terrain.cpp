#include "stdafx.h"
#include "Terrain.h"


CTerrain::CTerrain()
{
}

CTerrain::CTerrain(float fMapX, float fMapY)
{
	int m_iTileX = fMapX / TileCX;
	int m_iTileY = fMapY / TileCY;

}


CTerrain::~CTerrain()
{
	Release();
}


void CTerrain::Initialize()
{
	TILE_INFO* pTile = nullptr;
	for (int i = 0; i < m_iTileY; i++)
	{
		for (int j = 0; j < m_iTileX; j++)
		{
			pTile = new TILE_INFO;
			pTile->fX = j* TileCX + TileCX * 0.5f;
			pTile->fY = i* TileCY + TileCY * 0.5f;
			pTile->iDraw = 0;
			pTile->iOption = 0;
			m_pTile.push_back(pTile);
		}
	}
}

int CTerrain::Update()
{
	return NO_EVENT;

}

void CTerrain::Render(HDC hdc)
{
	
	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Tile");;
	NULL_CHECK(hMemDC);

	int iRenderCount = 0;

	int iCullStartY = (int)g_fScrollY / TileCX;	// 행번호
	int iCullStartX = (int)g_fScrollX / TileCY;	// 열번호
	int iTileCountX = WinCX / TileCX;
	int iTileCountY = WinCY / TileCY;

	int iIndex = 0;

	for (int i = iCullStartY; i < iCullStartY + iTileCountY + 2; ++i)
	{
		for (int j = iCullStartX; j < iCullStartX + iTileCountX + 2; ++j)
		{
			iIndex = i * m_iTileX + j;

			if (0 > iIndex || (int)m_pTile.size() <= iIndex)
				continue;

			int iLeft = int(m_pTile[iIndex]->fX - TileCX * 0.5f - g_fScrollX);
			int iTop = int(m_pTile[iIndex]->fY - TileCY * 0.5f - g_fScrollY);

			BitBlt(hdc, iLeft, iTop, TileCX, TileCY,
				hMemDC, m_pTile[iIndex]->iDraw * TileCX, 0, SRCCOPY);

			iRenderCount++;
		}
	}


	TCHAR sz[32] = L"";
	swprintf_s(sz, L"RenderCount: %d", iRenderCount);
	TextOut(hdc, 100, 100, sz, lstrlen(sz));

}

void CTerrain::Release()
{
	for_each(m_pTile.begin(), m_pTile.end(), SafeDelete<TILE_INFO*>);
	m_pTile.clear();
}
