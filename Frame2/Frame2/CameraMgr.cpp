#include "stdafx.h"
#include "Player.h"
#include "CameraMgr.h"

CCameraMgr* CCameraMgr::m_pInstance = nullptr;
CCameraMgr * CCameraMgr::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new CCameraMgr;
	return m_pInstance;
}

void CCameraMgr::DestroyInstance()
{
	if (m_pInstance != nullptr)
		delete m_pInstance;
	m_pInstance = nullptr;
}

CCameraMgr::CCameraMgr()	:
	m_ptrDestPoint(nullptr),
	m_bVibe(false)
{
	ZeroMemory(&m_curPoint, sizeof(m_curPoint));
}


CCameraMgr::~CCameraMgr()
{
	Release();
}

void CCameraMgr::initialize()
{
}

void CCameraMgr::Update()
{
	if (!m_bVibe)
	{
		m_curPoint.x = Lerpf(m_curPoint.x, m_ptrDestPoint->x, 0.07);
		m_curPoint.y = Lerpf(m_curPoint.y, m_ptrDestPoint->y, 0.07);
	}
	else
	{
		Vibe();
	}
}

POINT & CCameraMgr::GetCurPoint()
{
	return m_curPoint;
}

POINT & CCameraMgr::GetScrollPoint()
{
	g_fScrollX = m_curPoint.x - WinCX / 2;
	g_fScrollY = m_curPoint.y - WinCY / 2;
	return m_scrollPoint;
}

void CCameraMgr::SetDestPoint(POINT* _point)
{
	m_ptrDestPoint = _point;
}

void CCameraMgr::LookAtPlayer()
{
}

LONG CCameraMgr::Lerpf(float src, float dest, float t)
{
	LONG cur = src*(1 - t) + dest*t;
	return cur;
}

void CCameraMgr::VibeCamera(float _fPower)
{
	m_bVibe = true;
	m_fVibePower = _fPower;
}

void CCameraMgr::Vibe()
{
	m_fVibePower -=0.03;

	if (m_fVibePower < 0)
	{
		m_bVibe = false;
		return;
	}

	float fPower = m_fVibePower * 100;
	int iRot = (int)(m_fVibePower * 100) % 4;

	switch (iRot)
	{
	case 00:
		m_curPoint.x = Lerpf(m_curPoint.x, m_ptrDestPoint->x + fPower, 0.07);
		m_curPoint.y = Lerpf(m_curPoint.y, m_ptrDestPoint->y, 0.07);
		break;
	case 01:
		m_curPoint.x = Lerpf(m_curPoint.x, m_ptrDestPoint->x - fPower, 0.07);
		m_curPoint.y = Lerpf(m_curPoint.y, m_ptrDestPoint->y, 0.07);
		break;
	case 02:
		m_curPoint.x = Lerpf(m_curPoint.x, m_ptrDestPoint->x, 0.07);
		m_curPoint.y = Lerpf(m_curPoint.y, m_ptrDestPoint->y + fPower, 0.07);
		break;
	case 03:
		m_curPoint.x = Lerpf(m_curPoint.x, m_ptrDestPoint->x, 0.07);
		m_curPoint.y = Lerpf(m_curPoint.y, m_ptrDestPoint->y - fPower, 0.07);
		break;
	default:
		break;
	}
}

void CCameraMgr::Release()
{
}
