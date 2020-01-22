#include "stdafx.h"
#include "Tile.h"


CTile::CTile()
{
	ZeroMemory(&m_tRect,sizeof(RECT));
}

CTile::CTile(float fx,float fy, int option)
{
	SetPos(fx , fy );
	SetSize(TILECX, TILECY);
	m_iOption = option;

}


CTile::~CTile()
{
}

void CTile::Initialize()
{

}

int CTile::Update()
{
	//m_tInfo.fX -= g_fScrollX;
	UpdateWorldPos2();

	CGameObject::UpdateRect2();
	return NO_EVENT;
}

void CTile::Render(HDC hdc)
{
	if (CKeyManager::GetInstance()->KeyPressing(KEY_O))
	{

		GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, TILECX, TILECY, 
			CBmpManager::GetInstance()->GetMemDC(L"Tile"), m_iOption* TILECX, 0,
			TILECX, TILECY, RGB(0, 0, 0));

	}

		//Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		//GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom,
		//	CBmpManager::GetInstance()->GetMemDC(L"Tile"), TILECX*m_iOption, 0, TILECX, TILECY, RGB(0, 0, 0));

}

void CTile::Release()
{
}
