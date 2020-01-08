#pragma once
class CScene;
class CSceneManager
{
public:
	static CSceneManager* GetInstance();
	void DestroyInstance();
private:
	static CSceneManager* m_pInstance;
public:
	CSceneManager();
	~CSceneManager();

public:
	void SceneChange(SCENE_TYPE eCurType);
	void Update();
	void Render(HDC hDC);

private:
	void Release();

private:
	SCENE_TYPE	m_ePreSceneType;
	CScene*		m_pCurScene;
	int			m_iEvent;
};