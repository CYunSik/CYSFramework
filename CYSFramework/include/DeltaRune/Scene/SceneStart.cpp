#include "SceneStart.h"

#include "../../Scene/CameraManager.h"
#include "../UI/StartWidget.h"
#include "../../Scene/SceneUIManager.h"

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
