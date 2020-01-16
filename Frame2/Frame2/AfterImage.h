#pragma once
#include "GameObject.h"
class CAfterImage :
	public CGameObject
{
public:
	CAfterImage();
	CAfterImage(float x,float y);
	~CAfterImage();
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void SetPlayerInfo(POINT val, FRAME frame_val);
	void SetImageKey(wstring val) { m_wstrImageKey2 = val; }
	void AniDriection(HDC hdc);

private:
	POINT		m_playerPos;
	POINT		m_OldPos;
	FRAME		m_tFrame;
	FRAME		m_tOldFrame;
	POINT		m_LerpPos[20];
	bool		m_bFalg;
	int			m_iCount;
	wstring		m_wstrImageKey2;

	//알파값변수
	BLENDFUNCTION	m_BlendFuntion;
	int				m_iAlpha;
};

/*
GdiTransparentBlt(hdc,
m_LerpPos[i].x - m_tInfo.fCX*0.8,
m_LerpPos[i].y - m_tInfo.fCY*0.9,
(int)m_tInfo.fCX * 1.6,
(int)m_tInfo.fCY * 1.8,
hMemDC,
m_tOldFrame.dwFrameX*i,
m_tOldFrame.dwFrameY,
m_tInfo.fCX,
m_tInfo.fCY,
RGB(0, 0, 0));




*/