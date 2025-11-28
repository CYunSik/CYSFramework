#include "Scene.h"
#include "Input.h"
#include "CameraManager.h"
#include "SceneCollision.h"
#include "SceneAssetManager.h"
#include "SceneUIManager.h"

CScene::CScene()
{

}
CScene::~CScene()
{
	SAFE_DELETE(mAssetManager);
	SAFE_DELETE(mInput);
	SAFE_DELETE(mCameraManager);
	SAFE_DELETE(mCollision);
	SAFE_DELETE(mUIManager);
}

bool CScene::Init()
{
	mInput = new CInput;
	mInput->mScene = this;
	if (!mInput->Init())
	{
		SAFE_DELETE(mInput);
		return false;
	}

	mCameraManager = new CCameraManager;
	if (!mCameraManager->Init())
	{
		SAFE_DELETE(mCameraManager);
		return false;
	}

	mCollision = new CSceneCollision;

	mCollision->mScene = this;

	if (!mCollision->Init())
	{
		SAFE_DELETE(mCollision);
		return false;
	}

	mAssetManager = new CSceneAssetManager;
	mAssetManager->mScene = this;
	if (!mAssetManager->Init())
	{
		SAFE_DELETE(mAssetManager);
		return false;
	}

	mUIManager = new CSceneUIManager;
	mUIManager->mScene = this;
	if (!mUIManager->Init())
	{
		SAFE_DELETE(mUIManager);
		return false;
	}

	return true;
}

bool CScene::Init(const char* FileName)
{
	mInput = new CInput;
	if (!mInput->Init())
	{
		SAFE_DELETE(mInput);
		return false;
	}

	mCameraManager = new CCameraManager;
	if (!mCameraManager->Init())
	{
		SAFE_DELETE(mCameraManager);
		return false;
	}

	mCollision = new CSceneCollision;

	mCollision->mScene = this;

	if (!mCollision->Init())
	{
		SAFE_DELETE(mCollision);
		return false;
	}

	mAssetManager = new CSceneAssetManager;
	mAssetManager->mScene = this;
	if (!mAssetManager->Init())
	{
		SAFE_DELETE(mAssetManager);
		return false;
	}

	return true;
}

void CScene::Input(float DeletaTime)
{
	mInput->Update(DeletaTime);
}

void CScene::PreUpdate(float DeltaTime)
{
	std::list<CSharedPtr<class CSceneObject>>::iterator iter;
	std::list<CSharedPtr<class CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PreUpdate(DeltaTime);
		++iter;
	}
}

void CScene::Update(float DeltaTime)
{
	std::list<CSharedPtr<class CSceneObject>>::iterator iter;
	std::list<CSharedPtr<class CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}

	mCameraManager->Update(DeltaTime);

	// UI 매니저 업데이트
	mUIManager->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	std::list<CSharedPtr<class CSceneObject>>::iterator iter;
	std::list<CSharedPtr<class CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}
}

void CScene::Collision(float DeltaTime)
{
	// SceneCollision이 해당 씬의 충돌을 모두 관리하게 한다!!
	// 콜리전도 조만간 수정
	mCollision->Update(DeltaTime);
}

void CScene::Render()
{
// 전처리기에서 디버그
#ifdef _DEBUG
	if (mDebugQuadTree)
	{
		mCollision->Render();
	}
#endif // _DEBUG
	mCollision->ReturnNodePool();

	std::list<CSharedPtr<class CSceneObject>>::iterator iter;
	std::list<CSharedPtr<class CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render();
		++iter;
	}
}

void CScene::RenderUI()
{
	mUIManager->Render();
}

void CScene::EndFrame()
{
	std::list<CSharedPtr<CSceneObject>>::iterator iter;
	std::list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->EndFrame();
	}
}
