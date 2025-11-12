#pragma once
#include "SceneObject.h"

class CContinuousdamageBullet : public CSceneObject
{
	friend class CScene;

private:
	float mRadius = 300.f;		// 범위
	float mDamageInterval = 1.f;	// 공격 주기

	std::unordered_map<class CMonsterObject*, float> mMonsterDamageTimers;

	CSharedPtr<CSceneObject> mTarget;

protected:
	CSharedPtr<class CStaticMeshComponent> mMesh;
	CSharedPtr<class CStaticMeshComponent> mCircle;
	CSharedPtr<class CColliderOBB2D> mBody;
	CSharedPtr<class CMovementComponent> mMovement;
	CSharedPtr<class CRotationComponent> mRotation;

protected:
	CContinuousdamageBullet();
	CContinuousdamageBullet(const CContinuousdamageBullet& Obj);
	CContinuousdamageBullet(CContinuousdamageBullet&& Obj);
	virtual ~CContinuousdamageBullet();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void CollisionBullet(const FVector3D& HitPoint, class CColliderBase* Dest);
};

