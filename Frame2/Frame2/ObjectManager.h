#pragma once
// 중재자 패턴 (Mediator Pattern)
// 상호 의존도가 높은 M : N 관계를 M : 1 관계로 만들어서 의존도를 낮추는 디자인 패턴.
// 프로그램을 구성하는 오브젝트들은 서로 통신을 할 때 중재자를 통해서 수행한다.
// 즉, 오브젝트들은 서로를 몰라도 중재자만 알면 통신이 된다.
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
public: // 싱글톤 객체는 외부에서 생성과 소멸을 할 수 없다.
	CGameObject* GetPlayer() const;
	CGameObject* GetNearTarget(CGameObject* pObject, OBJ_TYPE eType);
	CGameObject* GetTerrain();
public:
	void AddObject(OBJ_TYPE eType, CGameObject* pObject);
	int Update();
	void Render(HDC hdc);
	void DeleteGroup(OBJ_TYPE eType);
private:
	void Release();

private:
	OBJECT_LIST		m_ObjectList[OBJ_END];
};

