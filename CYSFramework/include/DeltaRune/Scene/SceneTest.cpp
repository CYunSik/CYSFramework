#include "SceneTest.h"

#include "../JevilBossObject.h"
#include "../PlayerSoulObject.h"
#include "../../Object/BackObject.h"
#include "../../Scene/CameraManager.h"
#include "../../Component/SpriteComponent.h"
#include "../../Scene/SceneUIManager.h"
#include "../../Object/SceneObject.h"
#include "../../Component/CameraComponent.h"
#include "../../Object/GunnerMonster.h"
#include "../../Object/SceneObject.h"

#include "../../Share/Log.h"
#include "../Bullet/ClubBoom.h"

CSceneTest::CSceneTest()
{
}

CSceneTest::~CSceneTest()
{
}

bool CSceneTest::Init()
{
    if (!CScene::Init())
    {
        return false;
    }

    CPlayerSoulObject* Heart = CreateObj<CPlayerSoulObject>("Heart");

    if (Heart == nullptr)
    {
        return false;
    }

    // 크리스
    CSceneObject* Kris = CreateObj<CSceneObject>("Susie");
    CSpriteComponent* KrisSprite = Kris->CreateComponent<CSpriteComponent>();

    Kris->SetRootComponent(KrisSprite);
    Kris->SetWorldPos(-350.f, 70.f, 7.f);
    Kris->SetWorldScale(200.f, 150.f, 1.f);

    CAnimation2D* KrisAnim = KrisSprite->CreateAnimation2D<CAnimation2D>();
    KrisAnim->AddSequence("KrisIdle", 0.7f, 1.f, true, false);

    // 수지
    CSceneObject* Susie = CreateObj<CSceneObject>("Susie");
    CSpriteComponent* SusieSprite = Susie->CreateComponent<CSpriteComponent>();

    Susie->SetRootComponent(SusieSprite);
    Susie->SetWorldPos(-410.f, -30.f, 5.f);
    Susie->SetWorldScale(300.f, 200.f, 1.f);

    CAnimation2D* SusieAnim = SusieSprite->CreateAnimation2D<CAnimation2D>();
    SusieAnim->AddSequence("SusieIdle", 1.5f, 1.f, true, false);

    //////////////////////////////////////////////////////////////////////////////////
    // 랄세이
    CSceneObject* Ralsei = CreateObj<CSceneObject>("Ralsei");
    CSpriteComponent* RalseiSprite = Ralsei->CreateComponent<CSpriteComponent>();

    Ralsei->SetRootComponent(RalseiSprite);
    Ralsei->SetWorldPos(-390.f, -150.f, 2.f);
    Ralsei->SetWorldScale(250.f, 200.f, 1.f);

    CAnimation2D* RalseiAnim = RalseiSprite->CreateAnimation2D<CAnimation2D>();
    RalseiAnim->AddSequence("RalseiIdle", 1.f, 1.f, true, false);

    // 제빌
    CJevilBossObject* Jevil = CreateObj<CJevilBossObject>("Jevil");
    Jevil->SetWorldPos(300.f, 30.f, 1.f);

    // 전투박스
    CSceneObject* BattleBox = CreateObj<CSceneObject>("BattleBox");
    CSpriteComponent* BattleBoxSprite = BattleBox->CreateComponent<CSpriteComponent>("BattleBox");

    BattleBox->SetRootComponent(BattleBoxSprite);
    BattleBox->SetWorldPos(0.f, -100.f, 1.f);
    
    BattleBox->SetWorldScale(960.f, 720.f);

    BattleBoxSprite->SetTexture("BattleBox", TEXT("Texture/spr_battlebg_stretch_hitbox_0.png"));
    BattleBoxSprite->SetPivot(0.5f, 0.5f);
    BattleBoxSprite->SetOpacity(1.f);
    
	CAnimation2D* BattleBoxAnim = BattleBoxSprite->CreateAnimation2D<CAnimation2D>();
    BattleBoxAnim->AddSequence("BattleBoxStart", 0.7f, 1.f, false, false);

    // 제빌 배경
    CBackObject* JevilBG = CreateObj<CBackObject>("JevilBG");
    JevilBG->SetWorldPos(0.f, 0.f, 1.f);
    JevilBG->SetWorldScale(960.f, 720.f);

	// 테스트 몬스터
    CGunnerMonster* Monster = CreateObj<CGunnerMonster>("GunnerMonster");
    Monster->SetWorldPos(160.f, 190.f);
    Monster->SetTarget(Heart);
    Monster->SetFireInterval(0.3f);

    CGunnerMonster* Monster2 = CreateObj<CGunnerMonster>("GunnerMonster2");
    Monster2->SetWorldPos(160.f, -190.f);
    Monster2->SetTarget(Heart);
    Monster2->SetFireInterval(0.6f);

    CGunnerMonster* Monster3 = CreateObj<CGunnerMonster>("GunnerMonster");
    Monster3->SetWorldPos(-160.f, 190.f);
    Monster3->SetTarget(Heart);
    Monster3->SetFireInterval(0.9f);

    CGunnerMonster* Monster4 = CreateObj<CGunnerMonster>("GunnerMonster2");
    Monster4->SetWorldPos(-160.f, -190.f);
    Monster4->SetTarget(Heart);
    Monster4->SetFireInterval(1.2f);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // 테스트 패턴
    // 클로버 폭탄
    //CClubBoom* ClubBoom = CreateObj<CClubBoom>("ClubBoom");
    //ClubBoom->SetWorldPos(-200.f, 300.f);
    //ClubBoom->SetDownTime(1.2f);

    //CClubBoom* ClubBoom2 = CreateObj<CClubBoom>("ClubBoom2");
    //ClubBoom2->SetWorldPos(-350.f, 500.f);
    //ClubBoom2->SetDownTime(1.5f);

    //CClubBoom* ClubBoom3 = CreateObj<CClubBoom>("ClubBoom3");
    //ClubBoom3->SetWorldPos(200.f, 400.f);
    //ClubBoom3->SetDownTime(1.3f);

    //CClubBoom* ClubBoom4 = CreateObj<CClubBoom>("ClubBoom4");
    //ClubBoom4->SetWorldPos(350.f, 500.f);
    //ClubBoom4->SetDownTime(2.f);

    //CClubBoom* ClubBoom5 = CreateObj<CClubBoom>("ClubBoom5");
    //ClubBoom5->SetWorldPos(400.f, 700.f);
    //ClubBoom5->SetDownTime(2.3f);

    //CClubBoom* ClubBoom6 = CreateObj<CClubBoom>("ClubBoom6");
    //ClubBoom6->SetWorldPos(350.f, 1000.f);
    //ClubBoom6->SetDownTime(2.5f);

    //CClubBoom* ClubBoom7 = CreateObj<CClubBoom>("ClubBoom7");
    //ClubBoom7->SetWorldPos(400.f, 600.f);
    //ClubBoom7->SetDownTime(1.7f);

    //CClubBoom* ClubBoom8 = CreateObj<CClubBoom>("ClubBoom8");
    //ClubBoom8->SetWorldPos(-200.f, 600.f);
    //ClubBoom8->SetDownTime(1.3f);

    //CClubBoom* ClubBoom9 = CreateObj<CClubBoom>("ClubBoom9");
    //ClubBoom9->SetWorldPos(-400.f, 800.f);
    //ClubBoom9->SetDownTime(2.2f);

    //CClubBoom* ClubBoom10 = CreateObj<CClubBoom>("ClubBoom10");
    //ClubBoom10->SetWorldPos(-400.f, 800.f);
    //ClubBoom10->SetDownTime(2.2f);

    //CClubBoom* ClubBoom11 = CreateObj<CClubBoom>("ClubBoom11");
    //ClubBoom11->SetWorldPos(-400.f, 1200.f);
    //ClubBoom11->SetDownTime(2.8f);

    //CClubBoom* ClubBoom12 = CreateObj<CClubBoom>("ClubBoom12");
    //ClubBoom12->SetWorldPos(400.f, 1100.f);
    //ClubBoom12->SetDownTime(2.9f);

    //CClubBoom* ClubBoom13 = CreateObj<CClubBoom>("ClubBoom13");
    //ClubBoom13->SetWorldPos(350.f, 1400.f);
    //ClubBoom13->SetDownTime(3.5f);

    //CClubBoom* ClubBoom14 = CreateObj<CClubBoom>("ClubBoom14");
    //ClubBoom14->SetWorldPos(-250.f, 1400.f);
    //ClubBoom14->SetDownTime(3.5f);

    //CClubBoom* ClubBoom15 = CreateObj<CClubBoom>("ClubBoom15");
    //ClubBoom15->SetWorldPos(-250.f, 1400.f);
    //ClubBoom15->SetDownTime(3.8f);

    //CClubBoom* ClubBoom16 = CreateObj<CClubBoom>("ClubBoom15");
    //ClubBoom16->SetWorldPos(-300.f, 1700.f);
    //ClubBoom16->SetDownTime(4.5f);

    //CClubBoom* ClubBoom17 = CreateObj<CClubBoom>("ClubBoom15");
    //ClubBoom17->SetWorldPos(300.f, 1600.f);
    //ClubBoom17->SetDownTime(4.7f);

    return true;
}
