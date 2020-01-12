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
	// �ø� ����.
	// �ø�: �߷����� ���. (����ȭ)

	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"Tile");
	NULL_CHECK(hMemDC);
	
	int iRenderCount = 0;

	int iCullStartY = (int)g_fScrollY / TILECY;	//800/20    ���ȣ
	int iCullStartX = (int)g_fScrollX / TILECX;	//1280 /20  ����ȣ
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

	//// �ø� �ϱ� ��
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
	// ���콺 ��ŷ
	int i = pt.y / TILECY; // ��
	int j = pt.x / TILECX; // ��
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
	// WinAPI ���� ����
	HANDLE hFile = CreateFile(
		wstrFilePath.c_str(), /* ���� ��� */
		GENERIC_WRITE, /* ����� ��� */
		0, 
		0, 
		CREATE_ALWAYS, /* ���� ���� ��� */
		FILE_ATTRIBUTE_NORMAL, /* ������ ���� Ư�� */
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return false;

	DWORD dwBytes = 0;

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		// WinAPI ���� ���
		WriteFile(
			hFile,	/* ����� ������ �ڵ� */
			m_vecTile[i], /* ����� �������� �޸� �ּ� */
			sizeof(TILE_INFO), /* ����� �������� ũ�� */
			&dwBytes, /* �󸶸�ŭ ����� ����ƴ��� ����Ʈ ���� ��� */
			nullptr);
	}

	CloseHandle(hFile);

	return true;
}

bool CTerrain::LoadData(const wstring& wstrFilePath)
{
	// WinAPI ���� ����
	HANDLE hFile = CreateFile(
		wstrFilePath.c_str(), /* ���� ��� */
		GENERIC_READ, /* ����� ��� */
		0,
		0,
		OPEN_EXISTING, /* ���� ���� ��� */
		FILE_ATTRIBUTE_NORMAL, /* ������ ���� Ư�� */
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
		// WinAPI ���� �Է�
		ReadFile(
			hFile,	/* ����� ������ �ڵ� */
			&tInfo, /* �Է� ���� �������� �޸� �ּ� */
			sizeof(TILE_INFO), /* �Է� ���� �������� ũ�� */
			&dwBytes, /* �Է��� �����Ͱ� �󸶳� ���Ҵ��� ����Ʈ ���� ��� */
			nullptr);

		if (0 == dwBytes)
			break;

		m_vecTile.push_back(new TILE_INFO(tInfo));
	}

	CloseHandle(hFile);

	return true;
}
