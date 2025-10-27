#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"

#include "BulletObject.h"
#include "TornadoBullet.h"

CPlayerObject::CPlayerObject()
	: CSceneObject()
{
}

CPlayerObject::CPlayerObject(const CPlayerObject& Obj)
	: CSceneObject(Obj)
{
}

CPlayerObject::CPlayerObject(CPlayerObject&& Obj)
	: CSceneObject(Obj)
{
}

CPlayerObject::~CPlayerObject()
{
}

bool CPlayerObject::Init()
{
	// 게임 매니저 -> 씬매니저를 통해 -> 현재 씬을 실행시키고
	// 씬에서는 씬에 포함된 오브젝트들을 전부 순회하면서 시점 함수들을 호출해준다.
	// 오브젝트들은 본인의 루트 컴포넌트를 호출해주면
	// 루트 컴포넌트는 자식 컴포넌트들을 호출해준다.

	// 컴포넌트 하나 등록해줄거다.
	mRoot = CreateComponent<CStaticMeshComponent>();

	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");

	mRoot->SetWorldPos(0.f, 0.f, 5.5f);
	SetRootComponent(mRoot);

	// 위성 만들기
	mRotationPivot = CreateComponent<CSceneComponent>();
	mSub = CreateComponent<CStaticMeshComponent>();
	mSub2 = CreateComponent<CStaticMeshComponent>();

	mRoot->AddChild(mRotationPivot);
	mRotationPivot->AddChild(mSub);
	mRotationPivot->AddChild(mSub2);

	// 위성 1
	mSub->SetMesh("CenterRect");
	mSub->SetShader("ColorMeshShader");
	mSub->SetRelativePos(-2.f, 0.f, 0.f);
	mSub->SetRelativeScale(0.5f, 0.5f, 1.f);

	// 위성 2
	mSub2->SetMesh("CenterRect");
	mSub2->SetShader("ColorMeshShader");
	mSub2->SetRelativePos(2.f, 0.f, 0.f);
	mSub2->SetRelativeScale(0.5f, 0.5f, 1.f);

	// 입력
	mScene->GetInput()->AddBindKey("MoveUp", 'W');
	mScene->GetInput()->AddBindFunction("MoveUp", EInputType::Hold, this, &CPlayerObject::MoveUp);

	mScene->GetInput()->AddBindKey("MoveDown", 'S');
	mScene->GetInput()->AddBindFunction("MoveDown", EInputType::Hold, this, &CPlayerObject::MoveDown);

	// 회전
	mScene->GetInput()->AddBindKey("RotationZ", 'D');
	mScene->GetInput()->AddBindFunction("RotationZ", EInputType::Hold, this, &CPlayerObject::RotationZ);

	mScene->GetInput()->AddBindKey("RotationInv", 'A');
	mScene->GetInput()->AddBindFunction("RotationInv", EInputType::Hold, this, &CPlayerObject::RotationZInv);

	// 총알 발사
	mScene->GetInput()->AddBindKey("Fire", VK_SPACE);
	mScene->GetInput()->AddBindFunction("Fire", EInputType::Down, this, &CPlayerObject::Fire);

	// 스킬 1 : 차징 총알
	mScene->GetInput()->AddBindKey("Skill1", '1');
	mScene->GetInput()->AddBindFunction("Skill1", EInputType::Hold, this, &CPlayerObject::Skill1);
	mScene->GetInput()->AddBindFunction("Skill1", EInputType::Up, this, &CPlayerObject::Skill1Fire);

	// 스킬 2 : 토네이도 총알
	mScene->GetInput()->AddBindKey("Skill2", '2');
	mScene->GetInput()->AddBindFunction("Skill2", EInputType::Down, this, &CPlayerObject::Skill2);

	// 스킬 3 : 위성 발사
	mScene->GetInput()->AddBindKey("Skill3", '3');
	mScene->GetInput()->AddBindFunction("Skill3", EInputType::Down, this, &CPlayerObject::Skill3);

	// 스킬 4 : 돌아가는 위성의 범위를 늘렸다가 몇초후 다시 되돌아오기, 가능하면 위성의 속도도 늘렸다가 줄이기

	// 스킬 5 : 롤 탈론 궁극기 만들기 (플레이어 기준으로 8방향으로 총알을 발사하고 해당 총알이 몇초 돌다가 플레이어에게 다시 되돌아오는 부메랑 기능)

	return true;
}

void CPlayerObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	// 위성을 돌려주면 된다.
	FVector3D Rot = mRotationPivot->GetRelativeRotation();
	Rot.z += DeltaTime * 180.f;
	mRotationPivot->SetRelativeRotationZ(Rot.z);

	if (mSkill3Enable)
	{
		Skill3Update(DeltaTime);
	}
}

