#pragma once

#include "../../Scene/Scene.h"

class CSceneTest : public CScene
{
	friend class CSceneManager;

protected:
	CSceneTest();
	virtual ~CSceneTest();

public:
	virtual bool Init();
};
