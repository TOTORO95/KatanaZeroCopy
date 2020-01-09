#pragma once

class CLine;
class CGameObject;
class CLineManager
{
public:
	static CLineManager* GetInstance();
	void DestroyInstance();
private:
	static CLineManager* m_pInstance;
private:
	CLineManager();
	~CLineManager();

public:
	void Initialize();
	void Render(HDC hDC);
	bool CollisionLine(CGameObject* pObject, float* pOutY);

private:
	void Release();

private:
	list<CLine*>	m_LineList;
};

