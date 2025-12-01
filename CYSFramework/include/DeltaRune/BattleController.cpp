#include "BattleController.h"
#include "PlayerSoulObject.h"
#include "JevilBossObject.h"
#include "ChrisBattleObject.h"
#include "SusieBattleObject.h"
#include "RalseiBattleObject.h"
#include "../Share/Log.h"

CBattleController::CBattleController()
{
}

CBattleController::CBattleController(const CBattleController& Obj)
    : CObject(Obj)
{
}

CBattleController::~CBattleController()
{
}

bool CBattleController::Init()
{
    CObject::Init();

    return true;
}

void CBattleController::StartCutscene()
{
    mState = EBattleState::Cutscene;
    mCutsceneTime = 0.f;
    mCutsceneFinished = false;

    CLog::PrintLog("Cutscene Start");

    // 캐릭터 3명 초기 위치 세팅
    if (mChris)  mChris->SetWorldPos(600.f, 750.f, 0.f);
    if (mSusie)  mSusie->SetWorldPos(640.f, 770.f, 0.f);
    if (mRalsei) mRalsei->SetWorldPos(680.f, 750.f, 0.f);
}

void CBattleController::StartBattle()
{
    mBattleStarted = true;
    mState = EBattleState::PlayerTurn;

    CLog::PrintLog("Player Turn Start");
}

void CBattleController::Update(float DeltaTime)
{
    CObject::Update(DeltaTime);

    switch (mState)
    {
    case EBattleState::Cutscene:
        UpdateCutscene(DeltaTime);
        break;

    case EBattleState::PlayerTurn:
        UpdatePlayerTurn(DeltaTime);
        break;

    case EBattleState::EnemyTurn:
        UpdateEnemyTurn(DeltaTime);
        break;

    case EBattleState::SoulBattle:
        UpdateSoulBattle(DeltaTime);
        break;

    default:
        break;
    }
}

void CBattleController::UpdateCutscene(float DeltaTime)
{
    mCutsceneTime += DeltaTime;

    // 1초 동안 캐릭터들이 앞쪽으로 살짝 걷는 연출
    float moveSpeed = 40.f;

    if (mCutsceneTime < 1.f)
    {
        if (mChris)
        {
            FVector3D pos = mChris->GetWorldPosition();
            pos.y -= moveSpeed * DeltaTime;
            mChris->SetWorldPos(pos);
        }

        if (mSusie)
        {
            FVector3D pos = mSusie->GetWorldPosition();
            pos.y -= moveSpeed * DeltaTime;
            mSusie->SetWorldPos(pos);
        }

        if (mRalsei)
        {
            FVector3D pos = mRalsei->GetWorldPosition();
            pos.y -= moveSpeed * DeltaTime;
            mRalsei->SetWorldPos(pos);
        }
    }
    else
    {
        // 컷씬 종료
        mCutsceneFinished = true;
    }
}

void CBattleController::UpdatePlayerTurn(float DeltaTime)
{
    // UI에서 선택 기다리는 상태
    // 이후 플레이어 선택 완료되면
    //   mState = EBattleState::EnemyTurn;
    // 로 넘어감.
}

void CBattleController::UpdateEnemyTurn(float DeltaTime)
{
    // 제빌의 공격 패턴 실행
    // 패턴이 끝나면 SoulBattle 시작

    // 예시:
    // if (보스 패턴 끝)
    //      mState = EBattleState::SoulBattle;
}

void CBattleController::UpdateSoulBattle(float DeltaTime)
{
    // Soul(하트) 이동 가능 상태
    // 제빌의 패턴이 하트 공격

    // 예시:
    // if (하트 생존하고 패턴 끝나면)
    //    mState = EBattleState::EndTurn;

    // if (EndTurn)
    //    mState = EBattleState::PlayerTurn;
}
