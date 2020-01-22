#pragma once
#include "GameObject.h"
class CBulletTime :
	public CGameObject
{
public:
	CBulletTime();
	~CBulletTime();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	void BulletTime(HDC hdc);

private:
	//���İ�����
	BLENDFUNCTION	m_BlendFuntion;
	int				m_iAlpha;
	float m_fBulletGage;


};

