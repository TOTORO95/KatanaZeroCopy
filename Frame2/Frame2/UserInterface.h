#pragma once
#include "GameObject.h"
class CUserInterface :
	public CGameObject
{
public:
	CUserInterface();
	~CUserInterface();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	//void BulletTime(HDC hdc);
	void RenderUI(HDC hdc);

	////���İ�����
	//BLENDFUNCTION	m_BlendFuntion;
	//int				m_iAlpha;

	//Timer
	float m_fGameTimer;
	float m_fBulletGage;

};