void CPlayerObject::MoveUp(float DeltaTime)
{
	FVector3D Pos = mRootComponent->GetWorldPosition();
	// FVector3D Dir = { 0.f, 1.f, 0.f }; 기존꺼
	FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);

	mRootComponent->SetWorldPos(Pos + Dir * DeltaTime);
}

void CPlayerObject::MoveDown(float DeltaTime)
{
	FVector3D Pos = mRootComponent->GetWorldPosition();
	// FVector3D Dir = { 0.f, -1.f, 0.f }; 기존꺼
	FVector3D Dir = mRootComponent->GetAxis(EAxis::DownY);

	mRootComponent->SetWorldPos(Pos + Dir * DeltaTime);
}

void CPlayerObject::RotationZ(float DeltaTime)
{
	FVector3D Rot = mRootComponent->GetWorldRotation();
	mRootComponent->SetWorldRotationZ(Rot.z + 90.f * DeltaTime);
}

void CPlayerObject::RotationZInv(float DeltaTime)
{
	FVector3D Rot = mRootComponent->GetWorldRotation();
	mRootComponent->SetWorldRotationZ(Rot.z + -90.f * DeltaTime);
}

void CPlayerObject::Fire(float DeltaTime)
{
	// 총알을 만들것이고
	CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

	CSceneComponent* Root = Bullet->GetRootComponent();
	// 총알의 시작 위치 == 내 월드 위치
	Root->SetWorldPos(mRootComponent->GetWorldPosition());
	Root->SetWorldRotation(mRootComponent->GetWorldRotation());
	Bullet->SetLifeTime(2.f);
}

void CPlayerObject::Skill1(float DeltaTime)
{
	// 스킬을 누르는 동안
	if (!mSkill1Object)
	{
		// 발사할 총알 만든다.
		mSkill1Object = mScene->CreateObj<CBulletObject>("Skill1Bullet");
		mSkill1Object->SetBulletSpeed(0.f);
	}

	CSceneComponent* Root = mSkill1Object->GetRootComponent();
	Root->SetWorldPos(mRootComponent->GetWorldPosition() + mRootComponent->GetAxis(EAxis::Y));
	Root->SetWorldRotation(mRootComponent->GetWorldRotation());

	FVector3D Scale = Root->GetWorldScale();

	Scale.x += 2.f * DeltaTime;
	Scale.y += 2.f * DeltaTime;

	if (Scale.x >= 4.f)
	{
		Scale.x = 4.f;
	}

	if (Scale.y >= 4.f)
	{
		Scale.y = 4.f;
	}

	mSkill1Object->GetRootComponent()->SetWorldScale(Scale);
}

void CPlayerObject::Skill1Fire(float DeltaTime)
{
	mSkill1Object->SetBulletSpeed(2.f);
	mSkill1Object = nullptr;
}

void CPlayerObject::Skill2(float DeltaTime)
{
	// 총알을 만들것이고
	CTornadoBullet* Bullet = mScene->CreateObj<CTornadoBullet>("TornadoBullet");

	CSceneComponent* Root = Bullet->GetRootComponent();
	// 총알의 시작 위치 == 내 월드 위치
	Root->SetWorldPos(mRootComponent->GetWorldPosition());
	Root->SetWorldRotation(mRootComponent->GetWorldRotation());
	Bullet->SetBulletSpeed(5.f);
	Bullet->SetLifeTime(1.f);
}

void CPlayerObject::Skill3(float DeltaTime)
{
	// 스킬이 발동중이니?
	if (!mSkill3Enable)
	{
		mSkill3Enable = true;
		mSkill3Time = 3.f;
		mSkill3TimeAcc = 0.f;
		mSkill3Interval = 0.2f;
	}
}

void CPlayerObject::Skill3Update(float DeltaTime)
{
	mSkill3TimeAcc += DeltaTime;

	if (mSkill3TimeAcc >= mSkill3Interval)
	{
		mSkill3TimeAcc -= mSkill3Interval;

		// 총알을 발사한다.
		CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

		CSceneComponent* Root = Bullet->GetRootComponent();
		// 총알의 시작 위치 == 내 월드 위치
		Root->SetWorldPos(mSub->GetWorldPosition());
		Root->SetWorldRotation(mRootComponent->GetWorldRotation());
		Bullet->SetLifeTime(2.f);
		Bullet->SetBulletSpeed(1.5f);

		Bullet = mScene->CreateObj<CBulletObject>("Bullet");
		Root = Bullet->GetRootComponent();
		// 총알의 시작 위치 == 내 월드 위치
		Root->SetWorldPos(mSub2->GetWorldPosition());
		Root->SetWorldRotation(mRootComponent->GetWorldRotation());
		Bullet->SetLifeTime(2.f);
		Bullet->SetBulletSpeed(1.5f);
	}

	mSkill3Time -= DeltaTime;

	if (mSkill3Time <= 0.f)
	{
		mSkill3Enable = false;
	}
}
