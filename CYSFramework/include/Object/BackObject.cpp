#include "BackObject.h"

#include "../Component/SpriteComponent.h"

CBackObject::CBackObject()
{
}

CBackObject::CBackObject(const CBackObject& Obj)
{
}

CBackObject::CBackObject(CBackObject&& Obj)
{
}

CBackObject::~CBackObject()
{
}

bool CBackObject::Init()
{
	CSceneObject::Init();

	mRoot = CreateComponent<CSpriteComponent>("BackGround");

	mRoot->SetTexture("BackGround", TEXT("Texture/Jevil/JevilBG2/JevilBG (1).png"), 0);
	mRoot->SetTint(1.f, 1.f, 1.f);
	mRoot->SetPivot(0.5f, 0.5f);
	mRoot->SetOpacity(1.f);
	mRoot->SetUseTime(true);

	SetRootComponent(mRoot);

	//mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
	//mAnimation->AddSequence("JevilCarousel", 15.f, 1.f, true, false);

	return true;
}
