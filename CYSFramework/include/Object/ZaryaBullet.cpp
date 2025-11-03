#include "ZaryaBullet.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Scene/Scene.h"
#include "MonsterObject.h"

CZaryaBullet::CZaryaBullet()
{
}

CZaryaBullet::CZaryaBullet(const CZaryaBullet& Obj)
	: CSceneObject(Obj)
{
}

CZaryaBullet::CZaryaBullet(CZaryaBullet&& Obj)
	: CSceneObject(Obj)
{
}

CZaryaBullet::~CZaryaBullet()
{
}

bool CZaryaBullet::Init()
{
	if (!CSceneObject::Init())
	{
		return false;
	}

	mMesh = CreateComponent<CStaticMeshComponent>();
	mMovement = CreateComponent<CMovementComponent>();
	mRotation = CreateComponent<CRotationComponent>();

	mMovement->SetUpdateComponent(mMesh);
	mMovement->SetMoveAxis(EAxis::Y);
	mMovement->SetMoveSpeed(500.f);

	mMesh->SetMesh("CenterRect");
	mMesh->SetShader("ColorMeshShader");
	mMesh->SetWorldScale(50.f, 50.f, 1.f);

	SetRootComponent(mMesh);

	return true;
}

void CZaryaBullet::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	mActiveTime += DeltaTime;

	FVector3D Pos = mMesh->GetWorldPosition();

	// 1초 앞으로 이동 후 상태별로 분리
	if (mActiveTime >= 1.f)
	{
		// 총알 이동 정지
		mMovement->SetEnable(false);

		if (!mScene)
		{
			return;
		}

		FVector3D Center = GetWorldPosition();

		// 씬의 오브젝트 리스트 가져오기
		const std::list<CSharedPtr<CSceneObject>>& ObjectList = mScene->GetObjectList();

		for (const CSharedPtr<CSceneObject>& Ptr : ObjectList)
		{
			CSceneObject* Obj = Ptr.Get();
			if (!Obj)
			{
				continue;
			}
			if (!Obj->IsActive())
			{
				continue;
			}

			// 몬스터 오브젝트만 처리
			CMonsterObject* Monster = dynamic_cast<CMonsterObject*>(Obj);
			if (!Monster)
			{
				continue;
			}

			FVector3D MonsterPos = Monster->GetWorldPosition();
			FVector3D Dir;

			switch (mState)
			{
			case EZaryaState::Attraction:
				Dir = Center - MonsterPos;
				break;

			case EZaryaState::Push:
				Dir = MonsterPos - Center; // Attraction과 반대로해서 밀기
				break;
			}

			float Dist = Dir.Length();

			if (Dist < mRadius)
			{
				Dir.Normalize();

				FVector3D NewPos = MonsterPos + Dir * mForce * DeltaTime;
				Monster->SetWorldPos(NewPos);
			}
		}
	}
}