#pragma once

class CLine;
class CGameObject;
class CLineMgr
{
	DECLARE_SINGLETON(CLineMgr)

private:
	CLineMgr();
	~CLineMgr();

public:
	void Initialize();
	void Render(HDC hDC);
	bool CollisionLine(CGameObject* pObject, float* pOutY);

private:
	void Release();

private:
	list<CLine*>	m_LineList;
};

