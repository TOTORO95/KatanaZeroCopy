#include "stdafx.h"
#include "SceneManager.h"
#include "MyEdit.h"
#include "Logo.h"
#include "Title.h"
#include "Stage1.h"
CSceneManager* CSceneManager::m_pInstance = nullptr;
CSceneManager * CSceneManager::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new CSceneManager;
	return m_pInstance;
}

void CSceneManager::DestroyInstance()
{
	if (m_pInstance != nullptr)
		delete m_pInstance;
	m_pInstance = nullptr;
}

CSceneManager::CSceneManager()
	: m_ePreSceneType(SCENE_END),
	m_pCurScene(nullptr),
	m_iEvent(NO_EVENT)
{
}


CSceneManager::~CSceneManager()
{
	Release();
}

void CSceneManager::SceneChange(SCENE_TYPE eCurType)
{
	// 상태 패턴 (State Pattern)
	// 상속과 다형성을 이용해서 FSM을 더욱 더 유연하게 만들어주는 디자인 패턴.
	if (m_ePreSceneType != eCurType)
	{
		SafeDelete(m_pCurScene);

		switch (eCurType)
		{
		case SCENE_LOGO:
			m_pCurScene = new CLogo;
			break;
		case SCENE_TITLE:
			m_pCurScene = new CTitle;
			break;
		case SCENE_STAGE1:
			m_pCurScene = new CStage1;
			break;
		case SCENE_EDIT:
			m_pCurScene = new CMyEdit;
			break;
		}

		m_pCurScene->Initialize();
		m_ePreSceneType = eCurType;
	}
}

void CSceneManager::Update()
{
	m_iEvent = m_pCurScene->Update();
}

void CSceneManager::Render(HDC hDC)
{
	if (CHANGE_SCENE == m_iEvent)
		return;

	m_pCurScene->Render(hDC);
}

void CSceneManager::Release()
{
	SafeDelete(m_pCurScene);
}
