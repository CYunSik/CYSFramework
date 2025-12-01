#include "PenetrationBullet.h"

#include "BulletObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Scene/Scene.h"
#include "../Component/ColliderOBB2D.h"

#include "../Share/Log.h"

CPenetrationBullet::CPenetrationBullet()
{
}

CPenetrationBullet::CPenetrationBullet(const CPenetrationBullet& Obj)
	: CSceneObject(Obj)
{
}

CPenetrationBullet::CPenetrationBullet(CPenetrationBullet&& Obj)
	: CSceneObject(Obj)
{
}

CPenetrationBullet::~CPenetrationBullet()
{
}

bool CPenetrationBullet::Init()
{
	if (!CSceneObject::Init())
	{
		return false;
	}

	mMesh = CreateComponent<CStaticMeshComponent>();
	mBody = CreateComponent<CColliderOBB2D>();
	mMovement = CreateComponent<CMovementComponent>();
	mRotation = CreateComponent<CRotationComponent>();

	mMovement->SetUpdateComponent(mMesh);
	mMovement->SetMoveAxis(EAxis::Y);
	mMovement->SetMoveSpeed(500.f);

	mMesh->SetMesh("CenterRect");
	mMesh->SetShader("ColorMeshShader");
	mMesh->SetWorldScale(50.f, 50.f, 1.f);

	SetRootComponent(mMesh);

	mMesh->AddChild(mBody);
	mBody->SetBoxSize(50.f, 50.f);
	mBody->SetCollisionProfile("PlayerAttack");
	mBody->SetCollisionBeginFunc<CPenetrationBullet>(this, &CPenetrationBullet::CollisionBullet);

	return true;
}

void CPenetrationBullet::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
}

void CPenetrationBullet::CollisionBullet(const FVector3D& HitPoint, class CColliderBase* Dest)
{
	Dest->GetOwner()->Damage(1.f, this);
	//CLog::PrintLog("PenetrateDamage");
	++mPenetrateCount;

	if (mPenetrateCount >= 3)
	{
		Destroy();
	}
}
