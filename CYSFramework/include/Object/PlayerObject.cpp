#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "../Component/ColliderBase.h"
#include "../Collision.h"
#include "../Animation/Animation2D.h"

#include "../Scene/Scene.h"
#include "../Scene/Input.h"

#include "BulletObject.h"
#include "TornadoBullet.h"
#include "TalonR.h"
#include "ZaryaBullet.h"
#include "ContinuousdamageBullet.h"
#include "PenetrationBullet.h"

#include "../Component/SpriteComponent.h"
#include "../Share/Log.h"

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
	//mRoot = CreateComponent<CStaticMeshComponent>();
	mRoot = CreateComponent<CSpriteComponent>();
	mBody = CreateComponent<CColliderAABB2D>();
	//mBody = CreateComponent<CColliderSphere2D>();
	//mBody = CreateComponent<CColliderOBB2D>();
	//mLine = CreateComponent<CColliderLine2D>();

	mMovement = CreateComponent<CMovementComponent>();
	mRotation = CreateComponent<CRotationComponent>();
	mCamera = CreateComponent<CCameraComponent>();

	// 크리스
	//mRoot->SetMesh("CenterTexRect");
	mRoot->SetTexture("Kris", TEXT("Texture/spr_krisd_dark_0.png"), 0);
	mRoot->SetTint(1.f, 1.f, 1.f);
	mRoot->SetPivot(0.5f, 0.5f);
	mRoot->SetOpacity(1.f);
	//mRoot->SetShader("ColorMeshShader");

	mRoot->SetWorldPos(0.f, 0.f, 0.f);
	mRoot->SetWorldScale(45.f, 80.f, 1.f);
	SetRootComponent(mRoot);

	mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
	mAnimation->AddSequence("KrisIdle", 1.f, 1.f, true, false);
	mAnimation->AddSequence("KrisWalkRight", 1.f, 1.f, true, false);
	mAnimation->AddSequence("KrisWalkLeft", 1.f, 1.f, true, false);
	mAnimation->AddSequence("KrisWalkUp", 1.f, 1.f, true, false);
	mAnimation->AddSequence("KrisWalkDown", 1.f, 1.f, true, false);
	mAnimation->AddSequence("KrisAttack", 1.f, 1.f, true, false);

	mAnimation->SetEndFunction("KrisAttack", this, &CPlayerObject::AttackEnd);
	mAnimation->AddNotify("KrisAttack", 1, this, &CPlayerObject::AttackNotify);

	//mRoot->SetFlip(false);
	mRoot->AddChild(mBody);
	mBody->SetBoxSize(45.f, 80.f);
	//mBody->SetRadius(50.f);
	mBody->SetCollisionProfile("Player");
	mBody->SetCollisionBeginFunc(this, &CPlayerObject::OnCollisionBegin);
	mBody->SetCollisionEndFunc(this, &CPlayerObject::OnCollisionEnd);


	//mBody->AddChild(mLine);
	//mLine->SetCollisionProfile("Player");
	//mLine->SetLineDistance(300.f);
	//mLine->SetRelativePos(0.f, 50.f);

	// movement
	mMovement->SetUpdateComponent(mRoot);
	mMovement->SetMoveSpeed(350.f);

	// rotation
	mRotation->SetUpdateComponent(mRoot);

	// 카메라 세팅
	mCamera->SetProjectionType(ECameraProjectionType::Ortho);
	mRoot->AddChild(mCamera);

	mTrail.clear();
	mTrail.reserve(2000);

	// 위성 만들기
	//mRotationPivot = CreateComponent<CSceneComponent>();
	//mSub = CreateComponent<CStaticMeshComponent>();
	//mSub2 = CreateComponent<CStaticMeshComponent>();

	//mRoot->AddChild(mRotationPivot);
	//mRotationPivot->AddChild(mSub);
	//mRotationPivot->AddChild(mSub2);

	//// 위성 1
	//mSub->SetMesh("CenterRect");
	//mSub->SetShader("ColorMeshShader");
	//mSub->SetRelativePos(-200.f, 0.f, 0.f);
	//mSub->SetRelativeScale(0.5f, 0.5f, 1.f);

	//// 위성 2
	//mSub2->SetMesh("CenterRect");
	//mSub2->SetShader("ColorMeshShader");
	//mSub2->SetRelativePos(200.f, 0.f, 0.f);
	//mSub2->SetRelativeScale(0.5f, 0.5f, 1.f);

	// 입력
	mScene->GetInput()->AddBindKey("MoveUp", VK_UP);
	mScene->GetInput()->AddBindFunction("MoveUp", EInputType::Hold, this, &CPlayerObject::MoveUp);

	mScene->GetInput()->AddBindKey("MoveDown", VK_DOWN);
	mScene->GetInput()->AddBindFunction("MoveDown", EInputType::Hold, this, &CPlayerObject::MoveDown);

	mScene->GetInput()->AddBindKey("MoveLeft", VK_LEFT);
	mScene->GetInput()->AddBindFunction("MoveLeft", EInputType::Hold, this, &CPlayerObject::MoveLeft);

	mScene->GetInput()->AddBindKey("MoveRight", VK_RIGHT);
	mScene->GetInput()->AddBindFunction("MoveRight", EInputType::Hold, this, &CPlayerObject::MoveRight);

	// 회전
	//mScene->GetInput()->AddBindKey("RotationZ", 'E');
	//mScene->GetInput()->AddBindFunction("RotationZ", EInputType::Hold, this, &CPlayerObject::RotationZ);

	//mScene->GetInput()->AddBindKey("RotationInv", 'Q');
	//mScene->GetInput()->AddBindFunction("RotationInv", EInputType::Hold, this, &CPlayerObject::RotationZInv);

	// 총알 발사
	mScene->GetInput()->AddBindKey("Fire", VK_SPACE);
	mScene->GetInput()->AddBindFunction("Fire", EInputType::Down, this, &CPlayerObject::Fire);

	// 스킬 1 : 차징 총알
	mScene->GetInput()->AddBindKey("Skill1", '1');
	mScene->GetInput()->ChangeKeyCtrl("Skill1", true);

	mScene->GetInput()->AddBindFunction("Skill1", EInputType::Hold, this, &CPlayerObject::Skill1);
	mScene->GetInput()->AddBindFunction("Skill1", EInputType::Up, this, &CPlayerObject::Skill1Fire);

	// 스킬 2 : 토네이도 총알
	mScene->GetInput()->AddBindKey("Skill2", '2');
	mScene->GetInput()->AddBindFunction("Skill2", EInputType::Down, this, &CPlayerObject::Skill2);

	//// 스킬 3 : 위성 발사
	//mScene->GetInput()->AddBindKey("Skill3", '3');
	//mScene->GetInput()->AddBindFunction("Skill3", EInputType::Down, this, &CPlayerObject::Skill3);

	//// 스킬 4 : 돌아가는 위성의 범위를 늘렸다가 몇초후 다시 되돌아오기, 가능하면 위성의 속도도 늘렸다가 줄이기
	//mScene->GetInput()->AddBindKey("Skill4", '4');
	//mScene->GetInput()->AddBindFunction("Skill4", EInputType::Down, this, &CPlayerObject::Skill4);

	// 스킬 5 : 롤 탈론 궁극기 만들기 (플레이어 기준으로 8방향으로 총알을 발사하고 해당 총알이 몇초 돌다가 플레이어에게 다시 되돌아오는 부메랑 기능)
	mScene->GetInput()->AddBindKey("Skill5", '5');
	mScene->GetInput()->AddBindFunction("Skill5", EInputType::Down, this, &CPlayerObject::Skill5);

	// 스킬 6 : 오버워치 자리야 궁 (MonsterObject 끌어당기기)
	mScene->GetInput()->AddBindKey("Skill6", '6');
	mScene->GetInput()->AddBindFunction("Skill6", EInputType::Down, this, &CPlayerObject::Skill6);

	// 스킬 7 : MonsterObject 모두 밀쳐내기
	mScene->GetInput()->AddBindKey("Skill7", '7');
	mScene->GetInput()->AddBindFunction("Skill7", EInputType::Down, this, &CPlayerObject::Skill7);

	// 스킬 8 : 지속데미지 총알 (지속데미지 총알 범위 안에 있는 모든 몬스터들 전부에게)
	mScene->GetInput()->AddBindKey("Skill8", '8');
	mScene->GetInput()->AddBindFunction("Skill8", EInputType::Down, this, &CPlayerObject::Skill8);

	// 스킬 9 : 관통 총알 (지금은 바로 총알이 충돌하면 사라지지만 원하는 수를 지정해서 그 수만큼은 관통되게 만들어준다.) 
	mScene->GetInput()->AddBindKey("Skill9", '9');
	mScene->GetInput()->AddBindFunction("Skill9", EInputType::Down, this, &CPlayerObject::Skill9);

	return true;
}

void CPlayerObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	mSusie->SetPivot(0.5f, 0.5f);
	mRalsei->SetPivot(0.5f, 0.5f);

	bool IsMoving = (mMovement->GetVelocityLength() > 0.f);

	int SusieDelay = 900;
	int RalseiDelay = 1800;

	// 수지 랄세이 이동
	if (IsMoving)
	{
		size_t TrailSize = mTrail.size();

		if (TrailSize > SusieDelay)
		{
			mSusie->SetWorldPos(mTrail[TrailSize - SusieDelay]);
		}

		if (TrailSize > RalseiDelay)
		{
			mRalsei->SetWorldPos(mTrail[TrailSize - RalseiDelay]);
		}
	}

	if (IsMoving)
	{
		mTrail.push_back(GetWorldPosition());

		if (mTrail.size() > 2000)
		{
			mTrail.erase(mTrail.begin());
		}
	}

	if (mMovement->GetVelocityLength() == 0.f && mAutoBasePose)
	{
		mAnimation->ChangeAnimation("None");
	}

	// 위성을 돌려주면 된다.
	//FVector3D Rot = mRotationPivot->GetRelativeRotation();
	//Rot.z += DeltaTime * 180.f;
	//mRotationPivot->SetRelativeRotationZ(Rot.z);

	//// 스킬 3
	//if (mSkill3Enable)
	//{
	//	Skill3Update(DeltaTime);
	//}

	//// 스킬 4
	//if (mSkill4Enable)
	//{
	//	Skill4Update(DeltaTime);
	//}
}

