#pragma once
#include "SceneObject.h"

class CPenetrationBullet : public CSceneObject
{
	friend class CScene;

private:
	int mPenetrateCount = 0;	// 관통 횟수

	CSharedPtr<CSceneObject> mTarget;

protected:
	CSharedPtr<class CStaticMeshComponent> mMesh;
	CSharedPtr<class CColliderOBB2D> mBody;
	CSharedPtr<class CMovementComponent> mMovement;
	CSharedPtr<class CRotationComponent> mRotation;

protected:
	CPenetrationBullet();
	CPenetrationBullet(const CPenetrationBullet& Obj);
	CPenetrationBullet(CPenetrationBullet&& Obj);
	virtual ~CPenetrationBullet();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void CollisionBullet(const FVector3D& HitPoint, class CColliderBase* Dest);
};

