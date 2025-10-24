#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"

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

	return true;
}