void CPlayerObject::Damage(float Damage)
{
	mHp -= Damage;
}

void CPlayerObject::MoveUp(float DeltaTime)
{
	//FVector3D Pos = mRootComponent->GetWorldPosition();
	//// FVector3D Dir = { 0.f, 1.f, 0.f }; 기존꺼
	//FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);

	//mRootComponent->SetWorldPos(Pos + Dir * DeltaTime * 3.f);
	mAnimation->ChangeAnimation("KrisWalkUp");

	if (mIsUpCollision)
	{
		return;
	}

	mMovement->AddMove(mRoot->GetAxis(EAxis::Y));
}

void CPlayerObject::MoveDown(float DeltaTime)
{
	//FVector3D Pos = mRootComponent->GetWorldPosition();
	//// FVector3D Dir = { 0.f, -1.f, 0.f }; 기존꺼
	//FVector3D Dir = mRootComponent->GetAxis(EAxis::DownY);

	//mRootComponent->SetWorldPos(Pos + Dir * DeltaTime * -3.f);
	mAnimation->ChangeAnimation("KrisWalkDown");

	if (mIsDownCollision)
	{
		return;
	}

	mMovement->AddMove(mRoot->GetAxis(EAxis::Y) * -1.f);
}

void CPlayerObject::MoveLeft(float DeltaTime)
{
	mAnimation->ChangeAnimation("KrisWalkLeft");

	if (mIsLeftCollision)
	{
		return;
	}

	mMovement->AddMove(mRoot->GetAxis(EAxis::X) * -1.f);
}

