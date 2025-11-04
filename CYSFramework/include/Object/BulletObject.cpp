#include "BulletObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/ColliderAABB2D.h"

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

	return true;
}

void CBulletObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	//FVector3D Pos = mRoot->GetWorldPosition();
	//// 이동할 위치의 새로운 위치 값 = 내 위치 + 내 Y축 * 속도 * DeltaTime
	//mRoot->SetWorldPos(Pos + mRootComponent->GetAxis(EAxis::Y) * mSpeed * DeltaTime);
}