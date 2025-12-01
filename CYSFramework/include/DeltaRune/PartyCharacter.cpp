#include "PartyCharacter.h"
#include "../Component/SpriteComponent.h"
#include "../Animation/Animation2D.h"

CPartyCharacter::CPartyCharacter()
{
}

CPartyCharacter::~CPartyCharacter()
{
}

bool CPartyCharacter::Init()
{
    // 스프라이트 생성
    mSprite = CreateComponent<CSpriteComponent>();
    SetRootComponent(mSprite);

    mSprite->SetPivot(0.5f, 0.5f);
    mSprite->SetWorldScale(50.f, 50.f, 1.f);

    mAnimation = mSprite->CreateAnimation2D<CAnimation2D>();

    // 캐릭터별 기본 Idle 텍스처 설정
    if (mCharacterName == "Kris")
    {
        mSprite->SetTexture("KrisIdle", TEXT("Texture/Kris/spr_krisr_dark/spr_krisr_dark_0.png"), 0);
    }
    else if (mCharacterName == "Susie")
    {
        mSprite->SetTexture("SusieIdle", TEXT("Texture/Susie/spr_susier_dark/spr_susier_dark_0.png"), 0);
    }
    else if (mCharacterName == "Ralsei")
    {
        mSprite->SetTexture("RalseiIdle", TEXT("Texture/Ralsei/spr_ralseir/spr_ralseir_0.png"), 0);
    }

    return true;
}

void CPartyCharacter::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    if (mIsWalking)
    {
        // 오른쪽 걷기 애니메이션 재생
        if (mCharacterName == "Kris")
        {
            mAnimation->ChangeAnimation("KrisWalkRight");
        }
        else if (mCharacterName == "Susie")
        {
            mAnimation->ChangeAnimation("SusieWalkRight");
        }
        else if (mCharacterName == "Ralsei")
        {
        	mAnimation->ChangeAnimation("RalseiWalkRight");
        }

        // 오른쪽으로 이동
        FVector3D Pos = GetWorldPosition();
        Pos.x += mMoveSpeed * DeltaTime;
        SetWorldPos(Pos);
    }
    else
    {
        if (mCharacterName == "Kris")
        {
        	mAnimation->ChangeAnimation("None");
        }
        else if (mCharacterName == "Susie")
        {
        	mAnimation->ChangeAnimation("None");
        }
        else if (mCharacterName == "Ralsei")
        {
        	mAnimation->ChangeAnimation("None");
        }
    }
}

void CPartyCharacter::MoveRight(float DeltaTime)
{
    mIsWalking = true;
}

void CPartyCharacter::Stop()
{
    mIsWalking = false;
}
