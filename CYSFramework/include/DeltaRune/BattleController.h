#pragma once

#include "../Object/SceneObject.h"

enum class EBattleState
{
    None,
    Cutscene,
    PlayerTurn,    // 행동 선택 UI
    EnemyTurn,     // 제빌 패턴
    SoulBattle,    // 하트로 패턴 피하기
    EndTurn
};

class CBattleController : public CSceneObject
{
    friend class CScene;

protected:
    CBattleController();
    CBattleController(const CBattleController& Obj);
    virtual ~CBattleController();

private:
    EBattleState mState = EBattleState::None;

    // 컷씬 타임라인
    float mCutsceneTime = 0.f;
    bool mCutsceneFinished = false;

    // 진행 여부
    bool mBattleStarted = false;

    // 하트
    class CPlayerSoulObject* mSoul = nullptr;

    // 보스 제빌
    class CJevilBossObject* mBoss = nullptr;

    // 캐릭터 : 크리스, 수지, 랄세이
    class CChrisBattleObject* mChris = nullptr;
    class CSusieBattleObject* mSusie = nullptr;
    class CRalseiBattleObject* mRalsei = nullptr;

    // 상태 처리 함수
    void UpdateCutscene(float DeltaTime);
    void UpdatePlayerTurn(float DeltaTime);
    void UpdateEnemyTurn(float DeltaTime);
    void UpdateSoulBattle(float DeltaTime);

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);

	// Set
    void SetSoul(CPlayerSoulObject* Soul)
    {
	    mSoul = Soul;
    }

    void SetBoss(CJevilBossObject* Boss)
    {
	    mBoss = Boss;
    }

    void SetChris(CChrisBattleObject* Obj)
    {
	    mChris = Obj;
    }

    void SetSusie(CSusieBattleObject* Obj)
    {
	    mSusie = Obj;
    }

    void SetRalsei(CRalseiBattleObject* Obj)
    {
	    mRalsei = Obj;
    }

    // 제어 함수
    void StartCutscene();
    void StartBattle();

    bool IsCutsceneFinished() const
    {
	    return mCutsceneFinished;
    }

    bool IsBattleStarted() const
    {
	    return mBattleStarted;
    }
};
