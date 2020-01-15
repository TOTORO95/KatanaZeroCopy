#include "stdafx.h"
#include "BackGround.h"


CBackGround::CBackGround()
{

}


CBackGround::~CBackGround()
{
}

void CBackGround::Initialize()
{
	SetPos(WinCX*0.5, WinCY*0.5);
	SetSize(WinCX, WinCY);
	


}

int CBackGround::Update()
{
	UpdateWorldPos2();
	//cout <<"WorldPos"<< m_WorldPos.x<< " "<<  m_WorldPos.y << endl;
	
	//SetPos(m_WorldPos.x, m_WorldPos.y);
	UpdateRect2();
	//cout<<m_tRect

	return NO_EVENT;
}

void CBackGround::Render(HDC hdc)
{
	HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"bg");
	//HDC hBackDC= 
	NULL_CHECK(hMemDC);
	BitBlt(hdc,0, 0,WinCX,WinCY, hMemDC, WinCX*0.5- m_WorldPos.x, 0, SRCCOPY);
	

}

void CBackGround::Release()
{
}

