#include "BulletObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Share/Log.h"

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

	mRoot = CreateComponent<CStaticMeshComponent>();
	mBody = CreateComponent<CColliderAABB2D>();
	mMovement = CreateComponent<CMovementComponent>();
	mRotation = CreateComponent<CRotationComponent>();

	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");
	mRoot->SetWorldScale(0.5f, 0.5f, 1.f);

	// Movement 세팅
	mMovement->SetUpdateComponent(mRoot);
	mMovement->SetMoveAxis(EAxis::Y);
	mMovement->SetMoveSpeed(500.f);

	// Rotation 세팅
	mRotation->SetUpdateComponent(mRoot);

	SetRootComponent(mRoot);

	mRoot->AddChild(mBody);
	mBody->SetBoxSize(50.f, 50.f);
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
	CLog::PrintLog("Bullet Hit Collision", ELogPrintType::All);

	Destroy();
}
