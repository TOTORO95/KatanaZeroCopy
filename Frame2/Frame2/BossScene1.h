#pragma once
#include "Scene.h"
class CBossScene1 :
	public CScene
{
public:
	CBossScene1();
	~CBossScene1();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
private:
	virtual void Release() override;
private:
	int m_iSpawn;
	CGameObject* pHeadHunter;
	int	m_iExplosionRate;
	CGameObject* pBG;
	OBJECT_LIST m_pMonlist;
	CGameObject* pPlayer;
};

