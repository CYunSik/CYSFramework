#include "SceneJevilBattle.h"
#include "PlayerSoulObject.h"
#include "JevilBossObject.h"
#include "BattleController.h"
#include "../Share/Log.h"

CSceneJevilBattle::CSceneJevilBattle()
{
}

CSceneJevilBattle::~CSceneJevilBattle()
{
}

bool CSceneJevilBattle::Init()
{
    if (!CScene::Init())
    {
        return false;
    }

    CLog::PrintLog("SceneJevilBattle Init");

    mBattleController = CreateObj<CBattleController>("BattleController");

    // Player Soul
    mSoul = CreateObj<CPlayerSoulObject>("PlayerSoul");
    if (mSoul)
    {
    	mSoul->SetActive(false); // SoulBattle에서 등장
    }

    // Boss
    mBoss = CreateObj<CJevilBossObject>("JevilBoss");

    // 연결
    if (mBattleController)
    {
        mBattleController->SetSoul(mSoul);
        mBattleController->SetBoss(mBoss);
    }

    return true;
}

void CSceneJevilBattle::Update(float DeltaTime)
{
    CScene::Update(DeltaTime);

    if (!mBattleStarted)
    {
        mBattleStarted = true;

        CLog::PrintLog("Battle Start!");

        if (mBattleController)
            mBattleController->StartBattle();
    }
}
