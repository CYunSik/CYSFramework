#include "GunnerMonster.h"
#include "BulletObject.h"
#include "../Scene/Scene.h"
#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/MovementComponent.h"
#include "../Animation/Animation2D.h"

CGunnerMonster::CGunnerMonster()
{
}

CGunnerMonster::CGunnerMonster(const CGunnerMonster& Obj)
	: CMonsterObject(Obj)
{
}

CGunnerMonster::CGunnerMonster(CGunnerMonster&& Obj)
	: CMonsterObject(Obj)
{
}

CGunnerMonster::~CGunnerMonster()
{
}

bool CGunnerMonster::Init()
{
	if (!CMonsterObject::Init())
	{
		return false;
	}

	mRoot->SetTexture("SpadeBoom", TEXT("Texture/spr_bomb_spade_ch1_0.png"), 0);
	mRoot->SetPivot(0.5f, 0.5f);
	mRoot->SetOpacity(1.f);
	mRoot->SetWorldScale(50.f, 50.f, 1.f);

	//mAnimation->AddSequence("ClubBoom", 1.f, 1.f, true, false);

	SetTarget(mScene->FindObjectFromType<CPlayerObject>());

	return true;
}

void CGunnerMonster::Update(float DeltaTime)
{
	CMonsterObject::Update(DeltaTime);

	if (!mTarget->IsActive())
	{
		mTarget = nullptr;
	}
	else if (mTarget->IsEnable())
	{
		// 타켓을 바라보는 벡터
		// 내가 타겟을 바라보는 방향 벡터는 ?
		// 타켓 위치 - 자기자신 위치 == 방향 벡터
		//FVector3D ViewDir = mTarget->GetWorldPosition() - GetWorldPosition();
		//// 단위벡터로 만들어준다. (단위벡터 : 길이가 1인 벡터)
		//ViewDir.Normalize();

		//float Angle = FVector3D::Axis[EAxis::Y].GetAngle(ViewDir);

		float Angle = GetWorldPosition().GetViewTargetAngle(mTarget->GetWorldPosition());

		// 출력창 로그찍기
		// std::wostringstream oss;
		// oss << L"Angle : " << Angle << L"\n";
		// OutputDebugStringW(oss.str().c_str());

		SetWorldRotationZ(Angle);
	}

	// 발사하기 샘플
	mFireTime -= DeltaTime;

	if (mFireTime <= 0)
	{
		mFireTime = 1.f;
		//++mFireCount;

		//CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");
		//Bullet->SetBulletCollisionProfile("MonsterAttack");
		//Bullet->SetWorldScale(50.f, 50.f);
		//Bullet->SetWorldRotation(GetWorldRotation());
		//Bullet->SetWorldPos(GetWorldPosition());

		//Bullet->SetLifeTime(2.f);

		// 4번째 총알이면 다시 0으로
		//mFireCount = 0;
		std::vector<float> RotationOffSets = { -45.f, 0.f, 45.f };

		for (float AngleOffSet : RotationOffSets)
		{
			CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");
			Bullet->SetBulletCollisionProfile("MonsterAttack");

			Bullet->SetWorldScale(40.f, 40.f);
			Bullet->SetWorldRotation(GetWorldRotation());
			Bullet->SetWorldPos(GetWorldPosition());
			Bullet->AddWorldRotationZ(AngleOffSet);
			Bullet->SetLifeTime(2.f);
		}

		//if (mFireCount == 4)
		//{
		//}
	}
}
