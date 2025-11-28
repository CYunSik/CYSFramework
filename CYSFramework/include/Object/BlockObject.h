#pragma once
#include "SceneObject.h"

class CBlockObject : public CSceneObject
{
    friend class CScene;

protected:
    CBlockObject();
    CBlockObject(const CBlockObject& Obj);
    CBlockObject(CBlockObject&& Obj);
    virtual ~CBlockObject();

protected:
    CSharedPtr<class CSpriteComponent> mRoot;
    CSharedPtr<class CSpriteComponent> mRoot2;
    CSharedPtr<class CSpriteComponent> mRoot3;
    CSharedPtr<class CSpriteComponent> mRoot4;
    CSharedPtr<class CSpriteComponent> mRoot5;
    CSharedPtr<class CColliderAABB2D> mBody;
    CSharedPtr<class CColliderAABB2D> mBody2;
    CSharedPtr<class CColliderAABB2D> mBody3;
    CSharedPtr<class CColliderAABB2D> mBody4;

    // 애니메이션
    class CAnimation2D* mAnimation = nullptr;
	class CAnimation2D* mAnimationBattleFrame = nullptr;
	class CAnimation2D* mAnimationBattleBox = nullptr;
	class CAnimation2D* mAnimationBattleBox2 = nullptr;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void CollisionBlock(const FVector3D& HitPoint, class CColliderBase* Dest);
    void CollisionBlockEnd(class CColliderBase* Dest);
};