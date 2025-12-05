#pragma once
#include "../../Object/SceneObject.h"

class CClubBoom : public CSceneObject
{
    friend class CScene;

protected:
    CClubBoom();
    CClubBoom(const CClubBoom& Obj);
    CClubBoom(CClubBoom&& Obj);
    virtual ~CClubBoom();

protected:
    CSharedPtr<class CSpriteComponent> mRoot;

    // 콜라이더
    //CSharedPtr<class CColliderSphere2D> mBody;

    class CAnimation2D* mAnimation = nullptr;

    // 낙하 시간
    float mDownTime = 0.f;

public:
    void SetDownTime(float Time)
    {
        mDownTime = Time;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

