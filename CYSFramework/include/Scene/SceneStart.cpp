#include "SceneStart.h"

#include "CameraManager.h"
#include "../UI/UserWidget/StartWidget.h"
#include "../Component/SpriteComponent.h"
#include "SceneUIManager.h"
#include "../Object/SceneObject.h"
#include "../Component/CameraComponent.h"

#include "../Share/Log.h"

CSceneStart::CSceneStart()
{
}

CSceneStart::~CSceneStart()
{
}

bool CSceneStart::Init()
{
    if (!CScene::Init())
    {
        return false;
    }

	// UI 생성
	CStartWidget* Widget = mUIManager->CreateWidget<CStartWidget>("Start");

	mUIManager->AddToViewport(Widget);

	return true;
}
