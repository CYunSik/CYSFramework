#pragma once

class CBattleSystem
{
public:
    CBattleSystem(class CScene* Scene);
    ~CBattleSystem();

public:
    // 전투 상태머신
    enum class EBattleState
    {
        None,
        PlayerSelect,     // UI: 행동 선택
        PlayerAction,     // 플레이어 행동 수행
        EnemyDialogue,    // 적 대사
        EnemyAttack       // 하트로 피하기 패턴
    };

protected:
    class CScene* mScene = nullptr;

    EBattleState mState = EBattleState::None;

    // 턴 카운트 (제빌이 턴에 따라 대사/패턴이 달라짐)
    int mTurnCount = 0;

    // Fight/Act/Item/Spare 선택값
    int mSelectedCommand = -1;

public:
    void Init();
    void Update(float DeltaTime);

    void ChangeState(EBattleState NewState);

    // UI가 명령 버튼을 눌렀을 때 호출
    void OnCommandSelected(int CommandID);

    EBattleState GetState() const
    {
	    return mState;
    }

public:
    // 상태별 처리
    void PlayerSelect(float DeltaTime);
    void PlayerAction(float DeltaTime);
    void EnemyDialogue(float DeltaTime);
    void EnemyAttack(float DeltaTime);
};
