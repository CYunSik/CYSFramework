#pragma once
#include "SceneComponent.h"

enum class ECameraProjectionType
{
	Perspective,	// 원근 투영
	Ortho			// 직교 투영
};

class CCameraComponent : public CSceneComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CCameraComponent();
	CCameraComponent(const CCameraComponent& Com);
	CCameraComponent(CCameraComponent&& Com);
	virtual ~CCameraComponent();

protected:
	// 카메라 투영 방식
	ECameraProjectionType mProjType = ECameraProjectionType::Perspective;
	// 뷰(카메라) 행렬
	FMatrix mMatView;
	// 투영 행렬
	FMatrix mMatProj;

	float mViewAngle = 90.f;
	float mWidth = 1280.f;
	float mHeight = 720.f;
	float mViewDistance = 1000.f;

public:
	const FMatrix& GetViewMatrix() const
	{
		return mMatView;
	}

	const FMatrix& GetProjMatrix() const
	{
		return mMatProj;
	}

public:
	void SetProjectionType(ECameraProjectionType Type);
	void SetViewAngle(float Angle)
	{
		mViewAngle = Angle;
	}

	void SetViewResolution(float Width, float Height)
	{
		mWidth = Width;
		mHeight = Height;
	}

	void SetViewDistance(float Dist)
	{
		mViewDistance = Dist;
	}

public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual CSceneComponent* Clone();
};

