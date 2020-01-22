#pragma once
#include "GameObject.h"
class CFrontGround :
	public CGameObject
{
public:
	CFrontGround();
	CFrontGround(float x,float y);
	~CFrontGround();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

