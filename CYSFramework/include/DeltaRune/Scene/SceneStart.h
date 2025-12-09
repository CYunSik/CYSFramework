#pragma once
#include "../../Scene/Scene.h"

class CSceneStart : public CScene
{
	friend class CSceneManager;

protected:
	CSceneStart();
	virtual ~CSceneStart();

public:
	virtual bool Init();
};