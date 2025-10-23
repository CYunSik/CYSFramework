#include "SceneManager.h"
#include "SceneMain.h"

CSceneManager::CSceneManager()
{

}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(mCurrentScene);
}

bool CSceneManager::Init()
{
	mCurrentScene = CreateScene<CSceneMain>();

	if (mCurrentScene == nullptr)
	{
		return false;
	}

	return true;
}

void CSceneManager::Update(float DeltaTime)
{

}

void CSceneManager::Collision(float DeltaTime)
{

}

void CSceneManager::Render()
{

}