#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
	: m_dwKeyDown(0), m_dwKeyUp(0), m_dwCurKey(0)
{

}
CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Update()
{
	m_dwCurKey = 0;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwCurKey |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwCurKey |= KEY_DOWN;
	if (GetAsyncKeyState('A') & 0x8000)
		m_dwCurKey |= KEY_LEFT;
	if (GetAsyncKeyState('D') & 0x8000)
		m_dwCurKey |= KEY_RIGHT;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwCurKey |= KEY_SPACE;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwCurKey |= KEY_RETURN;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwCurKey |= KEY_LBUTTON;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwCurKey |= KEY_RBUTTON;
	if (GetAsyncKeyState('A') & 0x8000)
		m_dwCurKey |= KEY_A;
	if (GetAsyncKeyState('S') & 0x8000)
		m_dwCurKey |= KEY_S;
}

bool CKeyMgr::KeyDown(DWORD dwKey)
{
	// ���� ������ ���� ���� ������ �� TRUE
	if (!(m_dwKeyDown & dwKey) && (m_dwCurKey & dwKey))
	{
		m_dwKeyDown |= dwKey;
		return true;
	}
	// ���� ������ �ְ� ���� ������ �ʾ��� �� FALSE
	if ((m_dwKeyDown & dwKey) && !(m_dwCurKey & dwKey))
	{
		m_dwKeyDown ^= dwKey;

		return false;
	}

	return false;
}

bool CKeyMgr::KeyUp(DWORD dwKey)
{
	// ���� ������ �ְ� ���� ������ �ʾ��� �� TRUE
	if ((m_dwKeyUp & dwKey) && !(m_dwCurKey & dwKey))
	{
		m_dwKeyUp ^= dwKey;
		return true;
	}
	// ���� ������ ���� ���� ������ �� FALSE
	if (!(m_dwKeyUp & dwKey) && (m_dwCurKey & dwKey))
	{
		m_dwKeyUp |= dwKey;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyPressing(DWORD dwKey)
{
	if (m_dwCurKey & dwKey)
		return true;

	return false;
}

CKeyMgr* CKeyMgr::GetInstance()
{
	if (nullptr == m_pInstance)
		m_pInstance = new CKeyMgr;

	return m_pInstance;
}

void CKeyMgr::DestroyInstance()
{
	if (m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}