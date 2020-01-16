#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}

CBullet::CBullet(float x, float y,POINT targetpos)
{
	SetPos(x, y);
	SetSize(10, 10);
	SetPosVector(targetpos);
	//TODO: �Ѿ� �������!!!!���� setposvector �̿��ؼ� ���� �� ���� ������Ʈ���� �������� �Ѿ˳������ϰ� monster�� �Ѿ� ������� �߰�!
}


CBullet::~CBullet()
{
}

void CBullet::Initialize()
{
	m_fSpeed = 15;
}

int CBullet::Update()
{
	UpdateWorldPos();
	UpdateRect2();

	return NO_EVENT;
}

void CBullet::Render(HDC hdc)
{
	Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}

void CBullet::SetPosVector(POINT targetPos)
{
	SetAngle(targetPos.x, targetPos.y);
	m_posVector.x = cosf(m_fRadian);
	m_posVector.y = sinf(m_fRadian);

}
