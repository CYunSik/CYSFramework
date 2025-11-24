#include "BlockObject.h"

#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/SpriteComponent.h"
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

    mRoot = CreateComponent<CSpriteComponent>();
    mRoot2 = CreateComponent<CSpriteComponent>();
    //mBody = CreateComponent<CColliderAABB2D>();

    //mRoot->SetMesh("CenterRect");
    //mRoot->SetShader("ColorMeshShader");

    mRoot->SetTexture("HitBox1", TEXT("Texture/spr_battlebg_stretch_hitbox_0.png"), 0);
    mRoot->SetTint(0.f, 1.f, 0.f);
    mRoot->SetPivot(0.5f, 0.5f);
    mRoot->SetOpacity(1.f);
    mRoot->SetWorldScale(250.f, 250.f, 1.f);

    SetRootComponent(mRoot);
    //mRoot->AddChild(mRoot2);

    //mRoot2->SetTexture("HitBox2", TEXT("Texture/spr_battlebg_stretch_hitbox_1.png"), 0);
    //mRoot2->SetTint(1.f, 1.f, 1.f);
    //mRoot2->SetPivot(0.5f, 0.5f);
    //mRoot2->SetOpacity(1.f);
    //mRoot2->SetWorldScale(255.f, 255.f, 1.f);
	
	//mRoot->AddChild(mBody);
 //   mBody->SetBoxSize(300.f, 10.f);
 //   mBody->SetRelativePos(0.f, -140.f, 0.f);
 //   mBody->SetCollisionProfile("Default");
 //   mBody->SetCollisionBeginFunc<CBlockObject>(this, &CBlockObject::CollisionBlock);
 //   mBody->SetCollisionEndFunc<CBlockObject>(this, &CBlockObject::CollisionBlockEnd);

    return true;
}

void CBlockObject::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);
}

void CBlockObject::CollisionBlock(const FVector3D& HitPoint, class CColliderBase* Dest)
{
    //Dest->GetOwner()->SetMovement(0.f, this);
}

void CBlockObject::CollisionBlockEnd(class CColliderBase* Dest)
{
}
