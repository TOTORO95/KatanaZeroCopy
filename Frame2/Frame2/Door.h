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
	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:
	void SetNext(bool val) { m_bIsNext=val; }
	bool GetNext() { return m_bIsNext; }
private:
	
	bool			m_bIsNext;

	//���İ�����
	BLENDFUNCTION	m_BlendFuntion;
	float				m_fAlpha;

};

