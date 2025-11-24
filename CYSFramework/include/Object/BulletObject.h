#pragma once
#include "SceneObject.h"

class CBulletObject : public CSceneObject
{
	friend class CScene;

private:
	float mSpeed = 300.f;

public:
	float GetBulletSpeed() const
	{
		return mSpeed;
	}

	void SetBulletSpeed(const float& Speed)
	{
		mSpeed = Speed;
	}

	// 총알 오브젝트의 충돌체의 profile을 설정해주는거 만들고
	// 각각의 총알타입에 맞게 변경해주기
	void SetBulletCollisionProfile(const std::string& Name);

protected:
	CSharedPtr<class CSpriteComponent> mRoot;
	CSharedPtr<class CColliderSphere2D> mBody;
	CSharedPtr<class CMovementComponent> mMovement;
	CSharedPtr<class CRotationComponent> mRotation;

protected:
	CBulletObject();
	CBulletObject(const CBulletObject& Obj);
	CBulletObject(CBulletObject&& Obj);
	virtual ~CBulletObject();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void CollisionBullet(const FVector3D& HitPoint, class CColliderBase* Dest);
};

