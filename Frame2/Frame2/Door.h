#pragma once
#include "GameObject.h"
class CDoor :
	public CGameObject
{
public:
	CDoor();
	CDoor(float fx,float fy,float fcx,float fcy);
	~CDoor();
public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:
	void SetNext(bool val) { m_bIsNext=val; }
	bool GetNext() { return m_bIsNext; }
private:
	
	bool			m_bIsNext;

	//알파값변수
	BLENDFUNCTION	m_BlendFuntion;
	float				m_fAlpha;

};

