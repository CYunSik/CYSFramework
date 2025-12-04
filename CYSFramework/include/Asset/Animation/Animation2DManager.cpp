#include "Animation2DManager.h"
#include "Animation2DData.h"
#include "../../Animation/Animation2D.h"

CAnimation2DManager::CAnimation2DManager()
{
}

CAnimation2DManager::~CAnimation2DManager()
{
	CAnimation2D::DestroyCBuffer();
}

bool CAnimation2DManager::Init()
{
	// 애니메이션용 상수 버퍼 생성
	CAnimation2D::CreateCBuffer();

	// 애니메이션 하나 등록하기
	// Texture/Player/Player.png
	// 스프라이트 형식으로 만들기
	CreateAnimation("PlayerIdle");
	SetAnimationTextureType("PlayerIdle", EAnimationTextureType::SpriteSheet);
	SetTexture("PlayerIdle", "PlayerSprite", TEXT("Texture/Player/Player.png"));

	for (int i = 0; i < 5; ++i)
	{
		AddFrame("PlayerIdle", i * 200.f, 0.f, 200.f, 200.f);
	}

	// 스타트화면 애니메이션
	CreateAnimation("StartBGAnimation");
	SetAnimationTextureType("StartBGAnimation", EAnimationTextureType::Frame);

	std::vector<const TCHAR*> FileNames;
	FileNames.emplace_back(TEXT("Texture/UI/IMAGE_MENU_ANIMATION/IMAGE_MENU_ANIMATION_0.png"));
	FileNames.emplace_back(TEXT("Texture/UI/IMAGE_MENU_ANIMATION/IMAGE_MENU_ANIMATION_1.png"));
	FileNames.emplace_back(TEXT("Texture/UI/IMAGE_MENU_ANIMATION/IMAGE_MENU_ANIMATION_2.png"));
	FileNames.emplace_back(TEXT("Texture/UI/IMAGE_MENU_ANIMATION/IMAGE_MENU_ANIMATION_3.png"));
	FileNames.emplace_back(TEXT("Texture/UI/IMAGE_MENU_ANIMATION/IMAGE_MENU_ANIMATION_4.png"));

	SetTexture("StartBGAnimation", "StartBGAnimation", FileNames);
	AddFrameCount("StartBGAnimation", 5, 0.f, 0.f, 320.f, 70.f);

	// 크리스 오른쪽 걷기
	CreateAnimation("KrisWalkRight");
	SetAnimationTextureType("KrisWalkRight", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisr_dark/spr_krisr_dark_0.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisr_dark/spr_krisr_dark_1.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisr_dark/spr_krisr_dark_2.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisr_dark/spr_krisr_dark_3.png"));

	SetTexture("KrisWalkRight", "KrisWalkRight", FileNames);
	AddFrameCount("KrisWalkRight", 4, 0.f, 0.f, 19.f, 38.f);

	// 크리스 왼쪽 걷기
	CreateAnimation("KrisWalkLeft");
	SetAnimationTextureType("KrisWalkLeft", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisl_dark/spr_krisl_dark_0.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisl_dark/spr_krisl_dark_1.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisl_dark/spr_krisl_dark_2.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisl_dark/spr_krisl_dark_3.png"));

	SetTexture("KrisWalkLeft", "KrisWalkLeft", FileNames);
	AddFrameCount("KrisWalkLeft", 4, 0.f, 0.f, 19.f, 38.f);

	// 크리스 위로 걷기
	CreateAnimation("KrisWalkUp");
	SetAnimationTextureType("KrisWalkUp", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisu_dark/spr_krisu_dark_0.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisu_dark/spr_krisu_dark_1.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisu_dark/spr_krisu_dark_2.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisu_dark/spr_krisu_dark_3.png"));

	SetTexture("KrisWalkUp", "KrisWalkUp", FileNames);
	AddFrameCount("KrisWalkUp", 4, 0.f, 0.f, 19.f, 38.f);

	// 크리스 아래로 걷기
	CreateAnimation("KrisWalkDown");
	SetAnimationTextureType("KrisWalkDown", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisd_dark/spr_krisd_dark_0.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisd_dark/spr_krisd_dark_1.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisd_dark/spr_krisd_dark_2.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisd_dark/spr_krisd_dark_3.png"));

	SetTexture("KrisWalkDown", "KrisWalkDown", FileNames);
	AddFrameCount("KrisWalkDown", 4, 0.f, 0.f, 19.f, 38.f);

	// 크리스 Idle
	CreateAnimation("KrisIdle");
	SetAnimationTextureType("KrisIdle", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_idle/spr_krisb_idle_0.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_idle/spr_krisb_idle_1.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_idle/spr_krisb_idle_2.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_idle/spr_krisb_idle_3.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_idle/spr_krisb_idle_4.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_idle/spr_krisb_idle_5.png"));

	SetTexture("KrisIdle", "KrisIdle", FileNames);
	AddFrameCount("KrisIdle", 6, 0.f, 0.f, 36.f, 38.f);

	// 크리스 공격
	CreateAnimation("KrisAttack");
	SetAnimationTextureType("KrisAttack", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_attack/spr_krisb_attack_old_ch1_0.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_attack/spr_krisb_attack_old_ch1_1.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_attack/spr_krisb_attack_old_ch1_2.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_attack/spr_krisb_attack_old_ch1_3.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_attack/spr_krisb_attack_old_ch1_4.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_attack/spr_krisb_attack_old_ch1_5.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_attack/spr_krisb_attack_old_ch1_6.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_attack/spr_krisb_attack_old_ch1_7.png"));

	SetTexture("KrisAttack", "KrisAttack", FileNames);
	AddFrameCount("KrisAttack", 8, 0.f, 0.f, 63.f, 50.f);

	// 크리스 인트로
	CreateAnimation("KrisIntro");
	SetAnimationTextureType("KrisIntro", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_intro/spr_krisb_intro_ch1_0.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_intro/spr_krisb_intro_ch1_1.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_intro/spr_krisb_intro_ch1_2.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_intro/spr_krisb_intro_ch1_3.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_intro/spr_krisb_intro_ch1_4.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_intro/spr_krisb_intro_ch1_5.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_intro/spr_krisb_intro_ch1_6.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_intro/spr_krisb_intro_ch1_7.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_intro/spr_krisb_intro_ch1_8.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_intro/spr_krisb_intro_ch1_9.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_intro/spr_krisb_intro_ch1_10.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_intro/spr_krisb_intro_ch1_11.png"));

	SetTexture("KrisIntro", "KrisIntro", FileNames);
	AddFrameCount("KrisIntro", 12, 0.f, 0.f, 66.f, 47.f);

	// 크리스 아이템
	CreateAnimation("KrisItem");
	SetAnimationTextureType("KrisItem", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_item/spr_krisb_item_ch1_0.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_item/spr_krisb_item_ch1_1.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_item/spr_krisb_item_ch1_2.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_item/spr_krisb_item_ch1_3.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_item/spr_krisb_item_ch1_4.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_item/spr_krisb_item_ch1_5.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_item/spr_krisb_item_ch1_6.png"));

	SetTexture("KrisItem", "KrisItem", FileNames);
	AddFrameCount("KrisItem", 7, 0.f, 0.f, 63.f, 44.f);

	// 크리스 디펜스
	CreateAnimation("KrisDefend");
	SetAnimationTextureType("KrisDefend", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_defend/spr_krisb_defend_0.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_defend/spr_krisb_defend_1.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_defend/spr_krisb_defend_2.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_defend/spr_krisb_defend_3.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_defend/spr_krisb_defend_4.png"));
	FileNames.emplace_back(TEXT("Texture/Kris/spr_krisb_defend/spr_krisb_defend_5.png"));

	SetTexture("KrisDefend", "KrisDefend", FileNames);
	AddFrameCount("KrisDefend", 6, 0.f, 0.f, 35.f, 40.f);


	// 크리스 공격 이펙트
	CreateAnimation("AttackEffect");
	SetAnimationTextureType("AttackEffect", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_0.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_1.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_2.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_3.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_4.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_5.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_6.png"));
	FileNames.emplace_back(TEXT("Texture/Player/spr_attack_slap1/spr_attack_slap1_7.png"));

	SetTexture("AttackEffect", "AttackEffect", FileNames);
	AddFrameCount("AttackEffect", 8, 0.f, 0.f, 44.f, 45.f);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// 수지 오른쪽 이동
	CreateAnimation("SusieWalkRight");
	SetAnimationTextureType("SusieWalkRight", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susier_dark/spr_susier_dark_0.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susier_dark/spr_susier_dark_1.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susier_dark/spr_susier_dark_2.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susier_dark/spr_susier_dark_3.png"));

	SetTexture("SusieWalkRight", "SusieWalkRight", FileNames);
	AddFrameCount("SusieWalkRight", 4, 0.f, 0.f, 25.f, 46.f);

	// 수지 왼쪽 이동
	CreateAnimation("SusieWalkLeft");
	SetAnimationTextureType("SusieWalkLeft", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susiel_dark/spr_susiel_dark_0.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susiel_dark/spr_susiel_dark_1.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susiel_dark/spr_susiel_dark_2.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susiel_dark/spr_susiel_dark_3.png"));

	SetTexture("SusieWalkLeft", "SusieWalkLeft", FileNames);
	AddFrameCount("SusieWalkLeft", 4, 0.f, 0.f, 25.f, 46.f);

	// 수지 위로 이동
	CreateAnimation("SusieWalkUp");
	SetAnimationTextureType("SusieWalkUp", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieu_dark/spr_susieu_dark_0.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieu_dark/spr_susieu_dark_1.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieu_dark/spr_susieu_dark_2.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieu_dark/spr_susieu_dark_3.png"));

	SetTexture("SusieWalkUp", "SusieWalkUp", FileNames);
	AddFrameCount("SusieWalkUp", 4, 0.f, 0.f, 26.f, 46.f);

	// 수지 아래로 이동
	CreateAnimation("SusieWalkDown");
	SetAnimationTextureType("SusieWalkDown", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susied_dark/spr_susied_dark_0.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susied_dark/spr_susied_dark_1.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susied_dark/spr_susied_dark_2.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susied_dark/spr_susied_dark_3.png"));

	SetTexture("SusieWalkDown", "SusieWalkDown", FileNames);
	AddFrameCount("SusieWalkDown", 4, 0.f, 0.f, 26.f, 46.f);

	// 수지 공격
	CreateAnimation("SusieAttack");
	SetAnimationTextureType("SusieAttack", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_attack/spr_susieb_attack_0.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_attack/spr_susieb_attack_1.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_attack/spr_susieb_attack_2.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_attack/spr_susieb_attack_3.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_attack/spr_susieb_attack_4.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_attack/spr_susieb_attack_5.png"));

	SetTexture("SusieAttack", "SusieAttack", FileNames);
	AddFrameCount("SusieAttack", 6, 0.f, 0.f, 125.f, 80.f);

	// 수지 아이템
	CreateAnimation("SusieAct");
	SetAnimationTextureType("SusieAct", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_act/spr_susieb_act_0.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_act/spr_susieb_act_1.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_act/spr_susieb_act_2.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_act/spr_susieb_act_3.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_act/spr_susieb_act_4.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_act/spr_susieb_act_5.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_act/spr_susieb_act_6.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_act/spr_susieb_act_7.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_act/spr_susieb_act_8.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_act/spr_susieb_act_9.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_act/spr_susieb_act_10.png"));

	SetTexture("SusieAct", "SusieAct", FileNames);
	AddFrameCount("SusieAct", 11, 0.f, 0.f, 125.f, 80.f);

	// 수지 Idle
	CreateAnimation("SusieIdle");
	SetAnimationTextureType("SusieIdle", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_idle/spr_susieb_idle_0.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_idle/spr_susieb_idle_1.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_idle/spr_susieb_idle_2.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_idle/spr_susieb_idle_3.png"));

	SetTexture("SusieIdle", "SusieIdle", FileNames);
	AddFrameCount("SusieIdle", 4, 0.f, 0.f, 125.f, 80.f);

	// 수지 디펜드
	CreateAnimation("SusieDefend");
	SetAnimationTextureType("SusieDefend", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_defend/spr_susieb_defend_0.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_defend/spr_susieb_defend_1.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_defend/spr_susieb_defend_2.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_defend/spr_susieb_defend_3.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_defend/spr_susieb_defend_4.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susieb_defend/spr_susieb_defend_5.png"));

	SetTexture("SusieDefend", "SusieDefend", FileNames);
	AddFrameCount("SusieDefend", 6, 0.f, 0.f, 125.f, 80.f);

	// 수지 루드버스터
	CreateAnimation("SusieRudeBuster");
	SetAnimationTextureType("SusieRudeBuster", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_0.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_1.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_2.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_3.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_4.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_5.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_6.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_7.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_8.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_9.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_10.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_11.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_12.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_13.png"));
	FileNames.emplace_back(TEXT("Texture/Susie/spr_susie_rudebuster/spr_susie_rudebuster_14.png"));

	SetTexture("SusieRudeBuster", "SusieRudeBuster", FileNames);
	AddFrameCount("SusieRudeBuster", 15, 0.f, 0.f, 123.f, 79.f);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// 랄세이 오른쪽 이동
	CreateAnimation("RalseiWalkRight");
	SetAnimationTextureType("RalseiWalkRight", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseir/spr_ralseir_0.png"));
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseir/spr_ralseir_1.png"));
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseir/spr_ralseir_2.png"));
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseir/spr_ralseir_3.png"));

	SetTexture("RalseiWalkRight", "RalseiWalkRight", FileNames);
	AddFrameCount("RalseiWalkRight", 4, 0.f, 0.f, 23.f, 44.f);

	// 랄세이 왼쪽 이동
	CreateAnimation("RalseiWalkLeft");
	SetAnimationTextureType("RalseiWalkLeft", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseil/spr_ralseil_0.png"));
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseil/spr_ralseil_1.png"));
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseil/spr_ralseil_2.png"));
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseil/spr_ralseil_3.png"));
														   
	SetTexture("RalseiWalkLeft", "RalseiWalkLeft", FileNames);
	AddFrameCount("RalseiWalkLeft", 4, 0.f, 0.f, 23.f, 44.f);

	// 랄세이 위로 이동
	CreateAnimation("RalseiWalkUp");
	SetAnimationTextureType("RalseiWalkUp", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseiu/spr_ralseiu_0.png"));
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseiu/spr_ralseiu_1.png"));
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseiu/spr_ralseiu_2.png"));
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseiu/spr_ralseiu_3.png"));

	SetTexture("RalseiWalkUp", "RalseiWalkUp", FileNames);
	AddFrameCount("RalseiWalkUp", 4, 0.f, 0.f, 23.f, 44.f);

	// 랄세이 아래로 이동
	CreateAnimation("RalseiWalkDown");
	SetAnimationTextureType("RalseiWalkDown", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseid/spr_ralseid_0.png"));
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseid/spr_ralseid_1.png"));
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseid/spr_ralseid_2.png"));
	FileNames.emplace_back(TEXT("Texture/Ralsei/spr_ralseid/spr_ralseid_3.png"));

	SetTexture("RalseiWalkDown", "RalseiWalkDown", FileNames);
	AddFrameCount("RalseiWalkDown", 4, 0.f, 0.f, 23.f, 44.f);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// 제빌 메인
	CreateAnimation("JevilMain");
	SetAnimationTextureType("JevilMain", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_main/spr_joker_main_0.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_main/spr_joker_main_1.png"));

	SetTexture("JevilMain", "JevilMain", FileNames);
	AddFrameCount("JevilMain", 2, 0.f, 0.f, 42.f, 41.f);

	// 제빌 댄스
	CreateAnimation("JevilDance");
	SetAnimationTextureType("JevilDance", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_ch1/spr_joker_dance_ch1_0.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_ch1/spr_joker_dance_ch1_1.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_ch1/spr_joker_dance_ch1_2.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_ch1/spr_joker_dance_ch1_3.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_ch1/spr_joker_dance_ch1_4.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_ch1/spr_joker_dance_ch1_5.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_ch1/spr_joker_dance_ch1_6.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_ch1/spr_joker_dance_ch1_7.png"));

	SetTexture("JevilDance", "JevilDance", FileNames);
	AddFrameCount("JevilDance", 8, 0.f, 0.f, 46.f, 48.f);

	// 제빌 댄스 리버스
	CreateAnimation("JevilDanceReverse");
	SetAnimationTextureType("JevilDanceReverse", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_reverse_ch1/spr_joker_dance_reverse_ch1_0.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_reverse_ch1/spr_joker_dance_reverse_ch1_1.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_reverse_ch1/spr_joker_dance_reverse_ch1_2.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_reverse_ch1/spr_joker_dance_reverse_ch1_3.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_reverse_ch1/spr_joker_dance_reverse_ch1_4.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_reverse_ch1/spr_joker_dance_reverse_ch1_5.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_reverse_ch1/spr_joker_dance_reverse_ch1_6.png"));
	FileNames.emplace_back(TEXT("Texture/Jevil/spr_joker_dance_reverse_ch1/spr_joker_dance_reverse_ch1_7.png"));

	SetTexture("JevilDanceReverse", "JevilDanceReverse", FileNames);
	AddFrameCount("JevilDanceReverse", 8, 0.f, 0.f, 46.f, 48.f);

	// 제빌 배경
	CreateAnimation("JevilCarousel");
	SetAnimationTextureType("JevilCarousel", EAnimationTextureType::Frame);
	FileNames.clear();

	TCHAR Path[200][MAX_PATH] = {};
	for (int i = 1; i <= 200; ++i)
	{
		wsprintf(Path[i - 1], TEXT("Texture/Jevil/jevilBG2/JevilBG (%d).png"), i);
		FileNames.emplace_back(Path[i - 1]);
	}
	
	SetTexture("JevilCarousel", "JevilCarousel", FileNames);
	AddFrameCount("JevilCarousel", 200, 0.f, 0.f, 1418, 1080.f);

	// 제빌 클로버 폭탄
	CreateAnimation("ClubBoom");
	SetAnimationTextureType("ClubBoom", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/spr_bomb_club_ch1_0.png"));
	FileNames.emplace_back(TEXT("Texture/spr_bomb_club_ch1_1.png"));

	SetTexture("ClubBoom", "ClubBoom", FileNames);
	AddFrameCount("ClubBoom", 2, 0.f, 0.f, 23.f, 23.f);

	// 제빌 폭탄 터지는 효과
	CreateAnimation("Boom");
	SetAnimationTextureType("Boom", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture/Boom/Boom6.png"));
	FileNames.emplace_back(TEXT("Texture/Boom/Boom5.png"));
	FileNames.emplace_back(TEXT("Texture/Boom/Boom4.png"));
	FileNames.emplace_back(TEXT("Texture/Boom/Boom3.png"));
	FileNames.emplace_back(TEXT("Texture/Boom/Boom2.png"));
	FileNames.emplace_back(TEXT("Texture/Boom/Boom1.png"));

	SetTexture("Boom", "Boom", FileNames);
	AddFrameCount("Boom", 6, 0.f, 0.f, 75.f, 76.f);

	// 전투 외곽 테스트
	CreateAnimation("BattleFrame");
	SetAnimationTextureType("BattleFrame", EAnimationTextureType::Frame);
	FileNames.clear();

	TCHAR Path2[100][MAX_PATH] = {};
	for (int i = 1; i <= 100; ++i)
	{
		wsprintf(Path2[i - 1], TEXT("Texture/UI/BattleBGFrames/BattleFrame (%d).png"), i);
		FileNames.emplace_back(Path2[i - 1]);
	}

	SetTexture("BattleFrame", "BattleFrame", FileNames);
	AddFrameCount("BattleFrame", 100, 0.f, 0.f, 1280.f, 960.f);

	// 전투 박스 테스트
	CreateAnimation("BattleBoxStart");
	SetAnimationTextureType("BattleBoxStart", EAnimationTextureType::Frame);
	FileNames.clear();

	TCHAR Path3[18][MAX_PATH] = {};
	for (int i = 1; i <= 18; ++i)
	{
		wsprintf(Path3[i - 1], TEXT("Texture/UI/BATTLE_BOX_SEQUENCE/BatttleBox (%d).png"), i);
		FileNames.emplace_back(Path3[i - 1]);
	}

	SetTexture("BattleBoxStart", "BattleBoxStart", FileNames);
	AddFrameCount("BattleBoxStart", 18, 0.f, 0.f, 1280.f, 960.f);

	return true;
}

bool CAnimation2DManager::CreateAnimation(const std::string& Name)
{
	// 생성해야하는데 같은 이름이 있으면 false
	if (FindAnimation(Name))
	{
		return false;
	}

	CAnimation2DData* Animation = new CAnimation2DData;

	Animation->SetName(Name);

	mAnimationMap.insert(std::make_pair(Name, Animation));

	return true;
}

class CAnimation2DData* CAnimation2DManager::FindAnimation(const std::string& Name)
{
	auto iter = mAnimationMap.find(Name);

	if (iter == mAnimationMap.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CAnimation2DManager::ReleaseAnimation(class CAsset* Animation)
{
	auto iter = mAnimationMap.find(Animation->GetName());

	if (iter != mAnimationMap.end())
	{
		mAnimationMap.erase(iter);
	}
}

bool CAnimation2DManager::SetAnimationTextureType(const std::string& Name, EAnimationTextureType Type)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}
	
	Animation->SetAnimationTextureType(Type);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, class CTexture* Texture)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(Texture);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, const std::string& TextureName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(TextureName);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, const std::string& TextureName, const TCHAR* FileName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(TextureName, FileName);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, const std::string& TextureName, std::vector<const TCHAR*> FileName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(TextureName, FileName);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, const std::string& TextureName, const TCHAR* FileName, const TCHAR* Ext, int Count)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(TextureName, FileName, Ext, Count);

	return true;
}

bool CAnimation2DManager::SetTextureFullPath(const std::string& Name, const std::string& TextureName, const TCHAR* FullPath)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTextureFullPath(TextureName, FullPath);

	return true;
}

bool CAnimation2DManager::SetTextureFullPath(const std::string& Name, const std::string& TextureName, const std::vector<const TCHAR*>& FullPath)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTextureFullPath(TextureName, FullPath);

	return true;
}

// 프레임 설정
bool CAnimation2DManager::AddFrame(const std::string& Name, const FVector2D& Start, const FVector2D& Size)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->AddFrame(Start, Size);

	return true;
}

bool CAnimation2DManager::AddFrame(const std::string& Name, float StartX, float StartY, float SizeX, float SizeY)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->AddFrame(StartX, StartY, SizeX, SizeY);

	return true;
}

bool CAnimation2DManager::AddFrameCount(const std::string& Name, int Count, const FVector2D& Start, const FVector2D& Size)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->AddFrameCount(Count, Start, Size);

	return true;
}

bool CAnimation2DManager::AddFrameCount(const std::string& Name, int Count, float StartX, float StartY, float SizeX, float SizeY)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->AddFrameCount(Count, StartX, StartY, SizeX, SizeY);

	return true;
}