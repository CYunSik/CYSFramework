#pragma once
#include "../../Scene/Scene.h"

class CSceneGameOver : public CScene
{
	friend class CSceneManager;

protected:
	CSceneGameOver();
	virtual ~CSceneGameOver();

	float mLogoShowTime = 0.f;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

