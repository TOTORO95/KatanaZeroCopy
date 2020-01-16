#pragma once

class CCameraMgr
{
public:
	static CCameraMgr* GetInstance();
	void DestroyInstance();
private:
	static CCameraMgr* m_pInstance;

private:
	CCameraMgr();
	~CCameraMgr();

public:
	void initialize();
	void Update();
	
public:
	POINT& GetCurPoint();
	POINT& GetScrollPoint();

public:
	void SetDestPoint(POINT* _point);
	void VibeCamera(float _fPower);
	void LookAtPlayer();
	LONG Lerpf(float src, float dest, float t);
private:
	void Release();
	void Vibe();

private:
	bool	m_bVibe;
	float	m_fVibePower;

	POINT m_curPoint;
	POINT m_scrollPoint;
	POINT* m_ptrDestPoint;
};

