#pragma once
#include "GameObject.h"
class CPlayer :	public CGameObject
{
public:
	CPlayer();
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

private:
	bool		m_bIsJump;
	float		m_fJumpForce;	// 힘
	float		m_fJumpAcc;		// 가속도
	float		m_fRightVal;
	float		m_fLeftVal;
	float		m_fAtkRange;
	float		m_fAtkPower;

	OBJ_STATE	m_ePreState;
	OBJ_STATE	m_eCurState;
	wstring		m_wstrImageKey2;
	bool		m_bDown;
	bool		m_bRoll;
	bool		m_bOnFlat;
	bool		m_bDJump;
	bool		m_WallJump;
	int			m_iDirection;
	//알파값변수
	BLENDFUNCTION	m_BlendFuntion;
	int				m_iAlpha;
};

