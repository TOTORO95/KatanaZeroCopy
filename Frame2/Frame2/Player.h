#pragma once
#include "GameObject.h"
class CPlayer :	public CGameObject
{
public:
	CPlayer();
	CPlayer(float fX,float fY);
	~CPlayer();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
private:
	virtual void Release() override;
public:
	void SetIsDbJump(bool val) { m_bDJump = val; }
	bool GetIsDown() { return m_bDown; }
	bool GetIsRoll() { return m_bRoll; }
	void SetIsOnFlat(bool val) { m_bOnFlat=val; }
	void SetDirection(int val) { m_iDirection = val; }
	void BeAttack(POINT targetInfo);
	
private:
	void KeyInput();
	void Attack();
	void Move();
	void Roll();
	void Jump();
	void WallJump();
	void ScrollOffset();
	void Animate();
	void ChangeState();
	void AniDirection();
	void BulletTime(HDC hdc);
	void RenderUI(HDC hdc);
	void KnockBack();
private:
	bool		m_bIsJump;
	
	float		m_fAtkRange;
	float		m_fAtkPower;

	wstring		m_wstrImageKey2;
	bool		m_bDown;
	bool		m_bRoll;
	bool		m_bOnFlat;
	bool		m_bDJump;
	bool		m_WallJump;
	int			m_iDirection;
	bool		m_bIsHit;


	//알파값변수
	BLENDFUNCTION	m_BlendFuntion;
	int				m_iAlpha;

	//Timer
	float m_fGameTimer;
	float m_fBulletGage;
};

