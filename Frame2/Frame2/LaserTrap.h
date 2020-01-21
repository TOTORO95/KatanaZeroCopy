#pragma once
#include "GameObject.h"
class LaserTrap :
	public CGameObject
{
public:
	//TODO: ������ Ʈ���������� Image���� ������Ʈ���Ͽ� �̹�������
	//�������� �������� ���鲨�� �Ҹ� ���ִ°� ����!
	LaserTrap();
	LaserTrap(float fx,float fy,float fLaserRange= 520);
	~LaserTrap();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
private:
	void Animate();


private:
	POINT m_OldScroll;
	float m_fAtkRange;
};

