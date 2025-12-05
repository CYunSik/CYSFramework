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

	mBackGround = CreateComponent<CSpriteComponent>("BackGround");
	mDoor = CreateComponent<CSpriteComponent>();
	mBody = CreateComponent<CColliderAABB2D>();
	mBody2 = CreateComponent<CColliderAABB2D>();
	mBody3 = CreateComponent<CColliderAABB2D>();
	SetRootComponent(mBackGround);

	// 배경
	mBackGround->SetTexture("JevilPrisonBG", TEXT("Texture/Jevil/beforeJevilBG.png"), 0);
	mBackGround->SetPivot(0.5f, 0.5f);
	mBackGround->SetWorldScale(1840.f, 1200.f);

	// 문
	mDoor->SetTexture("JokerDoor", TEXT("Texture/Jevil/Door/spr_jokerdoor_2.png"), 0);
	mDoor->SetWorldPos(690.f, -385.f, 7.f);
	mDoor->SetPivot(0.5f, 0.5f);
	mDoor->SetWorldScale(0.058f, 0.19f);

	mBody->SetBoxSize(300.f, 10.f);

	// 길 콜라이더
	mBody2->SetBoxSize(300.f, 10.f);
	mBody2->SetRelativePos(-1200.f, 500.f, 5.f);

	mBody3->SetBoxSize(10.f, 300.f);
	mBody3->SetRelativePos(-1200.f, 430.f, 5.f);

	// 제빌씬 넘어가기 콜라이더

	mBackGround->AddChild(mDoor);
	mDoor->AddChild(mBody);
	mBackGround->AddChild(mBody2);
	mBackGround->AddChild(mBody3);

	return true;
}

void CJevilPrisonBG::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
}
