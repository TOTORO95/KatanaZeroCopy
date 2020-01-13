#pragma once
#include "GameObject.h"

class CTerrain : public CGameObject
{
public:
	CTerrain();
	virtual ~CTerrain();

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	vector<TILE_INFO*> GetTiles() { return m_vecTile; }
private:
	virtual void Release() override;

public:
	void TileChange(const POINT& pt, int iDrawID, int iOption = 0);
	bool SaveData(const wstring& wstrFilePath);
	bool LoadData(const wstring& wstrFilePath);

private:
	vector<TILE_INFO*>	m_vecTile;
	int m_iMaxX;
	int m_iMaxY;
};

