#pragma once
// ������ ���� (Mediator Pattern)
// ��ȣ �������� ���� M : N ���踦 M : 1 ����� ���� �������� ���ߴ� ������ ����.
// ���α׷��� �����ϴ� ������Ʈ���� ���� ����� �� �� �����ڸ� ���ؼ� �����Ѵ�.
// ��, ������Ʈ���� ���θ� ���� �����ڸ� �˸� ����� �ȴ�.
class CGameObject;
class CObjectManager
{
public:
	static CObjectManager* GetInstance();
	void DestroyInstance();
private:
	static CObjectManager*	m_pInstance;

public:
	CObjectManager();
	~CObjectManager();
public: // �̱��� ��ü�� �ܺο��� ������ �Ҹ��� �� �� ����.
	CGameObject* GetPlayer() const;
	CGameObject* GetNearTarget(CGameObject* pObject, OBJ_TYPE eType);
	CGameObject* GetTerrain();
	OBJECT_LIST GetObjList(OBJ_TYPE eType);
public:
	void AddObject(OBJ_TYPE eType, CGameObject* pObject);
	int Update();
	void Render(HDC hdc);
	void DeleteGroup(OBJ_TYPE eType);
	void Release();
	
private:
	int m_iCount;
	OBJECT_LIST		m_ObjectList[OBJ_END];
};

