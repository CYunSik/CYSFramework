#pragma once
#include "../Object/SceneObject.h"

class CJevilPrisonBG : public CSceneObject
{
    friend class CScene;

protected:
    CJevilPrisonBG();
    CJevilPrisonBG(const CJevilPrisonBG& Obj);
    CJevilPrisonBG(CJevilPrisonBG&& Obj);
    virtual ~CJevilPrisonBG();

protected:
    CSharedPtr<class CSpriteComponent> mBackGround;
    CSharedPtr<class CColliderAABB2D> mBody;
    CSharedPtr<class CColliderAABB2D> mBody2;

    // 애니메이션
    class CAnimation2D* mAnimation = nullptr;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

