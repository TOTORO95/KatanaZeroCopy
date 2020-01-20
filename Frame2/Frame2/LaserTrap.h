#pragma once
#include "GameObject.h"
class LaserTrap :
	public CGameObject
{
public:
	//TODO: 레이저 트랩만들차례 Image폴더 오브젝트파일에 이미지있음
	//레이져는 라인으로 만들꺼임 불릿 색넣는거 참고!
	LaserTrap();
	~LaserTrap();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

