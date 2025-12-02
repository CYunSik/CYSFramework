#include "JevilBossObject.h"

#include "../Component/SpriteComponent.h"

CJevilBossObject::CJevilBossObject()
{
}

CJevilBossObject::CJevilBossObject(const CJevilBossObject& Obj)
	: CSceneObject(Obj)
{
}

CJevilBossObject::CJevilBossObject(CJevilBossObject&& Obj)
	: CSceneObject(Obj)
{
}

CJevilBossObject::~CJevilBossObject()
{
}

bool CJevilBossObject::Init()
{
	CSceneObject::Init();

	mRoot = CreateComponent<CSpriteComponent>();
	mRoot2 = CreateComponent<CSpriteComponent>();
	mRoot3 = CreateComponent<CSpriteComponent>();
	//mRoot->SetTexture("JevilMain", TEXT("Texture/Jevil/spr_joker_main/spr_joker_main_0.png"), 0);
	mRoot->SetWorldScale(80.f, 90.f);
	mRoot->SetPivot(0.5f, 0.5f);
	SetRootComponent(mRoot);

	mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
	mAnimation->AddSequence("JevilDance", 0.7f, 1.f, true, false);

	mRoot2->SetRelativePos(-70.f, -10.f);
	mRoot2->SetRelativeScale(1.f, 1.f);
	mRoot2->SetPivot(0.5f, 0.5f);
	mRoot2->SetOpacity(0.8f);

	mAnimation2 = mRoot2->CreateAnimation2D<CAnimation2D>();
	mAnimation2->AddSequence("JevilDanceReverse", 0.6f, 1.f, true, false);

	mRoot3->SetRelativePos(70.f, 10.f);
	mRoot3->SetRelativeScale(1.f, 1.f);
	mRoot3->SetPivot(0.5f, 0.5f);
	mRoot3->SetOpacity(0.5f);

	mAnimation3 = mRoot3->CreateAnimation2D<CAnimation2D>();
	mAnimation3->AddSequence("JevilDanceReverse", 0.5f, 1.f, true, false);

	mRoot->AddChild(mRoot2);
	mRoot->AddChild(mRoot3);

	return true;
}

void CJevilBossObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
}
