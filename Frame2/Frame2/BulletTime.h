#pragma once
#include "GameObject.h"
class CBulletTime :
	public CGameObject
{
public:
	CBulletTime();
	~CBulletTime();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	void BulletTime(HDC hdc);

private:
	//알파값변수
	BLENDFUNCTION	m_BlendFuntion;
	int				m_iAlpha;
	float m_fBulletGage;


};

