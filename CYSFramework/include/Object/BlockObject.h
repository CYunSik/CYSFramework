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
    CSharedPtr<class CColliderAABB2D> mBody;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

private:
    void CollisionBlock(const FVector3D& HitPoint, class CColliderBase* Dest);
    void CollisionBlockEnd(class CColliderBase* Dest);
};