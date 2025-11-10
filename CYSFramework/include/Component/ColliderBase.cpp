#include "ColliderBase.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneCollision.h"
#include "../ProfileManager.h"

#include "../Shader/TransformCBuffer.h"
#include "../Shader/ColliderCBuffer.h"
#include "../Shader/Shader.h"
#include "../Shader/ShaderManager.h"
#include "../Asset/Mesh/Mesh.h"
#include "../Asset/Mesh/MeshManager.h"
#include "../Scene/CameraManager.h"

CColliderBase::CColliderBase()
{
}

CColliderBase::CColliderBase(const CColliderBase& Com)
	: CSceneComponent(Com)
{
}

CColliderBase::CColliderBase(CColliderBase&& Com)
	: CSceneComponent(Com)
{
}

CColliderBase::~CColliderBase()
{
#ifdef _DEBUG
	SAFE_DELETE(mTransformCBuffer);
	SAFE_DELETE(mCBuffer);
#endif // _DEBUG

}

void CColliderBase::SetCollisionProfile(const std::string& Name)
{
	mProfile = CProfileManager::GetInst()->FindProfile(Name);
}

void CColliderBase::CallCollisionBegin(const FVector3D& HitPoint, CColliderBase* Dest)
{
	mCollision = true;

	if (mCollisionBeginFunc)
	{
		mCollisionBeginFunc(HitPoint, Dest);
	}
}

void CColliderBase::CallCollisionEnd(CColliderBase* Dest)
{
	// mCollision = false;

	if (mCollisionEndFunc)
	{
		mCollisionEndFunc(Dest);
	}
}

bool CColliderBase::Init()
{
	if (!CSceneComponent::Init())
	{
		return false;
	}
	
	SetCollisionProfile("Default");

	mScene->GetCollision()->AddCollider(this);

#ifdef _DEBUG
	mShader = CShaderManager::GetInst()->FindShader("FrameMeshShader");

	// Transform 상수버퍼
	mTransformCBuffer = new CTransformCBuffer;
	mTransformCBuffer->Init();

	// Collider 상수버퍼
	mCBuffer = new CColliderCBuffer;
	mCBuffer->Init();
#endif // _DEBUG

	return true;
}

bool CColliderBase::Init(const char* FileName)
{
	if (!CSceneComponent::Init(FileName))
	{
		return false;
	}

	SetCollisionProfile("Default");

	mScene->GetCollision()->AddCollider(this);

#ifdef _DEBUG
	mShader = CShaderManager::GetInst()->FindShader("FrameMeshShader");

	// Transform 상수버퍼
	mTransformCBuffer = new CTransformCBuffer;
	mTransformCBuffer->Init();

	// Collider 상수버퍼
	mCBuffer = new CColliderCBuffer;
	mCBuffer->Init();
#endif // _DEBUG

	return true;
}

void CColliderBase::PreUpdate(float DeltaTime)
{
	CSceneComponent::PreUpdate(DeltaTime);
}

void CColliderBase::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CColliderBase::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CColliderBase::Collision(float DeltaTime)
{
	CSceneComponent::Collision(DeltaTime);
}

void CColliderBase::PreRender()
{
	CSceneComponent::PreRender();
}

void CColliderBase::Render()
{
	CSceneComponent::Render();

#ifdef _DEBUG
	// Transform 상수버퍼 데이터 넣어주기
	// 크기, 위치
	FMatrix matScale, matRot, matTranslate, matWorld;
	matScale.Scaling(mWorldScale);

	if (mEnableRotation)
	{
		matRot.Rotation(mWorldRot);
	}

	matTranslate.Translation(mWorldPos);

	// 크자이공부!!
	matWorld = matScale * matRot * matTranslate;

	FMatrix matView, matProj;
	matView = mScene->GetCameraManager()->GetViewMatrix();
	matProj = mScene->GetCameraManager()->GetProjMatrix();

	mTransformCBuffer->SetWorldMatrix(matWorld);
	mTransformCBuffer->SetViewMatrix(matView);
	mTransformCBuffer->SetProjMatrix(matProj);

	mTransformCBuffer->UpdateBuffer();

	// 상수버퍼들 업데이트
	// Collider 상수버퍼 데이터 넣어주기
	// 충돌 중 : 빨강
	if (mCollision)
	{
		mCBuffer->SetColor(1.f, 0.f, 0.f, 1.f);
	}
	else
	{
		// 충돌 X : 초록
		mCBuffer->SetColor(0.f, 1.f, 0.f, 1.f);
	}

	mCBuffer->UpdateBuffer();

	// 쉐이더 세팅
	mShader->SetShader();

	// 그려라
	mMesh->Render();

#endif // _DEBUG

	mCollision = false;
}

void CColliderBase::PostRender()
{
	CSceneComponent::PostRender();
}

CColliderBase* CColliderBase::Clone()
{
	return nullptr;
}