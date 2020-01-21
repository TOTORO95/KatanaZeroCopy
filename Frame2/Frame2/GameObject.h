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
	wstring GetImageKey() {return m_wstrImageKey;}
	void SetPos(float x, float y);
	void SetSize(float x, float y);
	void SetAngle(float degree);
	void SetAngle(float _x, float _y);
	void SetIsColl(bool val) { m_bIsColl = val; }
	bool GetisCOll() { return m_bIsColl; }
	void SetWorldPos(POINT val) { m_WorldPos = val; }
	POINT GetWorldPos() { return m_WorldPos; }
	bool GetIsDead() { return m_bIsDead; }
	void SetIsDead(bool _bool) { m_bIsDead = _bool; }
	bool GetIsAttk() const { return m_bIsAttk; }
	void SetIsAttk(bool val) { m_bIsAttk = val; }
	void SetFlat(float val) { m_flatY = val; }
	void SetWall(float val) { m_WallX = val; }
	float Lerp(float src,float dest, float t);
	void SetState(OBJ_STATE val) { m_state = val; }
	FRAME GetFrame() { return m_tFrame; }
	RECT GetHitBox() { return m_tHitBox; }
	OBJ_TYPE GetObjType() { return m_eObjType; }
	void SetObjType(OBJ_TYPE val) { m_eObjType=val; }
	void SetStop(bool val) { m_bisStop = val; }
	bool GetStop() { return m_bisStop; }

public:
	virtual void Initialize()=0;
	virtual int  Update()=0;
	virtual void Render(HDC hdc)=0;
protected:
	virtual void Release() = 0;
	void UpdateRect();
	void UpdateWorldPos();
	void UpdateRect2();
	void UpdateWorldPos2();
	bool RotateSizingImage(HDC& hdc, HBITMAP hBmp,
		float dblAngle,
		int ixRotateAxis, int iyRotateAxis, int srcX, int srcY, int srcWidth, int srcHeight,
		int ixDisplay, int iyDisplay, tagRGBTRIPLE rgb,
		float dblSizeRatio = 1,
		HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);
protected:

	INFO		m_tInfo;
	POINT		m_WorldPos;
	OBJ_STATE	m_ePreState;
	OBJ_STATE	m_eCurState;
	RECT		m_tRect;
	RECT		m_tHitBox;
	bool		m_bIsDead;
	float		m_fSpeed;
	float		m_fAngle;
	float		m_fRadian;
	float		m_fJumpForce;	// Èû
	float		m_fJumpAcc;		// °¡¼Óµµ
	float		m_fRightVal;
	float		m_fLeftVal;
	wstring		m_wstrImageKey;
	bool		m_bIsAttk;
	bool		m_bIsColl;
	int			m_iCount;
	float		m_flatY;
	float		m_WallX;
	OBJ_TYPE	m_eObjType;
	OBJ_STATE	m_state;
	FRAME		m_tAtkFrame;
	FRAME		m_tFrame;
	FRAME		m_tBloodFrame;
	POINT		m_OldScroll;
	bool		m_bisStop;
};

