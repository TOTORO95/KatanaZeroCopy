#pragma once
#include "GameObject.h"
class CUserInterface :
	public CGameObject
{
public:
	CUserInterface();
	~CUserInterface();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	//void BulletTime(HDC hdc);
	void RenderUI(HDC hdc);

	////알파값변수
	//BLENDFUNCTION	m_BlendFuntion;
	//int				m_iAlpha;

	//Timer
	float m_fGameTimer;
	float m_fBulletGage;

};

