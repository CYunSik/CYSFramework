#pragma once
#include "SceneObject.h"

enum class EZaryaState
{
	None,
	Attraction,	// 끌어당김
	Push		// 밀치기
};

class CZaryaBullet : public CSceneObject
{
	friend class CScene;

private:
	float mActiveTime = 0.f;	// 활성화 누적 시간
	float mRadius = 500.f;		// 범위
	float mForce = 300.f;		// 힘
	EZaryaState mState = EZaryaState::None;

	CSharedPtr<CSceneObject> mTarget;

protected:
	CSharedPtr<class CStaticMeshComponent> mMesh;
	CSharedPtr<class CMovementComponent> mMovement;
	CSharedPtr<class CRotationComponent> mRotation;

protected:
	CZaryaBullet();
	CZaryaBullet(const CZaryaBullet& Obj);
	CZaryaBullet(CZaryaBullet&& Obj);
	virtual ~CZaryaBullet();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

	void SetState(EZaryaState State)
	{
		mState = State;
	}
};
