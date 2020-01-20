#pragma once
class CCollisionManager
{
public:
	static CCollisionManager* GetInstance();
	void DestroyInstance();

private:
	static CCollisionManager* m_pInstance;
public:
	CCollisionManager();
	~CCollisionManager();


public:
	static void	CollisionDoor(OBJECT_LIST& dstList, OBJECT_LIST& srcList);
	static void CollisionRect(OBJECT_LIST& dstList, OBJECT_LIST& srcList);
	static void CollisionRectEx(OBJECT_LIST& dstList, OBJECT_LIST& srcList);
	static void CollisionSphere(OBJECT_LIST& dstList, OBJECT_LIST& srcList);
	static bool CollisionRectTile(OBJECT_LIST& dstList, OBJECT_LIST& srcList);
	static bool CollisionRectKatana(RECT& katanaRect, OBJECT_LIST& srcList, POINT playerPos = {0, 0});

private:
	static bool IntersectSphere(CGameObject* pDest, CGameObject* pSource);
	static bool IntersectRectEx(CGameObject* pDest, CGameObject* pSource, float* pMoveX, float* pMoveY);
	
};

