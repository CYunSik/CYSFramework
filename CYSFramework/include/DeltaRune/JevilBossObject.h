#pragma once
#include "../Object/SceneObject.h"

class CJevilBossObject : public CSceneObject
{
    friend class CScene;

protected:
    CJevilBossObject();
    CJevilBossObject(const CJevilBossObject& Obj);
    CJevilBossObject(CJevilBossObject&& Obj);
    virtual ~CJevilBossObject();

protected:
    // 제빌
    CSharedPtr<class CSpriteComponent> mRoot;
    CSharedPtr<class CSpriteComponent> mRoot2;
    CSharedPtr<class CSpriteComponent> mRoot3;

    // 이동
    //CSharedPtr<class CMovementComponent> mMovement;

    // 애니메이션
    class CAnimation2D* mAnimation = nullptr;
    class CAnimation2D* mAnimation2 = nullptr;
    class CAnimation2D* mAnimation3 = nullptr;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

