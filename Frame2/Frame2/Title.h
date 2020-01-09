#pragma once
#include "Scene.h"
class CTitle :
	public CScene
{
public:
	CTitle();
	~CTitle();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
private:
	void GrassAnimate();
	void PinkAnimate();
private:
	virtual void Release() override;

	FRAME m_GrassFrame;
	FRAME m_PinkFrame;
};

