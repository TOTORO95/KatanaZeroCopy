#pragma once
#include "Scene.h"
class CBossStage2 :
	public CScene
{
public:
	CBossStage2();
	~CBossStage2();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
private:
	CGameObject* pHeadHunter;
	CGameObject* pBG;
	CGameObject* pPlayer;
	OBJECT_LIST m_pMonlist;
};

