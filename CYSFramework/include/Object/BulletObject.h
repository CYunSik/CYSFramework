#pragma once
#include "SceneObject.h"

class CBulletObject : public CSceneObject
{
	friend class CScene;

private:
	float mSpeed = 2.f;

protected:
	CSharedPtr<class CStaticMeshComponent> mRoot;

protected:
	CBulletObject();
	CBulletObject(const CBulletObject& Obj);
	CBulletObject(CBulletObject&& Obj);
	virtual ~CBulletObject();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

