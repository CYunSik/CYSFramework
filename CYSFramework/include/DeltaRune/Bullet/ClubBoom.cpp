#include "ClubBoom.h"

#include "../../Component/SpriteComponent.h"
#include "../../Object/BulletObject.h"
#include "../../Scene/Scene.h"

CClubBoom::CClubBoom()
{
}

CClubBoom::CClubBoom(const CClubBoom& Obj)
{
}

CClubBoom::CClubBoom(CClubBoom&& Obj)
{
}

CClubBoom::~CClubBoom()
{
}

bool CClubBoom::Init()
{
	mRoot = CreateComponent<CSpriteComponent>("JevilAttack");

	mRoot->SetWorldScale(50.f, 50.f, 1.f);
	mRoot->SetTint(1.f, 1.f, 1.f);
	mRoot->SetPivot(0.5f, 0.5f);
	mRoot->SetOpacity(1.f);

	SetRootComponent(mRoot);

	mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
	mAnimation->AddSequence("ClubBoom", 0.1f, 1.f, true, false);

	return true;
}

void CClubBoom::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	mDownTime -= DeltaTime;

	FVector3D Pos = mRoot->GetWorldPosition();
	FVector3D Dir = mRoot->GetAxis(EAxis::Y) * -1;
	FVector3D NewPos = Pos + Dir * 350.f * DeltaTime;
	mRoot->SetWorldPos(NewPos);

	if (mDownTime <= 0.f)
	{
		std::vector<float> RotationOffSets = {
			-180.f, -150.f, -120.f, -90.f, -60.f, -30.f, 0.f, 30.f, 60.f, 90.f, 120.f, 150.f, 180.f
		};

		for (float AngleOffSet : RotationOffSets)
		{
			CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");
			Bullet->SetBulletCollisionProfile("MonsterAttack");

			Bullet->SetWorldScale(60.f, 60.f);
			Bullet->SetWorldRotation(GetWorldRotation());
			Bullet->SetWorldPos(GetWorldPosition());
			Bullet->AddWorldRotationZ(AngleOffSet);
			Bullet->SetLifeTime(20.f);
		}

		Destroy();
	}
}
