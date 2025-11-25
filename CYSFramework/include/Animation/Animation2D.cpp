#include "Animation2D.h"

#include "../Asset/AssetManager.h"
#include "../Asset/Animation/Animation2DData.h"
#include "../Asset/Animation/Animation2DManager.h"
#include "../Component/SpriteComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneAssetManager.h"

CAnimation2D::CAnimation2D()
{
}

CAnimation2D::CAnimation2D(const CAnimation2D& Anim)
{
}

CAnimation2D::~CAnimation2D()
{
}

bool CAnimation2D::Init()
{
	return true;
}

void CAnimation2D::Update(float DeltaTime)
{
	mCurrentSequence->Update(DeltaTime);
}

CAnimation2DSequence* CAnimation2D::FindSequence(const std::string& Name)
{
	auto iter = mSequenceMap.find(Name);

	if (iter == mSequenceMap.end())
	{
		return nullptr;
	}

	return iter->second;
}

bool CAnimation2D::AddSequence(const std::string& Name, float PlayTime, float PlayRate, bool Loop, bool Reverse)
{
	CAnimation2DSequence* Sequence = FindSequence(Name);

	// 이미 있다. 그래서 해줄 필요 x
	if (Sequence)
	{
		return false;
	}

	// 먼저 Animation2DData가 있는가?
	CAnimation2DData* Data = nullptr;

	if (mScene)
	{
		Data = mScene->GetAssetManager()->FindAnimation(Name);
	}
	else
	{
		Data = CAssetManager::GetInst()->GetAnimationManager()->FindAnimation(Name);
	}

	if (!Data)
	{
		return false;
	}

	// 데이터를 토대로 애니메이션 시퀀스를 만들어준다.
	Sequence = new CAnimation2DSequence;

	Sequence->mOwner = this;

	Sequence->SetAsset(Data);
	Sequence->SetPlayTime(PlayTime);
	Sequence->SetPlayRate(PlayRate);
	Sequence->SetLoop(Loop);
	Sequence->SetReverse(Reverse);

	if (!mCurrentSequence)
	{
		mCurrentSequence = Sequence;
		// 기존 Sprite컴포넌트의 Texture을 애니메이션의 Texture로 변경해준다.
		mOwner->SetTexture(mCurrentSequence->GetAnimationAsset()->GetTexture());
	}

	mSequenceMap.insert(std::make_pair(Name, Sequence));

	return true;
}

bool CAnimation2D::AddSequence(class CAnimation2DData* Asset, float PlayTime, float PlayRate, bool Loop, bool Reverse)
{
	CAnimation2DSequence* Sequence = FindSequence(Asset->GetName());

	// 이미 있다. 그래서 해줄 필요 x
	if (Sequence)
	{
		return false;
	}

	// 데이터를 토대로 애니메이션 시퀀스를 만들어준다.
	Sequence = new CAnimation2DSequence;

	Sequence->mOwner = this;

	Sequence->SetAsset(Asset);
	Sequence->SetPlayTime(PlayTime);
	Sequence->SetPlayRate(PlayRate);
	Sequence->SetLoop(Loop);
	Sequence->SetReverse(Reverse);

	if (!mCurrentSequence)
	{
		mCurrentSequence = Sequence;
		// 기존 Sprite컴포넌트의 Texture을 애니메이션의 Texture로 변경해준다.
		mOwner->SetTexture(mCurrentSequence->GetAnimationAsset()->GetTexture());
	}

	mSequenceMap.insert(std::make_pair(Asset->GetName(), Sequence));

	return true;
}

void CAnimation2D::SetPlayTime(const std::string& Name, float PlayTime)
{
	CAnimation2DSequence* Sequence = FindSequence(Name);

	if (!Sequence)
	{
		return;
	}

	Sequence->SetPlayTime(PlayTime);
}

void CAnimation2D::SetPlayRate(const std::string& Name, float PlayRate)
{
	CAnimation2DSequence* Sequence = FindSequence(Name);

	if (!Sequence)
	{
		return;
	}

	Sequence->SetPlayRate(PlayRate);
}

void CAnimation2D::SetLoop(const std::string& Name, bool Loop)
{
	CAnimation2DSequence* Sequence = FindSequence(Name);

	if (!Sequence)
	{
		return;
	}

	Sequence->SetLoop(Loop);
}

void CAnimation2D::SetReverse(const std::string& Name, bool Reverse)
{
	CAnimation2DSequence* Sequence = FindSequence(Name);

	if (!Sequence)
	{
		return;
	}

	Sequence->SetReverse(Reverse);
}

void CAnimation2D::ChangeAnimation(const std::string& Name)
{
	if (Name.empty())
	{
		return;
	}
	//else if (!mCurrentSequence)
	//{
	//	return;
	//}
	else if (mCurrentSequence->GetName() == Name)
	{
		return;
	}

	// 기존 시퀀스 초기화
	mCurrentSequence->mFrame = 0;
	mCurrentSequence->mTime = 0.f;
	mCurrentSequence->mEndFunctionEnable = true;

	// 새로운 시퀀스
	CAnimation2DSequence* Sequence = FindSequence(Name);

	if (!Sequence)
	{
		return;
	}

	mCurrentSequence = Sequence;
	mCurrentSequence->mFrame = 0;
	mCurrentSequence->mTime = 0.f;

	mOwner->SetTexture(mCurrentSequence->GetAnimationAsset()->GetTexture());
}

CAnimation2D* CAnimation2D::Clone()
{
	return new CAnimation2D(*this);
}
