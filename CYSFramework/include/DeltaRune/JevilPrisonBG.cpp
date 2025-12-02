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
	mNothing = CreateComponent<CSpriteComponent>();
	mBody = CreateComponent<CColliderAABB2D>();
	mBody2 = CreateComponent<CColliderAABB2D>();
	mBody3 = CreateComponent<CColliderAABB2D>();
	SetRootComponent(mBackGround);

	// 배경
	mBackGround->SetTexture("JevilPrisonBG", TEXT("Texture/Jevil/beforeJevilBG2.png"), 0);
	mBackGround->SetPivot(0.5f, 0.5f);
	mBackGround->SetWorldScale(1840.f, 1200.f);

	// 아무것도 없는 배경
	mNothing->SetTexture("Nothing", TEXT("Texture/spr_nothing.png"), 0);
	mNothing->SetPivot(0.5f, 0.5f);
	mNothing->SetWorldScale(1840.f, 1200.f);

	// 길 콜라이더
	mBody->SetBoxSize(300.f, 10.f);
	mBody->SetRelativePos(-900.f, 370.f, 5.f);

	mBody2->SetBoxSize(300.f, 10.f);
	mBody2->SetRelativePos(-1200.f, 500.f, 5.f);

	mBody3->SetBoxSize(10.f, 300.f);
	mBody3->SetRelativePos(-1200.f, 430.f, 5.f);

	mBackGround->AddChild(mNothing);
	mNothing->AddChild(mBody);
	mNothing->AddChild(mBody2);
	mNothing->AddChild(mBody3);

	return true;
}

void CJevilPrisonBG::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
}
