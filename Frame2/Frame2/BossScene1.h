#pragma once
#include "Scene.h"
class CBossScene1 :
	public CScene
{
public:
	CBossScene1();
	~CBossScene1();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
private:
	virtual void Release() override;

private:
	int m_iSpawn;
};

