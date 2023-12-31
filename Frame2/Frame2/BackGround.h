#pragma once
#include "GameObject.h"
class CBackGround :
	public CGameObject
{
public:
	CBackGround();
	CBackGround(wstring backGround);
	~CBackGround();
	bool GetTrigger() { return m_Trigger; }
	void SetTrigger(bool val) { m_Trigger = val; }
	
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	
	
	bool m_Trigger;
	
};

