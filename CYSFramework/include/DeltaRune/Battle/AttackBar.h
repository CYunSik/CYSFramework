#pragma once

// 단일 공격 바를 관리하는 클래스.
// 오른쪽에서 왼쪽으로 이동하며, Z키로 멈추면 데미지 판정.
// 화면 밖으로 나가면 MISS 처리.
class CAttackBar
{
protected:
    CAttackBar();
    ~CAttackBar();

protected:
    // 바의 현재 위치 (UI 렌더링 시 사용)
    float mBarX;
    float mBarY;

    // 이동 속도 및 한계
    float mSpeed;
    float mLeftLimitX;

    // 시작 위치 랜덤 범위
    float mStartMinX;
    float mStartMaxX;

    // SweetSpot 정보
    float mSweetSpotX;
    float mSweetSpotRadius;

    // 상태 플래그
    bool mActive;
    bool mStopped;
    bool mFinished;
    bool mMiss;

    // 0.0 ~ 1.0 사이 데미지 비율
    float mDamageRate;

public:
    // 기본 이동 정보 설정
    void Setup(float leftLimitX, float speed);

    // 바 실제 시작 (랜덤 시작 위치 + 스윗 스팟 설정)
    void Start(float startMinX, float startMaxX, float sweetSpotX, float sweetSpotRadius, float barY);

    // 매 프레임 이동
    void Update(float deltaTime);

    // 플레이어가 Z 누르면 호출, 바 멈추고 DamageRate 계산
    void Stop();

public:
    // Getters
    bool  IsActive() const
    {
	    return mActive;
    }

    bool  IsStopped() const
    {
	    return mStopped;
    }

    bool  IsFinished() const
    {
	    return mFinished;
    }

    bool  IsMiss() const
    {
	    return mMiss;
    }

    float GetBarX() const
    {
	    return mBarX;
    }

    float GetBarY() const
    {
	    return mBarY;
    }

    float GetSweetSpotX() const
    {
	    return mSweetSpotX;
    }

    float GetSweetSpotRadius() const
    {
	    return mSweetSpotRadius;
    }

    float GetDamageRate() const
    {
	    return mDamageRate;
    }
};
