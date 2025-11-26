#include "BulletObject.h"

#include "SpriteEffect.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Share/Log.h"
#include "../Scene/Scene.h"

CBulletObject::CBulletObject()
	: CSceneObject()
{

}

CBulletObject::CBulletObject(const CBulletObject& Obj)
	: CSceneObject(Obj)
{

}

CBulletObject::CBulletObject(CBulletObject&& Obj)
	: CSceneObject(Obj)
{

}
CBulletObject::~CBulletObject()
{

}

void CBulletObject::SetBulletCollisionProfile(const std::string& Name)
{
	mBody->SetCollisionProfile(Name);
}

bool CBulletObject::Init()
{
	CSceneObject::Init();

	mRoot = CreateComponent<CSpriteComponent>();
	mBody = CreateComponent<CColliderSphere2D>();
	mMovement = CreateComponent<CMovementComponent>();
	mRotation = CreateComponent<CRotationComponent>();

	mRoot->SetTexture("SpadeBullet", TEXT("Texture/spr_spadebullet.png"), 0);
	mRoot->SetTint(1.f, 1.f, 1.f);
	mRoot->SetPivot(0.5f, 0.5f);
	mRoot->SetOpacity(1.f);
	mRoot->SetWorldScale(30.f, 30.f, 1.f);

	// Movement 세팅
	mMovement->SetUpdateComponent(mRoot);
	mMovement->SetMoveAxis(EAxis::Y);
	mMovement->SetMoveSpeed(350.f);

	// Rotation 세팅
	mRotation->SetUpdateComponent(mRoot);

	SetRootComponent(mRoot);

	mRoot->AddChild(mBody);
	//mBody->SetBoxSize(30.f, 30.f);
	mBody->SetRadius(10.f);
	mBody->SetCollisionProfile("PlayerAttack");
	mBody->SetCollisionBeginFunc<CBulletObject>(this, &CBulletObject::CollisionBullet);

	return true;
}

void CBulletObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	//FVector3D Pos = mRoot->GetWorldPosition();
	//// 이동할 위치의 새로운 위치 값 = 내 위치 + 내 Y축 * 속도 * DeltaTime
	//mRoot->SetWorldPos(Pos + mRootComponent->GetAxis(EAxis::Y) * mSpeed * DeltaTime);
}

void CBulletObject::CollisionBullet(const FVector3D& HitPoint, CColliderBase* Dest)
{
	//CLog::PrintLog("Bullet Hit Collision", ELogPrintType::All);

	Dest->GetOwner()->Damage(1.f, this);

	CSpriteEffect* Effect = mScene->CreateObj<CSpriteEffect>("HitEffect");

	Effect->SetAnimation("AttackEffect");
	Effect->SetWorldPos(HitPoint);
	Effect->SetWorldScale(50.f, 50.f);

	Destroy();
}
