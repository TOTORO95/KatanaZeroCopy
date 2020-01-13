#pragma once
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();
public:
	INFO& GetInfo() ;
	RECT& GetRect() ;
	void SetImageKey(const wstring& wstrImageKey);
	void SetPos(float x, float y);
	void SetSize(float x, float y);
	void SetAngle(float degree);
	void SetAngle(float _x, float _y);
	void SetIsColl(bool val) { m_bIsColl = val; }

	bool GetIsDead() { return m_bIsDead; }
	bool SetIsDead(bool _bool) { m_bIsDead = _bool; }
	bool GetIsAttk() const { return m_bIsAttk; }
	void SetIsAttk(bool val) { m_bIsAttk = val; }
	void SetFlat(float val) { m_flatY = val; }
	void SetWall(float val) { m_WallX = val; }
public:
	virtual void Initialize()=0;
	virtual int  Update()=0;
	virtual void Render(HDC hdc)=0;
protected:
	virtual void Release() = 0;
	void UpdateRect();

protected:
	INFO	m_tInfo;
	RECT	m_tRect;
	RECT	m_tHitBox;
	bool	m_bIsDead;
	float	m_fSpeed;
	float	m_fAngle;
	float   m_fRadian;
	wstring	m_wstrImageKey;
	bool	m_bIsAttk;
	bool	m_bIsColl;
	int		m_iCount;
	float	m_flatY;
	float	m_WallX;
};

