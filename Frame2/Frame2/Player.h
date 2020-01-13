#pragma once
#include "GameObject.h"
class CPlayer :	public CGameObject
{
public:
	CPlayer();
	~CPlayer();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
private:
	virtual void Release() override;
public:
	void SetIsDbJump(bool val) { m_bDJump = val; }
private:
	void KeyInput();
	void Jump();
	void Attack();
	void Move();
	void ScrollOffset();
	void Animate();
	void ChangeState();
	void AniDirection();

private:
	bool		m_bIsJump;
	float		m_fJumpForce;	// ��
	float		m_fJumpAcc;		// ���ӵ�
	float		m_fRightVal;
	float		m_fLeftVal;
	float		m_fAtkRange;
	float		m_fAtkPower;
	

	OBJ_STATE	m_ePreState;
	OBJ_STATE	m_eCurState;
	FRAME		m_tFrame;
	FRAME		m_tAtkFrame;
	bool		m_bDJump;
	wstring		m_wstrImageKey2;
	
};

