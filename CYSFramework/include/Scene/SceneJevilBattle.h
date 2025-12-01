#pragma once

#include "Scene.h"

class CSceneJevilBattle : public CScene
{
    friend class CSceneManager;

protected:
    CSceneJevilBattle();
    virtual ~CSceneJevilBattle();

private:
    bool mBattleStarted = false;

protected:
    class CBattleController* mBattleController = nullptr;
    class CPlayerSoulObject* mSoul = nullptr;
    class CJevilBossObject* mBoss = nullptr;

public:
    virtual bool Init() override;
    virtual void Update(float DeltaTime) override;
};
