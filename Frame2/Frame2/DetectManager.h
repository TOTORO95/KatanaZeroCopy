#pragma once
class CDetectManager
{
public:
	static CDetectManager* GetInstance();	
	void DestroyInstance();

private:
	static CDetectManager* m_pInstance;
public:
	CDetectManager();
	~CDetectManager();

public:
	static bool CollisionRect(OBJECT_LIST& dstList, OBJECT_LIST& srcList);

};

