#include "MonsterObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"

#include "BulletObject.h"
#include "../Scene/Scene.h"
#include "../Share/Log.h"
#include "ObjectSpawnPoint.h"

CMonsterObject::CMonsterObject()
{
}

CMonsterObject::CMonsterObject(const CMonsterObject& Obj)
	: CSceneObject(Obj)
{
}

CMonsterObject::CMonsterObject(CMonsterObject&& Obj)
	: CSceneObject(Obj)
{
}

CMonsterObject::~CMonsterObject()
{
}

void CMonsterObject::CollisionMonster(const FVector3D& HitPoint, CColliderBase* Dest)
{
	CLog::PrintLog("CollisionMonster");

	// Dest->GetProfile()->Channel == ECollisionChannel::PlayerAttack();

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

	mRoot = CreateComponent<CStaticMeshComponent>();
	//mBody = CreateComponent<CColliderAABB2D>();
	//mBody = CreateComponent<CColliderSphere2D>();
	mBody = CreateComponent<CColliderOBB2D>();

	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");
	mRoot->SetWorldScale(100.f, 100.f);
	
	SetRootComponent(mRoot);

	mRoot->AddChild(mBody);
	mBody->SetBoxSize(100.f, 100.f);
	//mBody->SetRadius(50.f);
	mBody->SetCollisionProfile("Monster");
	mBody->SetCollisionBeginFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonster);

	return true;
}

void CMonsterObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	if (!mTarget->IsActive())
	{
		mTarget = nullptr;
	}
	else if (mTarget->IsEnable())
	{
		// TODO::
	}
	
}
