#pragma once
#include "Scene.h"
class CStage2 :
	public CScene
{
public:
	CStage2();
	~CStage2();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	void Release() override;
};

