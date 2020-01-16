#pragma once
#include "GameObject.h"
class CBullet : public CGameObject
{
public:
	CBullet();
	CBullet(float x,float y,POINT targetpos);
	~CBullet();
public:
	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
private:
	virtual void Release() override;

public:
	void SetPosVector(POINT targetPos);
private:
	POINT m_posVector;


};

