#pragma once

#include "../../Scene/Scene.h"

class CSceneTest : public CScene
{
	friend class CSceneManager;

protected:
	CSceneTest();
	virtual ~CSceneTest();

	class CBattleSystem* mBattleSystem = nullptr;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};
