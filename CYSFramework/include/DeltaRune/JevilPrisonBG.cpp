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
	mBody2 = CreateComponent<CColliderAABB2D>();
	SetRootComponent(mBackGround);

	// 배경
	mBackGround->SetPivot(0.5f, 0.5f);
	mBackGround->SetWorldScale(1840.f, 1200.f);
	mBackGround->SetTexture("JevilPrisonBG", TEXT("Texture/Jevil/beforeJevilBG.png"), 0);

	// 길 콜라이더
	mBody->SetBoxSize(300.f, 10.f);
	mBody->SetRelativePos(-1200.f, 370.f, 5.f);

	mBody2->SetBoxSize(10.f, 300.f);
	mBody2->SetRelativePos(-1300.f, 370.f, 5.f);

	mBackGround->AddChild(mBody);
	mBackGround->AddChild(mBody2);

	return true;
}

void CJevilPrisonBG::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
}
