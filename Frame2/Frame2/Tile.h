#pragma once
#include "GameObject.h"
class CTile: public CGameObject 
{
public:
	CTile();
	CTile(float fx, float fy,int option);
	~CTile();
	
	int GetTileOpt() { return m_iOption; }
	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;

	virtual int Update() override;

	virtual void Render(HDC hdc) override;

private:
	virtual void Release() override;
private:
	int m_iOption;

};

