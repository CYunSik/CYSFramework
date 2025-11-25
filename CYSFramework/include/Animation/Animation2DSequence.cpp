#include "Animation2DSequence.h"
#include "Animation2D.h"
#include "../Asset/Animation/Animation2DData.h"

CAnimation2DSequence::CAnimation2DSequence()
{
}

CAnimation2DSequence::CAnimation2DSequence(const CAnimation2DSequence& Anim)
{
	// 얕은 복사
	*this = Anim;
}

CAnimation2DSequence::~CAnimation2DSequence()
{
}

const std::string& CAnimation2DSequence::GetName() const
{
	return mAsset->GetName();
}

void CAnimation2DSequence::SetAsset(class CAnimation2DData* Asset)
{
	mAsset = Asset;

	mFrameTime = mPlayTime / mAsset->GetFrameCount();
}

void CAnimation2DSequence::SetPlayTime(float PlayTime)
{
	mPlayTime = PlayTime;

	if (mAsset)
	{
		mFrameTime = mPlayTime / mAsset->GetFrameCount();
	}
}

void CAnimation2DSequence::Update(float DelaTime)
{
	// 프레임 계산을 해준다.
	mTime += DelaTime * mPlayRate;

	if (mTime >= mFrameTime)
	{
		mTime -= mFrameTime;

		// 역재생인지
		if (mReverse)
		{
			--mFrame;

			if (mFrame < 0)
			{
				// 마지막 프레임이네?
				// EndFunction이 허용되어 있고 함수가 바인드 되어있니?
				if (mEndFunctionEnable && mEndFunction)
				{
					mEndFunctionEnable = false;
					mEndFunction();
				}

				if (mLoop)
				{
					mEndFunctionEnable = true;
					mFrame = mAsset->GetFrameCount() - 1;
				}
				else
				{
					mFrame = 0;
				}
			}
		}
		// 정상재생
		else
		{
			++mFrame;

			if (mFrame == mAsset->GetFrameCount())
			{
				if (mEndFunctionEnable && mEndFunction)
				{
					mEndFunctionEnable = false;
					mEndFunction();
				}

				if (mLoop)
				{
					mEndFunctionEnable = true;
					mFrame = mAsset->GetFrameCount() - 1;
				}
				else
				{
					// 마지막 이미지 반복재생
					// 루프가 아닐때
					mFrame = mAsset->GetFrameCount() - 1;
				}
			}
		}
		// 계산한 mFrame을 가지고 현재 실행시켜줄 Notify가 있는가?
		CallNotify();
	}
}

CAnimation2DSequence* CAnimation2DSequence::Clone()
{
	return new CAnimation2DSequence(*this);
}

void CAnimation2DSequence::CallNotify()
{
	size_t Size = mNotifyList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		// 해당 프레임 때
		if (mNotifyList[i]->Frame == mFrame)
		{
			// 함수 포인터가 있으면
			if (mNotifyList[i]->Function)
			{
				// 함수 실행
				mNotifyList[i]->Function();
			}
		}
	}
}
