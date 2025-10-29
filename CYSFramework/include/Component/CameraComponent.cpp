#include "CameraComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/CameraManager.h"

CCameraComponent::CCameraComponent()
{

}

CCameraComponent::CCameraComponent(const CCameraComponent& Com)
	: CSceneComponent(Com)
{

}

CCameraComponent::CCameraComponent(CCameraComponent&& Com)
	: CSceneComponent(Com)
{

}

CCameraComponent::~CCameraComponent()
{

}

void CCameraComponent::SetProjectionType(ECameraProjectionType Type)
{
	mProjType = Type;

	switch (mProjType)
	{
	case ECameraProjectionType::Perspective:	// 원근 투영

		// MeshComponent에서 썼던거
		mMatProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(mViewAngle), mWidth / mHeight, 0.5f, mViewDistance);
																 // 그려질 카메라 각도(시야각), 종횡비(카메라 비율), 최소 거리, 최대 거리
		break;
	case ECameraProjectionType::Ortho:			// 직교 투영
		mMatProj = DirectX::XMMatrixOrthographicOffCenterLH(mWidth / -2.f, mWidth / 2.f, mHeight / -2.f, mHeight / 2.f, 0, mViewDistance);
		break;
	}
}

bool CCameraComponent::Init()
{
	if (!CSceneComponent::Init())
	{
		return false;
	}

	// 초기화 할때 투영행렬 한번 계산한다.
	SetProjectionType(ECameraProjectionType::Perspective);

	// 처음 생성된 카메라 컴포넌트면 이 친구를 CameraManager의 뷰타켓으로 지정한다.
	if (!mScene->GetCameraManager()->GetViewTarget())
	{
		mScene->GetCameraManager()->SetViewTarget(this);
	}

	return true;
}
bool CCameraComponent::Init(const char* FileName)
{
	if (!CSceneComponent::Init())
	{
		return false;
	}

	// 초기화 할때 투영행렬 한번 계산한다.
	SetProjectionType(ECameraProjectionType::Perspective);

	// 처음 생성된 카메라 컴포넌트면 이 친구를 CameraManager의 뷰타켓으로 지정한다.
	if (!mScene->GetCameraManager()->GetViewTarget())
	{
		mScene->GetCameraManager()->SetViewTarget(this);
	}

	return true;
}

void CCameraComponent::PreUpdate(float DeltaTime)
{
	CSceneComponent::PreUpdate(DeltaTime);
}

void CCameraComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CCameraComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);

	// 뷰행렬 카메라 행렬을 만들 것이다.
	/*
		카메라는 월드 어딘가에 배치되어 있다.
		근데 카메라 행렬은
		그 해당 카메라 기준으로 화면을 그릴 것이기에
		해당 카메라의 위치를 (0, 0, 0) 좌표로 이동 후 Z축 +방향으로 바라보게 회전을 시킨다. 
	*/

	//카메라 축으로 뷰행렬을 구성한다.
	mMatView.Identity();	// 뷰행렬 단위행렬로 초기화

	// 카메라의 축행렬 구하기
	for (int i = 0; i < EAxis::End; ++i)
	{
		FVector3D Axis = mAxis[i];	// 카메라 축
		// 축별로 복사해온다.
		memcpy(&mMatView[i][0], &Axis, sizeof(FVector3D));
	}

	// 뷰행렬 회전 == 축행렬의 전치 행렬
	mMatView.Transpose();	// 뷰행렬의 회전값이다.

	// 카메라의 위치로 뷰행렬의 이동 행렬을 구성한다.
	for (int i = 0; i < EAxis::End; ++i)
	{
		// -X.P -Y.P -Z.P
		mMatView[3][i] = -mAxis[i].Dot(mWorldPos);
	}

	// 최종 뷰행렬이 나온다.
}

void CCameraComponent::Collision(float DeltaTime)
{
	CSceneComponent::Collision(DeltaTime);
}

void CCameraComponent::PreRender()
{
	CSceneComponent::PreRender();
}

void CCameraComponent::Render()
{
	CSceneComponent::Render();
}

void CCameraComponent::PostRender()
{
	CSceneComponent::PostRender();
}

CSceneComponent* CCameraComponent::Clone()
{
	return new CCameraComponent(*this);
}