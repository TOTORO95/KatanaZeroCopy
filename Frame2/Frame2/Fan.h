#pragma once
#include "GameObject.h"
class CFan :
	public CGameObject
{
public:
	CFan();
	CFan( float fx,float fy);
	~CFan();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	void Animate();
};

