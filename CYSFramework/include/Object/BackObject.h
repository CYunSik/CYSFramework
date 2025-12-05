#pragma once
#include "SceneObject.h"

class CBackObject :public CSceneObject
{
	friend class CScene;

protected:
	CBackObject();
	CBackObject(const CBackObject& Obj);
	CBackObject(CBackObject&& Obj);
	virtual ~CBackObject();

protected:
	CSharedPtr<class CSpriteComponent> mRoot;

	class CAnimation2D* mAnimation = nullptr;

public:
	virtual bool Init();
};

