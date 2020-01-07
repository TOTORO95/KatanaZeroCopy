#pragma once
#include "GameObject.h"

class CPlayer :
	public CGameObject
{
public:

	CPlayer();
	~CPlayer();

public:



public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hDC) override;
public:
	void KeyInput();
	void Jump();
	void Attack();
private:
	virtual void Release() override;
	void ScrollOffset();

private:
	int m_iCount;
	int m_iAnim;
	float m_fAtkPower;
	float fLeftVal;
	float fRightVal;
	Image* m_pImage;
	Gdiplus::Rect    m_gpRect;
	INFO m_LocInfo;

};

