#pragma once
#include "Monster.h"
class CPomp :
	public CMonster
{
public:
	CPomp();
	~CPomp();

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
private:
	virtual void Release() override;





};

