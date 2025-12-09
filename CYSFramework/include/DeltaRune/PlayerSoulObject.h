#pragma once
#include "../Object/SceneObject.h"

class CPlayerSoulObject : public CSceneObject
{
    friend class CScene;

protected:
    CPlayerSoulObject();
    CPlayerSoulObject(const CPlayerSoulObject& Obj);
    CPlayerSoulObject(CPlayerSoulObject&& Obj);
    virtual ~CPlayerSoulObject();

protected:
    // 하트
    CSharedPtr<class CSpriteComponent> mRoot;

    // 콜라이더
    CSharedPtr<class CColliderAABB2D> mBody;

    // 이동
    CSharedPtr<class CMovementComponent> mMovement;

    // 카메라
    CSharedPtr<class CCameraComponent> mCamera;

    class CAnimation2D* mAnimation = nullptr;

    // 이동 구역(배틀 박스 영역)
    float mMinX = -130.f;
    float mMaxX = 133.f;
    float mMinY = 5.f;
    float mMaxY = 202.f;

    // 패턴에 피격당하고 1초동안 무적을 위한 변수
    bool mInvincible = false;
    float mInvincibleTime = 0.f;

    std::string mHeart;
    std::string mInvincibleHeart;

    // [게임오버 테스트용]
    class CProgressBar* mHPBar;
    int mHP = 100;
    bool mGameOver = false;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

    void IsGameOver();

private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);
    void MoveLeft(float DeltaTime);
    void MoveRight(float DeltaTime);

    void OnCollisionBegin(const FVector3D& HitPoint, class CColliderBase* Dest);
};

