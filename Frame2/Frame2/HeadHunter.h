#pragma once
#include "Monster.h"
class CHeadHunter :
	public CMonster
{
public:
	CHeadHunter();
	CHeadHunter(float fPosX,float fPosY);
	~CHeadHunter();
public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	void Patroll() override;
private:
	virtual void Release() override;
private:
	void ChangeState()override;
	void Pattern()override;
	void RightShot(HDC hdc);
	void Animate()override;
	void AimLine(HDC hdc);
private:
	FRAME m_tLaserFrame;
	float m_fLaserRate;
};

