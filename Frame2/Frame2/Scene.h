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

protected:
	virtual void Release();
};


