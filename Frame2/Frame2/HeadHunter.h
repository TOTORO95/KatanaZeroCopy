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
	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	void Patroll() override;
	void BeAttack(POINT targetInfo) override;
	void DirectionAni();
private:
	void KnockBack()override;
	void ChangeState()override;
	void Pattern()override;
	void Animate()override;
	void TakeOutGun();
	void Laser(HDC hdc, float fDgree);
	void RightShot(HDC hdc);
	void AimLine(HDC hdc);
	void InitBMP();
	void VerticalLaser();
	void AimAni(HDC hdc);
	void RecoveryIncible();
	bool LoadBmp(HBITMAP &hmp, const wstring& wstrFilePath);
	BOOL RotateSizingImage(HDC hdc, HBITMAP hBmp, float fDgree, int ixRotateAxis, int iyRotateAxis, int ixDisplay, int iyDisplay,
		float dblSizeRatio = 1, HBITMAP hMaskBmp = NULL, int ixMask = 0, int iyMask = 0);
private:
	FRAME	m_tHorizonLaserFrame;
	float	m_fLaserRate;
	int		m_iHP;
	int		m_iAimNum;
	float	m_fFrameCount[10];
	int		m_iPatternNum;
	float	m_fAimRate;
	bool	m_bIsAimEnd;
	bool	m_bIsGunReady;
	bool	m_bIsInvincibility;
	int		m_RecoveryRate;
	int		m_iRecoveryTime;
	bool	m_bIsHide;
	POINT	m_tGPatternPos[2];
private://������ ��Ʈ��
	HBITMAP m_hBitLaser[7];

};

