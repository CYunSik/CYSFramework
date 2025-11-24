#include "BoomMonster.h"
#include "BulletObject.h"
#include "../Scene/Scene.h"
#include "PlayerObject.h"
#include "../Component/SpriteComponent.h"
#include "../Component/MovementComponent.h"

CBoomMonster::CBoomMonster()
{
}

CBoomMonster::CBoomMonster(const CBoomMonster& Obj)
	: CMonsterObject(Obj)
{
}

CBoomMonster::CBoomMonster(CBoomMonster&& Obj)
	: CMonsterObject(Obj)
{
}

CBoomMonster::~CBoomMonster()
{
}

bool CBoomMonster::Init()
{
	if (!CMonsterObject::Init())
	{
		return false;
	}

	mRoot->SetTexture("ClubBoom", TEXT("Texture/spr_bomb_club_ch1_0.png"), 0);
	mRoot->SetTint(1.f, 1.f, 1.f);
	mRoot->SetPivot(0.5f, 0.5f);
	mRoot->SetOpacity(1.f);

	mRoot->SetWorldScale(50.f, 50.f, 1.f);

	SetTarget(mScene->FindObjectFromType<CPlayerObject>());

	return true;
}

void CBoomMonster::Update(float DeltaTime)
{
	CMonsterObject::Update(DeltaTime);

	mDownTime -= DeltaTime;

	FVector3D Pos = mRoot->GetWorldPosition();
	FVector3D Dir = mRoot->GetAxis(EAxis::Y) * -1;
	FVector3D NewPos = Pos + Dir * 300.f * DeltaTime;
	mRoot->SetWorldPos(NewPos);

	if (mDownTime <= 0.f)
	{
		std::vector<float> RotationOffSets = { -180.f, -160.f, -140.f, -120.f, -100.f, -80.f, -60.f, -40.f, -20.f, 0.f, 
			20.f, 40.f, 60.f, 80.f, 100.f, 120.f, 140.f, 160.f, 180.f };

		for (float AngleOffSet : RotationOffSets)
		{
			CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");
			Bullet->SetBulletCollisionProfile("MonsterAttack");

			Bullet->SetWorldScale(30.f, 30.f);
			Bullet->SetWorldRotation(GetWorldRotation());
			Bullet->SetWorldPos(GetWorldPosition());
			Bullet->AddWorldRotationZ(AngleOffSet);
			Bullet->SetLifeTime(2.f);
		}

		Destroy();
	}
}
