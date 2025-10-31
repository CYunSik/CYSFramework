#include "NearingMonster.h"
#include "../Component/StaticMeshComponent.h"
#include "BulletObject.h"
#include "../Scene/Scene.h"
#include "PlayerObject.h"

// 로그찍기
#include <sstream>

CNearingMonster::CNearingMonster()
{
}

CNearingMonster::CNearingMonster(const CNearingMonster& Obj)
	: CMonsterObject(Obj)
{
}

CNearingMonster::CNearingMonster(CNearingMonster&& Obj)
	: CMonsterObject(Obj)
{
}

CNearingMonster::~CNearingMonster()
{
}

bool CNearingMonster::Init()
{
	if (!CMonsterObject::Init())
	{
		return false;
	}

	return true;
}

void CNearingMonster::Update(float DeltaTime)
{
	CMonsterObject::Update(DeltaTime);

	mFireTime -= DeltaTime;

	if (mTarget)
	{
		float Distance = GetWorldPosition().Distance(mTarget->GetWorldPosition());

		// 플레이어와 거리가 300이하일때
		if (Distance <= 300.f)
		{
			// 플레이어 따라가기
			float Angle = GetWorldPosition().GetViewTargetAngle(mTarget->GetWorldPosition());

			SetWorldRotationZ(Angle);

			if (mFireTime <= 0)
			{
				mFireTime = 1.f;

				CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");
				Bullet->SetWorldScale(50.f, 50.f);
				Bullet->SetWorldRotation(GetWorldRotation());
				Bullet->SetWorldPos(GetWorldPosition());

				Bullet->SetLifeTime(2.f);

				CPlayerObject* Player = dynamic_cast<CPlayerObject*>(mTarget.Get());

				if (Player)
				{
					// Player에게 데미지를 준다.
					Player->Damage(1);
				}
			}
		}
	}
}