#pragma once
#include "GameObject.h"
class CMonster2 :
	public CGameObject
{
public:
	CMonster2();
	CMonster2(MONSTER_TYPE eMonster_Type, float fposX, float fPosY);
	~CMonster2();


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
	virtual void BeAttack(POINT targetInfo);
	virtual void KnockBack();
	virtual	void Animate();
	virtual void Attack();
	virtual void Patroll();
	virtual	void Pattern();
	virtual void ChangeState();
	//void BloodAni();

public:
	RECT GetDetectRect() { return  m_tDetectRect; }
	MONSTER_TYPE GetMonType() { return m_eMonsterType; }
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

	float m_fBloodAngle;
	bool m_bIsBettackEnd;
	FRAME m_tBeattackFrame;
	int m_iBlood;
	POINT m_tOldPos;
	//HDC m_bloodHDC;
};