void CPlayerObject::MoveRight(float DeltaTime)
{
	mAnimation->ChangeAnimation("KrisWalkRight");

	if (mIsRightCollision)
	{
		return;
	}

	mMovement->AddMove(mRoot->GetAxis(EAxis::X));
}

void CPlayerObject::RotationZ(float DeltaTime)
{
	//FVector3D Rot = mRootComponent->GetWorldRotation();
	//mRootComponent->SetWorldRotationZ(Rot.z + 90.f * DeltaTime);

	mRotation->AddMoveZ(-90.f);
}

void CPlayerObject::RotationZInv(float DeltaTime)
{
	//FVector3D Rot = mRootComponent->GetWorldRotation();
	//mRootComponent->SetWorldRotationZ(Rot.z + -90.f * DeltaTime);

	mRotation->AddMoveZ(90.f);
}

void CPlayerObject::Fire(float DeltaTime)
{
	mAnimation->ChangeAnimation("KrisAttack");
	mAutoBasePose = false;

	// 총알을 만들것이고
	CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");
	Bullet->SetBulletCollisionProfile("PlayerAttack");

	CSceneComponent* Root = Bullet->GetRootComponent();
	// 총알의 시작 위치 == 내 월드 위치
	Root->SetWorldPos(mRootComponent->GetWorldPosition());
	Root->SetWorldRotation(mRootComponent->GetWorldRotation());
	Root->SetWorldScale(30.f, 30.f, 1.f);
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

	Scale.x += 200.f * DeltaTime;
	Scale.y += 200.f * DeltaTime;

	if (Scale.x >= 400.f)
	{
		Scale.x = 400.f;
	}

	if (Scale.y >= 400.f)
	{
		Scale.y = 400.f;
	}

	mSkill1Object->GetRootComponent()->SetWorldScale(Scale);
}

void CPlayerObject::Skill1Fire(float DeltaTime)
{
	mSkill1Object->SetBulletSpeed(300.f);
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
	Bullet->SetLifeTime(2.f);
}

void CPlayerObject::Skill3(float DeltaTime)
{
	// 스킬이 발동중이니?
	if (!mSkill3Enable)
	{
		mSkill3Enable = true;
		mSkill3Time = 3.f;
		mSkill3TimeAcc = 0.f;
		mSkill3Interval = 0.3f;
	}
}

void CPlayerObject::Skill3Update(float DeltaTime)
{
	mSkill3TimeAcc += DeltaTime;

	if (mSkill3TimeAcc >= mSkill3Interval)
	{
		mSkill3TimeAcc -= mSkill3Interval;

		// 총알을 발사한다.
		CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("SatelliteBullet");

		CSceneComponent* Root = Bullet->GetRootComponent();
		// 총알의 시작 위치 == 내 월드 위치
		Root->SetWorldPos(mSub->GetWorldPosition());
		Root->SetWorldRotation(mRootComponent->GetWorldRotation());
		Root->SetWorldScale(50.f, 50.f, 1.f);
		Bullet->SetLifeTime(2.f);

		Bullet = mScene->CreateObj<CBulletObject>("SatelliteBullet");
		Root = Bullet->GetRootComponent();
		// 총알의 시작 위치 == 내 월드 위치
		Root->SetWorldPos(mSub2->GetWorldPosition());
		Root->SetWorldRotation(mRootComponent->GetWorldRotation());
		Root->SetWorldScale(50.f, 50.f, 1.f);
		Bullet->SetLifeTime(2.f);
	}

	mSkill3Time -= DeltaTime;

	if (mSkill3Time <= 0.f)
	{
		mSkill3Enable = false;
	}
}

