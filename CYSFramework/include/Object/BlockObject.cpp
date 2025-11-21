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
    mRoot2 = CreateComponent<CStaticMeshComponent>();
    //mBody = CreateComponent<CColliderAABB2D>();

    //mRoot->SetMesh("CenterRect");
    //mRoot->SetShader("ColorMeshShader");
    mRoot->SetMesh("CenterTexRect");
    mRoot->SetMaterial(0, "HitBox1");
    mRoot->SetBaseColor(0, 0.f, 1.f, 0.f, 1.f);
    mRoot->SetShader("StaticMeshShader");
    mRoot->SetOpacity(0, 1.f);
    mRoot->SetWorldScale(300.f, 300.f);

    SetRootComponent(mRoot);
    mRoot->AddChild(mRoot2);

    mRoot2->SetMesh("CenterTexRect");
    mRoot2->SetMaterial(0, "HitBox2");
    mRoot2->SetShader("StaticMeshShader");
    mRoot2->SetOpacity(0, 1.f);
    mRoot2->SetWorldScale(300.f, 300.f);

    //mRoot->AddChild(mBody);
    //mBody->SetBoxSize(200.f, 200.f);
    //mBody->SetCollisionProfile("Default");
    //mBody->SetCollisionBeginFunc<CBlockObject>(this, &CBlockObject::CollisionBlock);
    //mBody->SetCollisionEndFunc<CBlockObject>(this, &CBlockObject::CollisionBlockEnd);

    return true;
}

void CBlockObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CBlockObject::CollisionBlock(const FVector3D& HitPoint, class CColliderBase* Dest)
{
    
}

void CBlockObject::CollisionBlockEnd(class CColliderBase* Dest)
{
}
