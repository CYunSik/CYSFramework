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
    CSharedPtr<class CColliderSphere2D> mBody;

    // 이동
    CSharedPtr<class CMovementComponent> mMovement;

    // 이동 구역(배틀 박스 영역)
    float mMinX = 300.f;
    float mMaxX = 980.f;
    float mMinY = 350.f;
    float mMaxY = 650.f;

    // 패턴에 피격당하고 1초동안 무적을 위한 변수
    bool mInvincible = false;
    float mInvincibleTime = 0.f;

    std::string mHeart;
    std::string mInvincibleHeart;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);
    void MoveLeft(float DeltaTime);
    void MoveRight(float DeltaTime);

    void OnCollisionBegin(const FVector3D& HitPoint, class CColliderBase* Dest);
};

