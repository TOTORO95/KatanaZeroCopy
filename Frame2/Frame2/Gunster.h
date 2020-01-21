#pragma once
#include "Monster.h"
class CGunster :
	public CMonster
{
public:
	CGunster();
	CGunster(float fPosX, float fPosY,int iAtkRate=40);
	~CGunster();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	void Patroll() override;
private:
	virtual void Release() override;

	void Attack() override;
	void ChangeState() override;

	
};

