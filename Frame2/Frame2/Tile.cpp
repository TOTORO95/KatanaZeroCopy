#include "stdafx.h"
#include "Tile.h"


CTile::CTile()
{
	ZeroMemory(&m_tRect,sizeof(RECT));
	m_iOption = 0;
}

CTile::CTile(float fx,float fy, int option)
{
	SetPos(fx , fy );
	SetSize(TILECX, TILECY);
	m_iOption= option;
}


CTile::~CTile()
{
}

void CTile::Initialize()
{

}

int CTile::Update()
{

	CGameObject::UpdateRect();
	return NO_EVENT;
}

void CTile::Render(HDC hdc)
{
	Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CTile::Release()
{
}
