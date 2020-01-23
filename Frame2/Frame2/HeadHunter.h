#pragma once
#include "Monster.h"
class CHeadHunter :
	public CMonster
{
public:
	CHeadHunter();
	CHeadHunter(float fPosX,float fPosY);
	~CHeadHunter();
private:
	virtual void Release() override;
public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	void Patroll() override;
	void BeAttack(POINT targetInfo) override;
	void DirectionAni();
private:
	void ChangeState()override;
	void Pattern()override;
	void Animate()override;
	void Laser(HDC hdc, float fDgree);
	void RightShot(HDC hdc);
	void AimLine(HDC hdc);
	void InitBMP();
	void VerticalLaser();
	void AimAni(HDC hdc);
	bool LoadBmp(HBITMAP &hmp, const wstring& wstrFilePath);
	BOOL RotateSizingImage(HDC hdc, HBITMAP hBmp, float fDgree, int ixRotateAxis, int iyRotateAxis, int ixDisplay, int iyDisplay,
		float dblSizeRatio = 1, HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);
private:
	FRAME	m_tHorizonLaserFrame;
	float	m_fLaserRate;
	int		m_iHP;
	int		m_iAimNum;
	float	m_fFrameCount[10];
private://레이저 비트맵
	HBITMAP m_hBitLaser[7];

};

