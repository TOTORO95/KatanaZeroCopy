#pragma once
#include "GameObject.h"
class CBackGround :
	public CGameObject
{
public:
	CBackGround();
	~CBackGround();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

