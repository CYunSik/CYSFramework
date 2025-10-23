#pragma once

#include "Scene.h"

class CSceneMain : public CScene
{
protected:
    CSceneMain();
    virtual ~CSceneMain();

public:
    virtual bool Init();
};

