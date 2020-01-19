#pragma once
class CScene
{
public:
	CScene();
	~CScene();
public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Render(HDC hDC) = 0;
	void SetMonCount(int val) { m_iMonCount = val; }
	int GetMonCount() { return m_iMonCount; }
	RECT GetDoor() { return m_tDoor; }

protected:
	virtual void Release();

protected:
	int m_iMonCount;
	bool m_bIsNest;
	RECT m_tDoor;

	//알파값변수
	BLENDFUNCTION	m_BlendFuntion;
	int				m_iAlpha;

};


