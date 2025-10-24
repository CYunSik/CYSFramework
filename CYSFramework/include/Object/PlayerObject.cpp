#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"

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
	CStaticMeshComponent* Root = CreateComponent<CStaticMeshComponent>();

	Root->SetMesh("CenterRect");
	Root->SetShader("ColorMeshShader");

	Root->SetWorldPos(0.f, 0.f, 1.5f);
	SetRootComponent(Root);

	// 입력
	mScene->GetInput()->AddBindKey("MoveUp", 'W');
	mScene->GetInput()->AddBindKey("MoveDown", 'S');

	mScene->GetInput()->AddBindFunction("MoveUp", EInputType::Hold, this, &CPlayerObject::MoveUp);
	mScene->GetInput()->AddBindFunction("MoveDown", EInputType::Hold, this, &CPlayerObject::MoveDown);

	// 회전
	mScene->GetInput()->AddBindKey("RotationZ", 'D');
	mScene->GetInput()->AddBindKey("RotationInv", 'A');

	mScene->GetInput()->AddBindFunction("RotationZ", EInputType::Hold, this, &CPlayerObject::RotationZ);
	mScene->GetInput()->AddBindFunction("RotationInv", EInputType::Hold, this, &CPlayerObject::RotationZInv);

	return true;
}

void CPlayerObject::MoveUp(float DeltaTime)
{
	FVector3D Pos = mRootComponent->GetWorldPosition();
	FVector3D Dir = { 0.f, 1.f, 0.f };

	mRootComponent->SetWorldPos(Pos + Dir * DeltaTime);
}

void CPlayerObject::MoveDown(float DeltaTime)
{
	FVector3D Pos = mRootComponent->GetWorldPosition();
	FVector3D Dir = { 0.f, -1.f, 0.f };

	mRootComponent->SetWorldPos(Pos + Dir * DeltaTime);
}

void CPlayerObject::RotationZ(float DeltaTime)
{
	FVector3D Rot = mRootComponent->GetWorldRotation();
	mRootComponent->SetWorldRotationZ(Rot.z + 90.f * DeltaTime);
}

void CPlayerObject::RotationZInv(float DeltaTime)
{
	FVector3D Rot = mRootComponent->GetWorldRotation();
	mRootComponent->SetWorldRotationZ(Rot.z + -90.f * DeltaTime);
}