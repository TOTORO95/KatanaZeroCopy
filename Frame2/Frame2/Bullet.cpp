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
	//TODO: 총알 만드는중!!!!현재 setposvector 이용해서 각도 줌 이제 업데이트에서 방향으로 총알나가게하고 monster에 총알 쏘는패턴 추가!
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
