#pragma once
#include "SceneObject.h"

class CMonsterSpawner : public CSceneObject
{
	friend class CScene;

protected:
	CMonsterSpawner();
	CMonsterSpawner(const CMonsterSpawner& Obj);
	CMonsterSpawner(CMonsterSpawner&& Obj);
	virtual ~CMonsterSpawner();

protected:
	CSharedPtr<class CStaticMeshComponent> mRoot;
	CSharedPtr<CSceneObject> mTarget;

	float mTime = 5.f;
	float mTimeAcc = 0.f;
	int mSpawnCount = 0;

public:
	void SetTarget(CSceneObject* Target)
	{
		mTarget = Target;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