void CPlayerObject::Skill4(float DeltaTime)
{
	if (!mSkill4Enable)
	{
		mSkill4Enable = true;
		mSkill4Time = 6.f;
		mSkill4TimeAcc = 0.f;
	}
}

void CPlayerObject::Skill4Update(float DeltaTime)
{
	mSkill4TimeAcc += DeltaTime;

	if (mSkill4TimeAcc < 2.f)
	{
		// 위성이 멀어지기
		FVector3D Pos = mSub->GetRelativePosition();
		Pos.x += DeltaTime * -150.f;
		mSub->SetRelativePos(Pos);

		FVector3D Pos2 = mSub2->GetRelativePosition();
		Pos2.x += DeltaTime * 150.f;
		mSub2->SetRelativePos(Pos2);

		// 속도 증가
		FVector3D Rot = mRotationPivot->GetRelativeRotation();
		Rot.z += DeltaTime * 270.f;		// 초당 270도 회전
		mRotationPivot->SetRelativeRotationZ(Rot.z);
	}
	else if (mSkill4TimeAcc >= 2.f && mSkill4TimeAcc < 4.f)
	{
		// 속도만 증가하고 그 자리에서 유지
		FVector3D Rot = mRotationPivot->GetRelativeRotation();
		Rot.z += DeltaTime * 270.f;
		mRotationPivot->SetRelativeRotationZ(Rot.z);
	}
	else if (mSkill4TimeAcc >= 4.f && mSkill4TimeAcc <= 6.f)
	{
		// 위성이 돌아오기
		FVector3D Pos = mSub->GetRelativePosition();
		Pos.x -= DeltaTime * -150.f;
		mSub->SetRelativePos(Pos);

		FVector3D Pos2 = mSub2->GetRelativePosition();
		Pos2.x -= DeltaTime * 150.f;
		mSub2->SetRelativePos(Pos2);

		FVector3D Rot = mRotationPivot->GetRelativeRotation();
		Rot.z += DeltaTime * 180.f;
		mRotationPivot->SetRelativeRotationZ(Rot.z);
	}

	if (mSkill4TimeAcc >= mSkill4Time)
	{
		mSkill4Enable = false;
	}
}

void CPlayerObject::Skill5(float DeltaTime)
{
	//8방향으로 총알 발사
	FVector3D Dir = mRoot->GetAxis(EAxis::Y);
	FVector3D Rot = mRoot->GetWorldRotation();

	FMatrix matRot;
	matRot.RotationZ(45.f);

	for (int i = 0; i < 8; ++i)
	{
		CTalonR* Bullet = mScene->CreateObj<CTalonR>("TalonBullet");

		CSceneComponent* Root = Bullet->GetRootComponent();
		FVector3D Pos = mRoot->GetWorldPosition();
		Root->SetWorldPos(Pos + Dir);
		Root->SetWorldRotation(Rot);
		Root->SetWorldScale(50.f, 50.f, 1.f);
		Rot.z += 45;

		Dir = Dir.TransformNormal(matRot);
		Dir.Normalize();
		Bullet->SetTarget(this);
	}
}

void CPlayerObject::Skill6(float DeltaTime)
{
	CZaryaBullet* Bullet = mScene->CreateObj<CZaryaBullet>("ZaryaBullet");

	Bullet->SetWorldRotation(GetWorldRotation());
	Bullet->SetWorldPos(GetWorldPosition());
	Bullet->SetLifeTime(3.f);

	Bullet->SetState(EZaryaState::Attraction);
}

void CPlayerObject::Skill7(float DeltaTime)
{
	CZaryaBullet* Bullet = mScene->CreateObj<CZaryaBullet>("ZaryaPushBullet");

	Bullet->SetWorldRotation(GetWorldRotation());
	Bullet->SetWorldPos(GetWorldPosition());
	Bullet->SetLifeTime(3.f);

	Bullet->SetState(EZaryaState::Push);
}

