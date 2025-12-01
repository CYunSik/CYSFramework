#include "ContinuousdamageBullet.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Scene/Scene.h"
#include "MonsterObject.h"
#include "../Component/ColliderOBB2D.h"

#include "../Share/Log.h"

CContinuousdamageBullet::CContinuousdamageBullet()
{
}

CContinuousdamageBullet::CContinuousdamageBullet(const CContinuousdamageBullet& Obj)
	: CSceneObject(Obj)
{
}

CContinuousdamageBullet::CContinuousdamageBullet(CContinuousdamageBullet&& Obj)
	: CSceneObject(Obj)
{
}

CContinuousdamageBullet::~CContinuousdamageBullet()
{
}

bool CContinuousdamageBullet::Init()
{
	if (!CSceneObject::Init())
	{
		return false;
	}

	mMesh = CreateComponent<CStaticMeshComponent>();
	mCircle = CreateComponent<CStaticMeshComponent>();
	mMovement = CreateComponent<CMovementComponent>();
	mRotation = CreateComponent<CRotationComponent>();

	mMovement->SetUpdateComponent(mMesh);
	mMovement->SetMoveAxis(EAxis::Y);
	mMovement->SetMoveSpeed(150.f);

	mMesh->SetMesh("CenterRect");
	mMesh->SetShader("ColorMeshShader");
	mMesh->SetWorldScale(50.f, 50.f, 1.f);

	SetRootComponent(mMesh);

	mMesh->AddChild(mCircle);
	mCircle->SetMesh("FrameSphere2D");
	mCircle->SetShader("FrameMeshShader");
	mCircle->SetWorldScale(450.f, 450.f, 1.f);

	return true;
}

void CContinuousdamageBullet::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	FVector3D Center = GetWorldPosition();

	// 씬에서 몬스터들 리스트로 찾기
	const std::list<CSharedPtr<CSceneObject>> ObjList = mScene->GetObjectList();

	// 몬스터별 데미지 타이머 저장용
	static std::unordered_map<CMonsterObject*, float> MonsterDamageTimer;

	for (const CSharedPtr<CSceneObject>& Ptr : ObjList)
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

		// 몬스터 위치 가져와서
		FVector3D MonsterPos = Monster->GetWorldPosition();

		// 거리계산
		float Dist = MonsterPos.Distance(Center);

		// 300.f 범위안에 있으면
		if (Dist < mRadius)
		{
			// 몬스터별 누적 시간
			float& Timer = MonsterDamageTimer[Monster];
			Timer += DeltaTime;

			// 개별 몬스터의 타이머가 Interval 이상이면 데미지 동시에 적용
			if (Timer >= mDamageInterval)
			{
				Monster->Damage(1.f, this);
				//CLog::PrintLog("ContinuousDamage");
				Timer = 0.f;
			}
		}
		else
		{
			// 범위 밖인 몬스터는 삭제
			MonsterDamageTimer.erase(Monster);
		}
	}
}