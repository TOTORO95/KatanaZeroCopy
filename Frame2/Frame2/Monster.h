#pragma once
#include "GameObject.h"
class CMonster :
	public CGameObject
{
public:
	CMonster();
	CMonster(MONSTER_TYPE eMonster_Type,float fposX,float fPosY);
	~CMonster();

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
private:
	virtual void Release() override;


public:
	void LoadBmp();
	void InitMonster();
	void UpdateDetectRect();
	void Move();
	void BeAttack(POINT targetInfo);
	void KnockBack();
	virtual	void Animate();
	virtual void Attack();
	virtual void Patroll();
	virtual	void Pattern();
	virtual void ChangeState();
public:
	RECT GetDetectRect() { return  m_tDetectRect; }
	void SetTarget(POINT targetInfo, bool isTarget);
protected:
	POINT m_tFixPos;
	float m_fCount;
	POINT m_tTargetPos;
	bool m_bIsTargetSet;
	RECT m_tDetectRect;
	LONG m_iDetectRange;
	OBJ_DIRECTION m_eDirection;
	MONSTER_TYPE m_eMonsterType;
	wstring m_wstrLImageKey;
	wstring m_wstrRImageKey;
	float m_HitRange;
	int m_iAttackRate;
	
	bool m_bIsBettackEnd;
	FRAME m_tBeattackFrame;

};

