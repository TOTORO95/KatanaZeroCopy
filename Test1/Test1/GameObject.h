#pragma once
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();


public:
	OBJTYPE GetObjType() const { return m_ObjType; }
	void SetObjType(OBJTYPE val) { m_ObjType = val; }
	INFO GetInfo() const { return m_tInfo; }
	void SetInfo(INFO _val) { m_tInfo = _val; }
	void SetPos(float _x, float _y) { m_tInfo.fPosX = _x, m_tInfo.fPosY = _y; }
	void SetSize(float _x, float _y) { m_tInfo.fCX = _x, m_tInfo.fCY = _y; }
	bool IsDead();
	void SetDead(bool _bool) { m_bIsDead = _bool; }
	bool GetIsColl() const { return m_bIsColl; }
	void SetIsColl(bool val) { m_bIsColl = val; }
	float Lerp(float value1, float value2, float amount);

public:

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Render(HDC _hDC) = 0;

protected:
	void SetAngle(INFO _info);
	void SetAngle(float _x, float _y);
	virtual void Release() = 0;
	void UpdateRect();
	

protected:
	INFO	m_tInfo;
	INFO	m_tAimInfo;
	RECT	m_tRect;
	RECT	m_tHitBox;
	OBJTYPE m_ObjType;

	float	m_fJumpForce;
	float	m_fJumpAcc;
	float	m_fSpeed;
	float	m_fRadian;
	float	m_fDegree;
	bool	m_bIsJump;
	bool	m_bIsDead;
	bool	m_bIsColl;
	float	m_fAtkRange;
};

