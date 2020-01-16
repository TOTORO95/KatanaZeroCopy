#pragma once
#include "GameObject.h"
class CMonster :
	public CGameObject
{
public:
	CMonster();
	CMonster(float fposX,float fPosY);
	~CMonster();

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
private:
	virtual void Release() override;


public:
	void UpdateDetectRect();
	void Attack();
	void BeAttack();
	void Pattern();
public:
	RECT GetDetectRect() { return  m_tDetectRect; }
	void SetTarget(POINT targetInfo, bool isTarget);
private:
	POINT m_tFixPos;
	int m_iCount;
	POINT m_tTargetPos;
	bool m_bIsTargetSet;
	RECT m_tDetectRect;
	LONG m_iDetectRange;
	OBJ_DIRECTION m_eDirection;

};

