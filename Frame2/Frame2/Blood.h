#pragma once
#include "GameObject.h"
class CBlood :
	public CGameObject
{
public:
	CBlood();
	~CBlood();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

