#pragma once
#include "../GameInfo.h"

struct FAnimation2DNotify
{
	// 노티파이 이름
	std::string Name;
	// 몇번째 프레임
	int Frame = 0;
	// 호출될 함수 포인터
	std::function<void()> Function;
};

class CAnimation2DSequence
{
	friend class CAnimation2D;

private:
	CAnimation2DSequence();
	CAnimation2DSequence(const CAnimation2DSequence& Anim);
	~CAnimation2DSequence();

private:
	// 해당 시퀀스를 들고있는 Animation2D 클래스
	class CAnimation2D* mOwner = nullptr;

	// 애니메이션 정보를 하나 들고있는다.
	CSharedPtr<class CAnimation2DData> mAsset;

	// 지금 실행중인 프레임은 몇번인가?
	int mFrame = 0;

	// 프레임을 증가시키기 위한 누적 시간
	float mTime = 0.f;

	// 한 프레임이 변경하는데 필요한 시간
	float mFrameTime = 0.f;

	// 동작되는 시간
	// ex : 10개의 프레임이 있으면 10개가 한바퀴 도는 시간을 말함
	float mPlayTime = 1.f;

	// 재생속도 배율
	float mPlayRate = 1.f;

	// 반복 여부
	bool mLoop = false;

	// 역재생인지
	bool mReverse = false;

	// 함수포인터를 이용해서 애니메이션이 종료되거나 특정 프레임때 함수를 호출
	// 함수 사용 여부
	// 종료 함수 호출 여부
	bool mEndFunctionEnable = true;

	// 애니메이션이 한번 종료될때마다 호출해줄 함수
	std::function<void()> mEndFunction;

	// 원하는 프레임에 함수를 호출하는 함수 포인터
	std::vector<FAnimation2DNotify*> mNotifyList;

	////////////////
public:
	// Getter
	CAnimation2DData* GetAnimationAsset() const
	{
		return mAsset;
	}

	int GetFrame() const
	{
		return mFrame;
	}

	float GetTime() const
	{
		return mTime;
	}

	float GetFrameTime() const
	{
		return mFrameTime;
	}

	float GetPlayTime() const
	{
		return mPlayTime;
	}

	const std::string& GetName() const;

	/////////// Set
public:
	void SetAsset(class CAnimation2DData* Asset);
	void SetPlayTime(float PlayTime);

	void SetPlayRate(float Rate)
	{
		mPlayRate = Rate;
	}

	void SetLoop(bool Loop)
	{
		mLoop = Loop;
	}

	void SetReverse(bool Reverse)
	{
		mReverse = Reverse;
	}

public:
	void Update(float DelaTime);
	CAnimation2DSequence* Clone();

private:
	void CallNotify();

public:
	// 함수포인터 바인드하기
	// 템플릿
	template<typename T>
	void SetEndFunction(T* Obj, void(T::* Func)())
	{
		mEndFunction = std::bind(Func, Obj);
	}

	// Notify 바인드
	template<typename T>
	void AddNotify(const std::string& Name, int Frame, T* Obj, void(T::* Func)())
	{
		FAnimation2DNotify* Notify = new FAnimation2DNotify;

		Notify->Name = Name;
		Notify->Frame = Frame;
		Notify->Function = std::bind(Func, Obj);

		mNotifyList.emplace_back(Notify);
	}
};

