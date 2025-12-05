#include "PlayerSoulObject.h"

#include "../Component/CameraComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/SpriteComponent.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/MovementComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "../Share/Log.h"

CPlayerSoulObject::CPlayerSoulObject()
{
}

CPlayerSoulObject::CPlayerSoulObject(const CPlayerSoulObject& Obj)
    : CSceneObject(Obj)
{
}

CPlayerSoulObject::CPlayerSoulObject(CPlayerSoulObject&& Obj)
    : CSceneObject(Obj)
{
}

CPlayerSoulObject::~CPlayerSoulObject()
{
}

bool CPlayerSoulObject::Init()
{
    mRoot = CreateComponent<CSpriteComponent>();
    mCamera = CreateComponent<CCameraComponent>();
    SetRootComponent(mRoot);

    mRoot->SetTexture("PlayerSoul", TEXT("Texture/Heart/spr_heart_0.png"));
    mRoot->SetTint(1.f, 1.f, 1.f);
    mRoot->SetWorldScale(22.f, 22.f, 1.f);
    mRoot->SetWorldPos(0.f, 0.f, 0.f);
    mRoot->SetPivot(0.5f, 0.5f);

    mMovement = CreateComponent<CMovementComponent>();
    mMovement->SetUpdateComponent(mRoot);
    mMovement->SetMoveSpeed(200.f);

    mBody = CreateComponent<CColliderAABB2D>();
    mBody->SetBoxSize(22.f, 22.f);
    mBody->SetCollisionProfile("Player");
    mBody->SetCollisionBeginFunc<CPlayerSoulObject>(this, &CPlayerSoulObject::OnCollisionBegin);

    mRoot->AddChild(mBody);

    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
    mAnimation->AddSequence("HeartHit", 0.3f, 1.f, true, false);

    mCamera->SetProjectionType(ECameraProjectionType::Ortho);
    mCamera->SetWorldPos(0.f, 0.f, -1000.f);

	// 전투박스
    SetWorldPos(0.f, 0.f, 0.f);

	// 입력
    mScene->GetInput()->AddBindKey("MoveUp", VK_UP);
    mScene->GetInput()->AddBindFunction("MoveUp", EInputType::Hold, this, &CPlayerSoulObject::MoveUp);

    mScene->GetInput()->AddBindKey("MoveDown", VK_DOWN);
    mScene->GetInput()->AddBindFunction("MoveDown", EInputType::Hold, this, &CPlayerSoulObject::MoveDown);

    mScene->GetInput()->AddBindKey("MoveLeft", VK_LEFT);
    mScene->GetInput()->AddBindFunction("MoveLeft", EInputType::Hold, this, &CPlayerSoulObject::MoveLeft);

    mScene->GetInput()->AddBindKey("MoveRight", VK_RIGHT);
    mScene->GetInput()->AddBindFunction("MoveRight", EInputType::Hold, this, &CPlayerSoulObject::MoveRight);

    return true;
}

void CPlayerSoulObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    // 만약 무적상태라면 (피격) 1초동안 무적
    if (mInvincible)
    {
        mInvincibleTime += DeltaTime;

        if (mInvincibleTime >= 2.f)
        {
            // 무적 해제
            mInvincible = false;
            mInvincibleTime = 0.f;
            mBody->SetCollisionProfile("Player");

            // 하트 원래 텍스쳐로 복원
            mAnimation->ChangeAnimation("None");
            CLog::PrintLog("Invincible Off");
        }
    }
    else
    {
        mAnimation->ChangeAnimation("None");
    }

    // 배틀 박스 제한
    FVector3D pos = GetWorldPosition();

    if (pos.x < mMinX)
    {
        pos.x = mMinX;
    }

    if (pos.x > mMaxX)
    {
        pos.x = mMaxX;
    }

    if (pos.y < mMinY)
    {
        pos.y = mMinY;
    }

    if (pos.y > mMaxY)
    {
        pos.y = mMaxY;
    }

    SetWorldPos(pos);
}

void CPlayerSoulObject::MoveUp(float DeltaTime)
{
    mMovement->AddMove(mRoot->GetAxis(EAxis::Y));
}

void CPlayerSoulObject::MoveDown(float DeltaTime)
{
    mMovement->AddMove(mRoot->GetAxis(EAxis::Y) * -1.f);
}

void CPlayerSoulObject::MoveLeft(float DeltaTime)
{
    mMovement->AddMove(mRoot->GetAxis(EAxis::X) * -1.f);
}

void CPlayerSoulObject::MoveRight(float DeltaTime)
{
    mMovement->AddMove(mRoot->GetAxis(EAxis::X));
}

void CPlayerSoulObject::OnCollisionBegin(const FVector3D& HitPoint, CColliderBase* Dest)
{
    // 이미 무적이면 피격무시
    if (mInvincible)
    {
        return;
    }

    // 무적 시작
    CLog::PrintLog("Invincible On");
    mInvincible = true;
    mInvincibleTime = 0.f;
    mBody->SetCollisionProfile("Invincible");

    // 어두운 하트 텍스쳐 적용
    mAnimation->ChangeAnimation("HeartHit");
}
