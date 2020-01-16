#include "stdafx.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Tile.h"
#include "Player.h"
#include "Bullet.h"
CCollisionManager* CCollisionManager::m_pInstance = nullptr;
CCollisionManager * CCollisionManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new CCollisionManager;
	return m_pInstance;
}

void CCollisionManager::DestroyInstance()
{
	if (m_pInstance != nullptr)
		delete m_pInstance;
	m_pInstance = nullptr;
}

CCollisionManager::CCollisionManager()
{
}


CCollisionManager::~CCollisionManager()
{
}

void CCollisionManager::CollisionBullet(OBJECT_LIST& dstList, OBJECT_LIST& srcList)
{
	for (auto pDest : dstList)
	{
		for (auto pSrc : srcList)
		{
			RECT rc = {};

			// 두 사각형이 교차되었는지 판별하는 함수. 교차됐으면 TRUE, 아니면 FALSE 반환.
			// 두 사각형이 교차되었을 때 겹친 영역에 또다른 사각형이 만들어진다. 
			// 이 겹친 사각형을 첫번째 인자로 반환한다.
			if (IntersectRect(&rc, &pDest->GetRect(), &pSrc->GetRect()))
			{
				cout << "총알 충돌" << endl;
				pDest->SetIsDead(true);
				//pSrc->IsDead();
			}
		}
	}
}
void CCollisionManager::CollisionRect(OBJECT_LIST& dstList, OBJECT_LIST& srcList)
{
	float fMoveX = 0.f, fMoveY = 0.f;

	for (auto pDest : dstList)
	{
		for (auto pSrc : srcList)
		{
			if (IntersectRectEx(pDest, pSrc, &fMoveX, &fMoveY))
			{
				float fX = pSrc->GetInfo().fX;
				float fY = pSrc->GetInfo().fY;

				if (fMoveX > fMoveY) // Y축으로 밀어냄
				{
					if (pDest->GetInfo().fY < fY)
						pSrc->SetPos(fX, fY + fMoveY);
					else
						pSrc->SetPos(fX, fY - fMoveY);
				}
				else // X축으로 밀어냄
				{
					if (pDest->GetInfo().fX < fX)
						pSrc->SetPos(fX + fMoveX, fY);
					else
						pSrc->SetPos(fX - fMoveX, fY);
				}
			}
		}
	}
}

void CCollisionManager::CollisionRectEx(OBJECT_LIST& dstList, OBJECT_LIST& srcList)
{
	float fMoveX = 0.f, fMoveY = 0.f;
	for (auto pSrc : srcList)
	{
		bool m_flatCOll = false;
		bool m_wallCOll = false;
		bool m_OnFlat = false;
		for (auto pDest : dstList)
		{
			if (IntersectRectEx(pDest, pSrc, &fMoveX, &fMoveY))
			{
				float fX = pSrc->GetInfo().fX;
				float fY = pSrc->GetInfo().fY;

				if (fMoveX > fMoveY) // Y축으로 밀어냄
				{
					if (dynamic_cast<CTile*>(pDest)->GetTileOpt() == 1)
					{
						//cout << "플랫" << endl;
						if (pDest->GetInfo().fY < fY)//타일이 플레이어보다위에잇음
						{
							pSrc->SetPos(fX, fY + fMoveY+8);
							
						}
						else
						{
							m_OnFlat = true;
							m_flatCOll = true;
							pSrc->SetPos(fX, fY - fMoveY);
							pSrc->SetFlat(pDest->GetInfo().fY);
							
							//return;
						}
					}
					if (dynamic_cast<CTile*>(pDest)->GetTileOpt() == 2 &&
						!(dynamic_cast<CPlayer*>(pSrc)->GetIsDown()))
					{
						//cout << "플랫" << endl;
						if (pDest->GetInfo().fY < fY)//타일이 플레이어보다위에잇음
						{
							//pSrc->SetPos(fX, fY + fMoveY + 8);
						}
						else
						{
							m_flatCOll = true;
							pSrc->SetPos(fX, fY - fMoveY);
							pSrc->SetFlat(pDest->GetInfo().fY);
							//return;
						}
					}
				}
				else // X축으로 밀어냄
				{
					if (dynamic_cast<CTile*>(pDest)->GetTileOpt() == 4)
					{
						//cout << "Wall" << endl;
						pSrc->SetWall(pDest->GetInfo().fX);
						m_wallCOll = true;
						dynamic_cast<CPlayer*>(pSrc)->SetIsDbJump(m_wallCOll);
						//cout << "벽" << endl;
						if (pDest->GetInfo().fX< fX)
						{
							//cout << "player= x"<<fX <<"  "<<fX + fMoveX << endl;
							pSrc->SetPos(fX + fMoveX + 2, fY);
							dynamic_cast<CPlayer*>(pSrc)->SetDirection(0);
						}
						else
						{
							pSrc->SetPos(fX - fMoveX-2, fY);
							dynamic_cast<CPlayer*>(pSrc)->SetDirection(1);

						}
					}
					if (dynamic_cast<CTile*>(pDest)->GetTileOpt() == 3)
					{
						//cout << "Wall" << endl;
						pSrc->SetWall(pDest->GetInfo().fX);
						m_wallCOll = true;
						//cout << "벽" << endl;
						if (pDest->GetInfo().fX< fX)
						{
							pSrc->SetPos(fX + fMoveX+2, fY);
						}
						else
						{
							pSrc->SetPos(fX - fMoveX-2, fY);
						}
					}
				}
				//cout << "충돌" << endl;
			}

		}
		pSrc->SetIsColl(m_flatCOll);
	
		dynamic_cast<CPlayer*>(pSrc)->SetIsOnFlat(m_OnFlat);

	}

}
//void CCollisionManager::CollisionSphere(RECT& katanaRect, OBJECT_LIST& srcList)
//{
//	
//	for (auto pSrc : srcList)
//	{
//		if (IntersectSphere(pDest, pSrc))
//		{
//			cout << "총알 충돌" << endl;
//			//pDest->SetIsDead(true);
//			pSrc->SetIsDead(true);
//		}
//	}
//	
//}
void CCollisionManager::CollisionSphere(OBJECT_LIST& dstList, OBJECT_LIST& srcList)
{
	for (auto pDest : dstList)
	{
		for (auto pSrc : srcList)
		{
			if (IntersectSphere(pDest, pSrc))
			{
				cout << "총알 충돌" << endl;
				//pDest->SetIsDead(true);
				pSrc->SetIsDead(true);
			}
		}
	}
}

