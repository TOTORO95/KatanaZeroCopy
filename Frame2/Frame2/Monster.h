#pragma once
#include "GameObject.h"
class CMonster :
	public CGameObject
{
public:
	CMonster();
	CMonster(float fposX,float fPosY);
	~CMonster();


	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;

	virtual int Update() override;

	virtual void Render(HDC hdc) override;

	virtual void Release() override;
	void Attack();
	void BeAttack();
	void Pattern();
	POINT m_tFixPos;
	int m_iCount;
};

