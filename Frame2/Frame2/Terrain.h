#pragma once
#include "GameObject.h"

class CTerrain :
	public CGameObject
{
public:
	CTerrain();
	CTerrain(float fMapX, float fMapY);
	~CTerrain();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	vector<TILE_INFO*> m_pTile;
	int m_iTileX;
	int m_iTileY;
};