bool CCollisionManager::CollisionRectTile(OBJECT_LIST & dstList, OBJECT_LIST & srcList)
{
	float fMoveX = 0.f, fMoveY = 0.f;

	for (auto pSrc : srcList)
	{
		for (auto pDest : dstList)
		{
			float fX = pSrc->GetInfo().fX;
			float fY = pSrc->GetInfo().fY;
			RECT rc = {};
			if (IntersectRect(&rc, &pDest->GetRect(), &pSrc->GetRect()))
			{
				if (dynamic_cast<CTile*>(pDest)->GetTileOpt() == 4)
				{
					//cout << "Wall" << endl;
					pSrc->SetWall(pDest->GetInfo().fX);
					dynamic_cast<CPlayer*>(pSrc)->SetIsDbJump(true);
				}
				if (dynamic_cast<CTile*>(pDest)->GetTileOpt() == 1)
				{
					pSrc->SetFlat(pDest->GetInfo().fY);
					pSrc->SetIsColl(true);
					return true;
				}

				
			}
		}
		dynamic_cast<CPlayer*>(pSrc)->SetIsDbJump(false);
		pSrc->SetIsColl(false);
		return false;
	}
	return false;
}

bool CCollisionManager::CollisionRectKatana(RECT & katanaRect, OBJECT_LIST & srcList)
{
	for (auto pSrc : srcList)
	{
		float fX = pSrc->GetInfo().fX;
		float fY = pSrc->GetInfo().fY;
		RECT rc = {};
		if (IntersectRect(&rc, &katanaRect, &pSrc->GetRect()))
		{
			dynamic_cast<CBullet*>(pSrc)->ReflectionBullet();
			cout << "카타나 충돌" << endl;
		}

	}
	return false;
}

bool CCollisionManager::IntersectSphere(CGameObject* pDest, CGameObject* pSource)
{
	// 원충돌
	// 두 원의 반지름 합을 구한다. r1 + r2
	// 두 원의 중점 간 거리를 구한다. d
	// r1 + r2 >= d 조건을 만족하면 TRUE

	float r1 = pDest->GetInfo().fCX * 0.5f;
	float r2 = pSource->GetInfo().fCX * 0.5f;

	float w = pDest->GetWorldPos().x - pSource->GetWorldPos().x;
	float h = pDest->GetWorldPos().y - pSource->GetWorldPos().y;

	// sqrtf: 제곱근 구하는 함수. <cmath>에서 제공.
	float d = sqrtf(w * w + h * h);

	return r1 + r2 >= d;
}


bool CCollisionManager::IntersectRectEx(CGameObject* pDest, CGameObject* pSource, float* pMoveX, float* pMoveY)
{
	// x축의 반지름 합과 거리를 구한다.
	// 이 때 x축의 반지름 합이 x축의 거리보다 크면 x쪽으로 겹쳤다.
	float fSumX = pDest->GetInfo().fCX * 0.5f + pSource->GetInfo().fCX * 0.5f;
	float fDistX = fabs(pDest->GetWorldPos().x - pSource->GetWorldPos().x);

	// y축의 반지름 합과 거리를 구한다.
	// 이 때 y축의 반지름 합이 y축의 거리보다 크면 y쪽으로 겹쳤다.
	float fSumY = pDest->GetInfo().fCY * 0.5f + pSource->GetInfo().fCY * 0.5f;
	float fDistY = fabs(pDest->GetInfo().fY - pSource->GetInfo().fY);

	if (fSumX >= fDistX && fSumY >= fDistY)
	{
		// 겹친영역의 크기 구하기.
		*pMoveX = fSumX - fDistX;
		*pMoveY = fSumY - fDistY;
		return true;
	}

	return false;
}
