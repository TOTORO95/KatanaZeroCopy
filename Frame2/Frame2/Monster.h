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
	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
private:
	virtual void Release() override;


public:
	void LoadBmp();
	void UpdateDetectRect();
	void Move();
	void Attack();
	void BeAttack(POINT targetInfo);
	void KnockBack();
	void Pattern();
	void Animate();
	void ChangeState();

public:
	RECT GetDetectRect() { return  m_tDetectRect; }
	void SetTarget(POINT targetInfo, bool isTarget);
private:
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
	
};

