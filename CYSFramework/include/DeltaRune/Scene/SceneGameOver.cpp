#include "SceneGameOver.h"

#include "../PlayerSoulObject.h"
#include "../../Component/SpriteComponent.h"

CSceneGameOver::CSceneGameOver()
{
}

CSceneGameOver::~CSceneGameOver()
{
}

bool CSceneGameOver::Init()
{
    if (!CScene::Init())
    {
        return false;
    }

    CPlayerSoulObject* Heart = CreateObj<CPlayerSoulObject>("Heart");

    if (Heart == nullptr)
    {
        return false;
    }

    Heart->IsGameOver();

	return true;
}

void CSceneGameOver::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);

    mLogoShowTime += DeltaTime;

    if (mLogoShowTime >= 3.f)
    {
        CSceneObject* GameOverBG = CreateObj<CSceneObject>("GameOver");
        CSpriteComponent* GameOverBGSprite = GameOverBG->CreateComponent<CSpriteComponent>();

        GameOverBG->SetRootComponent(GameOverBGSprite);
        GameOverBG->SetWorldPos(0.f, 150.f, 7.f);
        GameOverBG->SetWorldScale(800.f, 350.f, 1.f);

        GameOverBGSprite->SetTexture("GameOverBGSprite", TEXT("Texture/UI/spr_gameoverbg.png"));
        GameOverBGSprite->SetPivot(0.5f, 0.5f);
    }
}