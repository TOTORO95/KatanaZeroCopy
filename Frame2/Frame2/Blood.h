#pragma once
#include "GameObject.h"
class CBlood :
	public CGameObject
{
public:
	CBlood();
	CBlood(POINT pos,float fdgree);
	~CBlood();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	
private:
	void Animate();
	void DirectionAni();
private:
	int m_iBlood;
	HDC m_bloodHDC;
};

