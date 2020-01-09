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

private:
	void KeyInput();
	void Jump();
	void ScrollOffset();
	void Animate();
	void ChangeState();

private:
	bool		m_bIsJump;
	float		m_fJumpForce;	// ��
	float		m_fJumpAcc;		// ���ӵ�
	float		m_fRightVal;
	float		m_fLeftVal;


	OBJ_STATE	m_ePreState;
	OBJ_STATE	m_eCurState;
	FRAME		m_tFrame;
};

