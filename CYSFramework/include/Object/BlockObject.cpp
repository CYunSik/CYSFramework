#include "BlockObject.h"

#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Scene/Scene.h"

CBlockObject::CBlockObject()
{
}

CBlockObject::CBlockObject(const CBlockObject& Obj)
    : CSceneObject(Obj)
{
}

CBlockObject::CBlockObject(CBlockObject&& Obj)
    : CSceneObject(Obj)
{
}

CBlockObject::~CBlockObject()
{
}

bool CBlockObject::Init()
{
    if (!CSceneObject::Init())
    {
        return false;
    }

    mRoot = CreateComponent<CStaticMeshComponent>();
    mBody = CreateComponent<CColliderAABB2D>();

    mRoot->SetMesh("CenterRect");
    mRoot->SetShader("ColorMeshShader");
    mRoot->SetWorldScale(50.f, 300.f);

    SetRootComponent(mRoot);

    mRoot->AddChild(mBody);
    mBody->SetBoxSize(50.f, 300.f);
    mBody->SetCollisionProfile("Default");
    mBody->SetCollisionBeginFunc<CBlockObject>(this, &CBlockObject::CollisionBlock);
    mBody->SetCollisionEndFunc<CBlockObject>(this, &CBlockObject::CollisionBlockEnd);

    return true;
}

void CBlockObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CBlockObject::CollisionBlock(const FVector3D& HitPoint, class CColliderBase* Dest)
{
    Dest->GetOwner()->SetMovement(0.f, this);
}

void CBlockObject::CollisionBlockEnd(class CColliderBase* Dest)
{
}
