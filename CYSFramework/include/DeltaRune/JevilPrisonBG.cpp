#include "JevilPrisonBG.h"

#include "../Component/SpriteComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Scene/Scene.h"

CJevilPrisonBG::CJevilPrisonBG()
{
}

CJevilPrisonBG::CJevilPrisonBG(const CJevilPrisonBG& Obj)
	: CSceneObject(Obj)
{
}

CJevilPrisonBG::CJevilPrisonBG(CJevilPrisonBG&& Obj)
	: CSceneObject(Obj)
{
}

CJevilPrisonBG::~CJevilPrisonBG()
{
}

bool CJevilPrisonBG::Init()
{
	CSceneObject::Init();

	if (!CSceneObject::Init())
	{
		return false;
	}

	mBackGround = CreateComponent<CSpriteComponent>();
	mBody = CreateComponent<CColliderAABB2D>();
	SetRootComponent(mBackGround);

	// 배경
	mBackGround->SetPivot(0.5f, 0.5f);
	mBackGround->SetWorldScale(1840.f, 1200.f, 2.f);
	mBackGround->SetTexture("JevilPrisonBG", TEXT("Texture/Jevil/beforeJevilBG.png"), 0);

	// 길 콜라이더
	mBody->SetBoxSize(500.f, 10.f);
	mBody->SetRelativePos(0.f, 370.f, 1.f);

	mBackGround->AddChild(mBody);

	return true;
}

void CJevilPrisonBG::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
}
