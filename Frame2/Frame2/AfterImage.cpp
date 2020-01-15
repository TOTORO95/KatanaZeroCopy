#include "stdafx.h"
#include "AfterImage.h"


CAfterImage::CAfterImage()
{
}

CAfterImage::CAfterImage(float x, float y)
{
	SetPos(x, y);
}


CAfterImage::~CAfterImage()
{
}

void CAfterImage::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_tFrame.dwFrameStart = 0;
	m_tFrame.dwFrameCount = 4;
	m_tFrame.dwFrameX = 0;
	m_tFrame.dwFrameY = 0;
	m_tFrame.dwFrameSpeed = 200; // 0.2초 간격
	m_tFrame.dwOldTime = GetTickCount();

	CBmpManager::GetInstance()->LoadBmp(L"RShadow1", L"../Image/Player/AfterImage/RAfterImage1.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"RShadow2", L"../Image/Player/AfterImage/RAfterImage2.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"RShadow3", L"../Image/Player/AfterImage/RAfterImage3.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"RShadow4", L"../Image/Player/AfterImage/RAfterImage3.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"RShadow5", L"../Image/Player/AfterImage/RAfterImage3.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"RShadow6", L"../Image/Player/AfterImage/RAfterImage3.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"RShadow7", L"../Image/Player/AfterImage/RAfterImage3.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"RShadow8", L"../Image/Player/AfterImage/RAfterImage3.bmp");
	
	CBmpManager::GetInstance()->LoadBmp(L"LShadow1", L"../Image/Player/AfterImage/LAfterImage1.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LShadow2", L"../Image/Player/AfterImage/LAfterImage2.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LShadow3", L"../Image/Player/AfterImage/LAfterImage3.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LShadow4", L"../Image/Player/AfterImage/LAfterImage3.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LShadow5", L"../Image/Player/AfterImage/LAfterImage3.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LShadow6", L"../Image/Player/AfterImage/LAfterImage3.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LShadow7", L"../Image/Player/AfterImage/LAfterImage3.bmp");
	CBmpManager::GetInstance()->LoadBmp(L"LShadow8", L"../Image/Player/AfterImage/LAfterImage3.bmp");

	m_OldPos = { (LONG)m_tInfo.fX,(LONG)m_tInfo.fY };
	m_playerPos = { (LONG)m_tInfo.fX,(LONG)m_tInfo.fY };
	m_tOldFrame = m_tFrame;
	m_bFalg = false;
	m_iCount = 0;

}

int CAfterImage::Update()
{
	UpdateWorldPos2();
	//switch (m_tFrame.dwFrameCount)
	//{
	//case 11:
	//	cout << "IDLE상태" << endl;
	//	break;
	//case 10:
	//	cout << "RUN상태" << endl;
	//	break;
	//case 7:
	//	cout << "ATTACK상태" << endl;
	//	break;

	//default:
	//	break;
	//}

	//cout << m_playerPos.x << "  " << m_playerPos.y << endl;
	//cout << m_OldPos.x << "  " << m_OldPos.y << endl;


	for (int i = 0; i < m_tFrame.dwFrameCount; i++)
	{
		m_LerpPos[i].x = Lerp(m_OldPos.x, m_playerPos.x, (float)i / (float)(m_tFrame.dwFrameCount));
		m_LerpPos[i].y = Lerp(m_OldPos.y, m_playerPos.y, (float)i / (float)(m_tFrame.dwFrameCount));
	}
	m_OldPos = m_playerPos;
	if (m_tFrame.dwFrameCount != m_tOldFrame.dwFrameCount)
		m_bFalg = true;

	return NO_EVENT;
}

void CAfterImage::Render(HDC hdc)
{
	m_iCount++;
	CGameObject::UpdateRect2();
	if(m_bFalg)
	{

		AniDriection(hdc);
	
		m_tOldFrame = m_tFrame;
		if (m_iCount % 30 == 0)
		{
			m_bFalg = false;
			m_iCount = 0;
		}
	}

}

void CAfterImage::Release()
{
}

void CAfterImage::SetPlayerInfo(POINT val, FRAME frame_val)
{
	m_playerPos.x = val.x,
	m_playerPos.y = val.y; 
	m_tFrame = frame_val;
}

void CAfterImage::AniDriection(HDC hdc)
{
	if (m_wstrImageKey == L"Player_R")
	{
		HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"RShadow1");
		for (int i = 0; i < m_tOldFrame.dwFrameCount - 1; i++)
		{
			switch (i)
			{
			case 1:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"RShadow2");
				break;
			case 2:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"RShadow3");
				break;
			case 3:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"RShadow4");
				break;
			case 4:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"RShadow5");
				break;
			case 5:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"RShadow6");
				break;
			case 6:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"RShadow7");
				break;
			case 7:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"RShadow8");
				break;
			case 8:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"RShadow9");
				break;
			default:
				break;
			}
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
		}
	}
	else
	{
		HDC hMemDC = CBmpManager::GetInstance()->GetMemDC(L"LShadow1");
		for (int i = 0; i < m_tOldFrame.dwFrameCount - 1; i++)
		{
			switch (i)
			{
			case 1:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"LShadow2");
				break;
			case 2:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"LShadow3");
				break;
			case 3:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"LShadow4");
				break;
			case 4:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"LShadow5");
				break;
			case 5:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"LShadow6");
				break;
			case 6:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"LShadow7");
				break;
			case 7:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"LShadow8");
				break;
			case 8:
				hMemDC = CBmpManager::GetInstance()->GetMemDC(L"LShadow9");
				break;
			default:
				break;
			}
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
		}
	}
}
