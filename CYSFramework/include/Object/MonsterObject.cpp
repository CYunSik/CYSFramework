#include "MonsterObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"

#include "BulletObject.h"
#include "../Scene/Scene.h"
#include "../Share/Log.h"
#include "ObjectSpawnPoint.h"
#include "../Component/MovementComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Animation/Animation2D.h"

#include "../Component/WidgetComponent.h"
#include "../Scene/SceneUIManager.h"
#include "../UI/UserWidget/HeadInfo.h"

CMonsterObject::CMonsterObject()
{
	mState = EMonsterState::Idle;
}

CMonsterObject::CMonsterObject(const CMonsterObject& Obj)
	: CSceneObject(Obj)
{
	mState = EMonsterState::Idle;
}

CMonsterObject::CMonsterObject(CMonsterObject&& Obj)
	: CSceneObject(Obj)
{
	mState = EMonsterState::Idle;
}

CMonsterObject::~CMonsterObject()
{
}

void CMonsterObject::Idle(float DeltaTime)
{
}

void CMonsterObject::Recone(float DeltaTime)
{
}

void CMonsterObject::Research(float DeltaTime)
{
}

void CMonsterObject::Move(float DeltaTime)
{
}

void CMonsterObject::Attack(float DeltaTime)
{
}

void CMonsterObject::CollisionMonster(const FVector3D& HitPoint, CColliderBase* Dest)
{
	//CLog::PrintLog("CollisionBegin");

	// Dest->GetProfile()->Channel == ECollisionChannel::PlayerAttack();

}

void CMonsterObject::CollisionMonsterEnd(CColliderBase* Dest)
{
	//CLog::PrintLog("CollisionEnd");
}

float CMonsterObject::Damage(float Attack, CSceneObject* Obj)
{
	float Dmg = CSceneObject::Damage(Attack, Obj);

	mHP -= (int)Dmg;

	if (mHP <= 0)
	{
		if (mSpawnPoint != nullptr)
		{
			mSpawnPoint->ClearObject();
		}
		Destroy();
	}

	return Dmg;
}

bool CMonsterObject::Init()
{
	if (!CSceneObject::Init())
	{
		return false;
	}

	mRoot = CreateComponent<CSpriteComponent>();
	mMovement = CreateComponent<CMovementComponent>();
	//mBody = CreateComponent<CColliderAABB2D>();
	//mBody = CreateComponent<CColliderSphere2D>();
	//mBody = CreateComponent<CColliderOBB2D>();

	CHeadInfo* Widget = mScene->GetUIManager()->CreateWidget<CHeadInfo>("HeadInfo");

	mWidgetComponent = CreateComponent<CWidgetComponent>();
	mWidgetComponent->SetWidget(Widget);

	mRoot->AddChild(mWidgetComponent);
	
	SetRootComponent(mRoot);

	//mRoot->AddChild(mBody);
	//mBody->SetBoxSize(50.f, 50.f);
	//mBody->SetRadius(50.f);
	//mBody->SetCollisionProfile("Monster");
	//mBody->SetCollisionBeginFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonster);
	//mBody->SetCollisionEndFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonsterEnd);

	//mRoot->AddChild(mRoot2);

	mMovement->SetUpdateComponent(mRoot);

	return true;
}

void CMonsterObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	if (!mTarget->IsActive())
	{
		mTarget = nullptr;
		return;
	}
	else if (!mTarget->IsEnable())
	{
		return;
	}

	//FSM
	//유한 상태 기계
	switch (mState)
	{
	case EMonsterState::Idle:
		Idle(DeltaTime);
		break;
	case EMonsterState::Recone:
		Recone(DeltaTime);
		break;
	case EMonsterState::Research:
		Research(DeltaTime);
		break;
	case EMonsterState::Move:
		Move(DeltaTime);
		break;
	case EMonsterState::Attack:
		Attack(DeltaTime);
		break;
	}
}
