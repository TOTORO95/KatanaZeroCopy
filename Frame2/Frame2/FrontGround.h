#pragma once
#include "GameObject.h"
class CFrontGround :
	public CGameObject
{
public:
	CFrontGround();
	CFrontGround(float x,float y);
	~CFrontGround();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

