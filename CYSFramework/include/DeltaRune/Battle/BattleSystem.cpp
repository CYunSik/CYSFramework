#include "BattleSystem.h"
#include "../../Scene/Scene.h"
#include "../../Share/Log.h"

CBattleSystem::CBattleSystem(CScene* Scene)
{
    mScene = Scene;
}

CBattleSystem::~CBattleSystem()
{

}

void CBattleSystem::Init()
{
    ChangeState(EBattleState::PlayerSelect);

    CLog::PrintLog("BattleSystem Init: PlayerSelect 시작");
}

void CBattleSystem::Update(float DeltaTime)
{
    switch (mState)
    {
    case EBattleState::PlayerSelect:
        PlayerSelect(DeltaTime);
        break;

    case EBattleState::PlayerAction:
        PlayerAction(DeltaTime);
        break;

    case EBattleState::EnemyDialogue:
		EnemyDialogue(DeltaTime);
        break;

    case EBattleState::EnemyAttack:
        EnemyAttack(DeltaTime);
        break;
    }
}

void CBattleSystem::ChangeState(EBattleState NewState)
{
    mState = NewState;

    switch (mState)
    {
    case EBattleState::PlayerSelect:
        CLog::PrintLog("상태 변경: PlayerSelect (플레이어 명령 선택)");
        break;
    case EBattleState::PlayerAction:
        CLog::PrintLog("상태 변경: PlayerAction (플레이어 행동 수행)");
        break;
    case EBattleState::EnemyDialogue:
        CLog::PrintLog("상태 변경: EnemyDialogue (적 대사)");
        break;
    case EBattleState::EnemyAttack:
        CLog::PrintLog("상태 변경: EnemyAttack (적 공격 패턴)");
        break;
    }
}

void CBattleSystem::OnCommandSelected(int CommandID)
{
    mSelectedCommand = CommandID;

    // 명령 선택이 끝났으면 플레이어 행동 Phase로 이동
    ChangeState(EBattleState::PlayerAction);
}

void CBattleSystem::PlayerSelect(float DeltaTime)
{
    // UI가 명령을 선택하면 OnCommandSelected()가 호출됨
}

void CBattleSystem::PlayerAction(float DeltaTime)
{
    // 공격 애니메이션, Act, Item 사용 같은 실제 액션 구현

    // 지금은 구조만 잡아놓은 상태 → 바로 EnemyDialogue로 넘어감
    CLog::PrintLog("PlayerAction 완료 → EnemyDialogue로 이동");

    ChangeState(EBattleState::EnemyDialogue);
}

void CBattleSystem::EnemyDialogue(float DeltaTime)
{
    // 대사 박스 보여주기
    // 일정 시간 후 EnemyAttack으로 넘어감

    CLog::PrintLog("EnemyDialogue 완료 → EnemyAttack로 이동");

    ChangeState(EBattleState::EnemyAttack);
}

void CBattleSystem::EnemyAttack(float DeltaTime)
{
    // 하트 스폰 + 제빌 패턴 진행
    // 일정 시간 후 다시 PlayerSelect로 복귀

    CLog::PrintLog("EnemyAttack 완료 → PlayerSelect로 이동");

    mTurnCount++;

    ChangeState(EBattleState::PlayerSelect);
}
