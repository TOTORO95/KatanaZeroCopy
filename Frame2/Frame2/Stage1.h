#pragma once
#include "Scene.h"
class CStage1 :public CScene
{
public:
	CStage1();
	~CStage1();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
private:
	virtual void Release() override;
};

