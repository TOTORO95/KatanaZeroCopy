#pragma once
#include "Monster.h"
class CGrunt :
	public CMonster
{
public:
	CGrunt();
	CGrunt(float fposX, float fPosY);
	~CGrunt();

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
private:
	virtual void Release() override;
	void Attack() override;
	void ChangeState() override;

};

