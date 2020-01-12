#include "stdafx.h"
#include "Title.h"


CTitle::CTitle()
{
}


CTitle::~CTitle()
{
}

void CTitle::Initialize()
{
	CBmpManager::GetInstance()->LoadBmp(L"TitleBG", L"../Image/Logo/Title_BG.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"TitleGrass", L"../Image/Logo/Title_Plants1.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"PinkHead", L"../Image/Logo/Pink_Head2.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"TitleHead", L"../Image/Logo/Title_Head1.bmp");

	m_GrassFrame.dwFrameStart = 0;
	m_GrassFrame.dwFrameCount = 11;
	m_GrassFrame.dwFrameSpeed = 100;
	m_GrassFrame.dwFrameX = 0;
	m_GrassFrame.dwFrameY = 360;
	m_GrassFrame.dwOldTime = GetTickCount();
	
	m_PinkFrame.dwFrameStart = 0;
	m_PinkFrame.dwFrameCount = 3;
	m_PinkFrame.dwFrameSpeed = 300;
	m_PinkFrame.dwFrameX = 0;
	m_PinkFrame.dwFrameY = 200;
	m_PinkFrame.dwOldTime = GetTickCount();
}

int CTitle::Update()
{
	if (CKeyManager::GetInstance()->KeyDown(KEY_F))
	{
		CSceneManager::GetInstance()->SceneChange(SCENE_STAGE1);
		return CHANGE_SCENE;
	}
	if (CKeyManager::GetInstance()->KeyDown(KEY_R))
	{
		CSceneManager::GetInstance()->SceneChange(SCENE_EDIT);
		return CHANGE_SCENE;
	}

	GrassAnimate();
	PinkAnimate();


	return NO_EVENT;
}

void CTitle::Render(HDC hDC)
{//TODO: 현재 타이틀 나무 애니메이션 제작 그다음 게임스테이지시작!
	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"TitleBG");
	NULL_CHECK(hMemDC);
	BitBlt(hDC, 0, 0, WinCX, WinCY, hMemDC, 0, 0, SRCCOPY);
	hMemDC = CBmpManager::GetInstance()->GetMemDC(L"TitleGrass");
	NULL_CHECK(hMemDC);
	//hMemDC= CBmpManager::GetInstance()->

	
	//GdiTransparentBlt(hDC, 0, 0, 1280, 720, hMemDC2,
	//	m_GrassFrame.dwFrameX, m_GrassFrame.dwFrameY*m_GrassFrame.dwFrameStart, 640, 360, RGB(0, 0, 0));

	GdiTransparentBlt(hDC, 0, 0, 1280, 720, hMemDC,
			m_GrassFrame.dwFrameX, m_GrassFrame.dwFrameY*m_GrassFrame.dwFrameStart, 640, 360, RGB(55, 55, 55));

	hMemDC = CBmpManager::GetInstance()->GetMemDC(L"PinkHead");
	NULL_CHECK(hMemDC);

	//GdiTransparentBlt(hDC, 710, 250, 150, 200, hMemDC,
	//	0, 400, 150, 200, RGB(0, 0, 0));

	GdiTransparentBlt(hDC, 712, 250, 150, 200, hMemDC,
		m_PinkFrame.dwFrameX, m_PinkFrame.dwFrameY*m_PinkFrame.dwFrameStart, 150, 200, RGB(0, 0, 0));



}

void CTitle::GrassAnimate()
{
	DWORD dwCurTime = GetTickCount();

	if (m_GrassFrame.dwOldTime + m_GrassFrame.dwFrameSpeed <= dwCurTime)
	{
		++m_GrassFrame.dwFrameStart;
		m_GrassFrame.dwOldTime = dwCurTime;
	}

	if (m_GrassFrame.dwFrameStart == m_GrassFrame.dwFrameCount)
		m_GrassFrame.dwFrameStart = 0;


}

void CTitle::PinkAnimate()
{
	DWORD dwCurTime = GetTickCount();

	if (m_PinkFrame.dwOldTime + m_PinkFrame.dwFrameSpeed <= dwCurTime)
	{
		++m_PinkFrame.dwFrameStart;
		m_PinkFrame.dwOldTime = dwCurTime;
	}

	if (m_PinkFrame.dwFrameStart == m_PinkFrame.dwFrameCount)
		m_PinkFrame.dwFrameStart = 0;


}
void CTitle::Release()
{
}
