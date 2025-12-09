#pragma once
#include "Scene.h"

class CSceneEditor : public CScene
{
	friend class CSceneManager;

protected:
	CSceneEditor();
	virtual ~CSceneEditor();

protected:
	CSharedPtr<class CTileMapObj> mTileMapObj;


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

