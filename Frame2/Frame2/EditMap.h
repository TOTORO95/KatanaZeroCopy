#pragma once
#include "Scene.h"
class CTerrain;
class CEditMap :
	public CScene
{
public:
	CEditMap();
	~CEditMap();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	
private:
	CTerrain* m_pTerrain;
	RECT m_rect;

};