void CPlayerObject::Skill8(float DeltaTime)
{
	CContinuousdamageBullet* Bullet = mScene->CreateObj<CContinuousdamageBullet>("ContinuousBullet");

	Bullet->SetWorldRotation(GetWorldRotation());
	Bullet->SetWorldPos(GetWorldPosition());
	Bullet->SetLifeTime(5.f);
}

void CPlayerObject::Skill9(float DeltaTime)
{
	CPenetrationBullet* Bullet = mScene->CreateObj<CPenetrationBullet>("PenetrationBullet");

	Bullet->SetWorldRotation(GetWorldRotation());
	Bullet->SetWorldPos(GetWorldPosition());
	Bullet->SetLifeTime(3.f);
}

void CPlayerObject::AttackEnd()
{
	//CLog::PrintLog("AttackEnd");
	mAutoBasePose = true;
}

void CPlayerObject::AttackNotify()
{
	//CLog::PrintLog("AttackStart");
}

void CPlayerObject::OnCollisionBegin(const FVector3D& HitPoint, CColliderBase* Dest)
{
	CColliderAABB2D* Wall = dynamic_cast<CColliderAABB2D*>(Dest);
	if (!Wall)
	{
		return;
	}

	const FAABB2D& PlayerBox = mBody->GetBox();
	const FAABB2D& WallBox = Wall->GetBox();

	float EmptyLine = 2.f;

	// 왼쪽
	mLine[0].Start.x = PlayerBox.Min.x;
	mLine[0].Start.y = PlayerBox.Min.y + EmptyLine;
	mLine[0].End.x = PlayerBox.Min.x;
	mLine[0].End.y = PlayerBox.Max.y - EmptyLine;

	// 위
	mLine[1].Start.x = PlayerBox.Min.x + EmptyLine;
	mLine[1].Start.y = PlayerBox.Max.y;
	mLine[1].End.x = PlayerBox.Max.x - EmptyLine;
	mLine[1].End.y = PlayerBox.Max.y;

	// 오른쪽
	mLine[2].Start.x = PlayerBox.Max.x;
	mLine[2].Start.y = PlayerBox.Max.y - EmptyLine;
	mLine[2].End.x = PlayerBox.Max.x;
	mLine[2].End.y = PlayerBox.Min.y + EmptyLine;

	// 바닥
	mLine[3].Start.x = PlayerBox.Max.x - EmptyLine;
	mLine[3].Start.y = PlayerBox.Min.y;
	mLine[3].End.x = PlayerBox.Min.x + EmptyLine;
	mLine[3].End.y = PlayerBox.Min.y;

	FVector3D LineHitPoint;
	if (CCollision::CollisionLine2DToAABB2D(LineHitPoint, mLine[0], WallBox))
	{
		mIsLeftCollision = true;
	}

	if (CCollision::CollisionLine2DToAABB2D(LineHitPoint, mLine[1], WallBox))
	{
		mIsUpCollision = true;
	}

	if (CCollision::CollisionLine2DToAABB2D(LineHitPoint, mLine[2], WallBox))
	{
		mIsRightCollision = true;
	}

	if (CCollision::CollisionLine2DToAABB2D(LineHitPoint, mLine[3], WallBox))
	{
		mIsDownCollision = true;
	}
}

void CPlayerObject::OnCollisionEnd(CColliderBase* Dest)
{
	if (mIsLeftCollision)
	{
		mIsLeftCollision = false;
	}
	
	if (mIsRightCollision)
	{
		mIsRightCollision = false;
	}

	if (mIsUpCollision)
	{
		mIsUpCollision = false;
	}

	if (mIsDownCollision)
	{
		mIsDownCollision = false;
	}
}