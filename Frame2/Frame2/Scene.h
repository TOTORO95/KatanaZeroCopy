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
	RECT GetDoorRect() { return m_tDoor; }
	bool GetisNext() { return m_bIsNext; }
	virtual void Release();
//protected:

protected:
	int m_iMonCount;
	bool m_bIsNext;
	RECT m_tDoor;
	OBJECT_LIST m_pMonList;
	OBJECT_LIST m_pDoor;
};


