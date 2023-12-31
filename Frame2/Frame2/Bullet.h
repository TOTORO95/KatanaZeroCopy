#pragma once
#include "GameObject.h"
class CBullet : public CGameObject
{
public:
	CBullet();
	CBullet(float x,float y,POINT targetpos);
	~CBullet();
public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
private:
	virtual void Release() override;

public:
	void SetPosVector(POINT targetPos);
	void ReflectionBullet();
	void Animate();
	BULLET_TAG GetBulletTag() { return m_eBulletTag; }
private:
	POINT m_tEffectPos;
	POINT m_posVector;
	bool m_Reverce;
	FRAME m_frame;
	POINT m_tOldPos;
	BULLET_TAG m_eBulletTag;
};


