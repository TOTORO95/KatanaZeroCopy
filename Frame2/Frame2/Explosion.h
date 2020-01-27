#pragma once
#include "GameObject.h"
class CExplosion :
	public CGameObject
{
public:
	CExplosion();
	CExplosion(float fx, float fy);
	~CExplosion();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	void Animate();
	

private:
	bool m_bIsEnd;

};

