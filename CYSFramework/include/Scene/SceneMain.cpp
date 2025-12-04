#include "SceneMain.h"

#include "SceneAssetManager.h"
#include "SceneUIManager.h"
#include "../Asset/Material/Material.h"
#include "../Object/PlayerObject.h"
#include "../Object/MonsterObject.h"
#include "../Object/GunnerMonster.h"
#include "../Object/NearingMonster.h"
#include "../Object/MonsterSpawner.h"
#include "../Object/ObjectSpawnPoint.h"
#include "../Object/BlockObject.h"
#include "../Object/BoomMonster.h"
#include "../UI/UserWidget/MainWidget.h"
#include "../Component/SpriteComponent.h"
#include "../DeltaRune/JevilBossObject.h"
#include "../DeltaRune/JevilPrisonBG.h"

CSceneMain::CSceneMain()
{
}

CSceneMain::~CSceneMain()
{
}

bool CSceneMain::Init()
{
	if (!CScene::Init())
	{
		return false;
	}
	
	/////////////// 사용할 머티리얼 만들기
	mAssetManager->CreateMaterial("Spade1");

	CMaterial* Material = mAssetManager->FindMaterial("Spade1");
	Material->SetPixelShader("DefaultMaterialShader");
	Material->SetSamplerType(ETextureSamplerType::Linear);
	Material->AddTexture("Spade1", TEXT("Texture/spr_bomb_spade_ch1_0.png"), 0);

	mAssetManager->CreateMaterial("Spade2");

	CMaterial* Material7 = mAssetManager->FindMaterial("Spade2");
	Material7->SetPixelShader("DefaultMaterialShader");
	Material7->SetSamplerType(ETextureSamplerType::Linear);
	Material7->AddTexture("Spade2", TEXT("Texture/spr_bomb_spade_ch1_1.png"), 0);

	mAssetManager->CreateMaterial("Monster2");

	CMaterial* Material2 = mAssetManager->FindMaterial("Monster2");
	Material2->SetPixelShader("DefaultMaterialShader");
	Material2->SetSamplerType(ETextureSamplerType::Linear);
	Material2->AddTexture("Monster2", TEXT("Texture/spr_joker_teleport_r_ch1_1.png"), 0);

	// 제빌 스페이스 총알
	mAssetManager->CreateMaterial("Bullet1");

	CMaterial* Material3 = mAssetManager->FindMaterial("Bullet1");
	Material3->SetPixelShader("DefaultMaterialShader");
	Material3->SetSamplerType(ETextureSamplerType::Linear);
	Material3->AddTexture("Bullet1", TEXT("Texture/spr_spadebullet.png"), 0);

	// 제빌 다이아몬드 총알
	mAssetManager->CreateMaterial("Bullet2");

	CMaterial* Material4 = mAssetManager->FindMaterial("Bullet2");
	Material4->SetPixelShader("DefaultMaterialShader");
	Material4->SetSamplerType(ETextureSamplerType::Linear);
	Material4->AddTexture("Bullet2", TEXT("Texture/spr_diamondbullet_ch1.png"), 0);

	/////////////////// 사용할 사운드를 미리 추가한다.
	mAssetManager->LoadSound("Hit", "Effect", false, "Sound/snd_attack_sound.wav");


	// 전투 박스
	//mAssetManager->CreateMaterial("HitBox1");

	//CMaterial* Material5 = mAssetManager->FindMaterial("HitBox1");
	//Material5->SetPixelShader("DefaultMaterialShader");
	//Material5->SetSamplerType(ETextureSamplerType::Linear);
	//Material5->AddTexture("HitBox1", TEXT("Texture/spr_battlebg_stretch_hitbox_0.png"), 0);

	//mAssetManager->CreateMaterial("HitBox2");

	//CMaterial* Material6 = mAssetManager->FindMaterial("HitBox2");
	//Material6->SetPixelShader("DefaultMaterialShader");
	//Material6->SetSamplerType(ETextureSamplerType::Linear);
	//Material6->AddTexture("HitBox2", TEXT("Texture/spr_battlebg_stretch_hitbox_1.png"), 0);

	//////////////////////////////////////

	CPlayerObject* Player = CreateObj<CPlayerObject>("Player");

	if (Player == nullptr)
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////
	// 수지
	CSceneObject* Susie = CreateObj<CSceneObject>("Susie");
	CSpriteComponent* SusieSprite = Susie->CreateComponent<CSpriteComponent>();

	Susie->SetRootComponent(SusieSprite);
	Susie->SetWorldPos(0.f, 0.f, 0.f);
	Susie->SetWorldScale(45.f, 80.f, 1.f);

	//기본 텍스처
	SusieSprite->SetTexture("Susie_Idle", TEXT("Texture/Susie/spr_susier_dark/spr_susier_dark_0.png"));

	// 애니메이션
	CAnimation2D* SusieAnim = SusieSprite->CreateAnimation2D<CAnimation2D>();
	SusieAnim->AddSequence("SusieWalkLeft",  1.f, 1.f, true, false);
	SusieAnim->AddSequence("SusieWalkRight", 1.f, 1.f, true, false);
	SusieAnim->AddSequence("SusieWalkUp", 1.f, 1.f, true, false);
	SusieAnim->AddSequence("SusieWalkDown", 1.f, 1.f, true, false);

	Player->SetSusieObj(Susie);
	Player->SetSusieSprite(SusieSprite);
	Player->SetSusieAnimation(SusieAnim);

	//////////////////////////////////////////////////////////////////////////////////
	// 랄세이
	CSceneObject* Ralsei = CreateObj<CSceneObject>("Ralsei");
	CSpriteComponent* RalseiSprite = Ralsei->CreateComponent<CSpriteComponent>();

	Ralsei->SetRootComponent(RalseiSprite);
	Ralsei->SetWorldPos(0.f, 0.f, 0.f);
	Ralsei->SetWorldScale(45.f, 80.f, 1.f);

	// 기본
	RalseiSprite->SetTexture("Ralsei_Idle", TEXT("Texture/Ralsei/spr_ralseir/spr_ralseir_0.png"));

	// 애니메이션
	CAnimation2D* RalseiAnim = RalseiSprite->CreateAnimation2D<CAnimation2D>();
	RalseiAnim->AddSequence("RalseiWalkLeft", 1.f, 1.f, true, false);
	RalseiAnim->AddSequence("RalseiWalkRight", 1.f, 1.f, true, false);
	RalseiAnim->AddSequence("RalseiWalkUp", 1.f, 1.f, true, false);
	RalseiAnim->AddSequence("RalseiWalkDown", 1.f, 1.f, true, false);

	Player->SetRalseiObj(Ralsei);
	Player->SetRalseiSprite(RalseiSprite);
	Player->SetRalseiAnimation(RalseiAnim);
	//////////////////////////////////////////////////////////////////////////////////

	CObjectSpawnPoint* MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint1");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::Loop);
	MonsterPoint->SetSpawnTime(6.f);
	MonsterPoint->SetImmediateSpawn(true);
	//MonsterPoint->SetDestroySpawnCount(3);
	MonsterPoint->SetWorldPos(400.f, 300.f);

	//MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint2");
	//MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	//MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	//MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::CountDestroy);
	//MonsterPoint->SetImmediateSpawn(true);
	//MonsterPoint->SetSpawnTime(5.f);
	//MonsterPoint->SetDestroySpawnCount(3);
	//MonsterPoint->SetWorldPos(-400.f, 200.f);

	//MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint3");
	//MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	//MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	//MonsterPoint->SetImmediateSpawn(true);
	//MonsterPoint->SetSpawnTime(5.f);
	//MonsterPoint->SetWorldPos(400.f, -200.f);

	//MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint4");
	//MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	//MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	//MonsterPoint->SetImmediateSpawn(true);
	//MonsterPoint->SetSpawnTime(3.5f);
	//MonsterPoint->SetWorldPos(-400.f, -200.f);

	//MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint5");
	//MonsterPoint->SetSpawnType(EObjectSpawnType::NearingMonster);
	//MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	//MonsterPoint->SetImmediateSpawn(true);
	//MonsterPoint->SetSpawnTime(10.f);
	//MonsterPoint->SetWorldPos(200.f, 0.f);

	///////////////////////////////////////////
	// UI 생성
	CMainWidget* Widget = mUIManager->CreateWidget<CMainWidget>("Main");
	mUIManager->AddToViewport(Widget);



	///////////////////////////////////////////
	// 제빌 테스트
	CJevilBossObject* Jevil = CreateObj<CJevilBossObject>("Jevil");
	Jevil->SetWorldPos(500.f, -100.f, 1.f);
	
	// 제빌 감옥 배경
	CJevilPrisonBG* BackGround = CreateObj<CJevilPrisonBG>("JevilPrisionBG");
	BackGround->SetWorldPos(720.f, -390.f, 3.f);

	// 테스트용 배경
	//CBlockObject* Block = CreateObj<CBlockObject>("TestAnimation");
	//Block->SetWorldPos(0.f, 200.f, 5.f);

	// 클로버 폭탄
	//CBoomMonster* ClubMonster = CreateObj<CBoomMonster>("ClubMonster");
	//ClubMonster->SetWorldPos(-200.f, 300.f);
	//ClubMonster->SetDownTime(1.f);

	//CBoomMonster* ClubMonster2 = CreateObj<CBoomMonster>("ClubMonster2");
	//ClubMonster2->SetWorldPos(-350.f, 500.f);
	//ClubMonster2->SetDownTime(1.5f);

	//CBoomMonster* ClubMonster3 = CreateObj<CBoomMonster>("ClubMonster3");
	//ClubMonster3->SetWorldPos(200.f, 400.f);
	//ClubMonster3->SetDownTime(0.8f);

	//CBoomMonster* ClubMonster4 = CreateObj<CBoomMonster>("ClubMonster4");
	//ClubMonster4->SetWorldPos(350.f, 500.f);
	//ClubMonster4->SetDownTime(2.f);

	//CBoomMonster* ClubMonster5 = CreateObj<CBoomMonster>("ClubMonster5");
	//ClubMonster5->SetWorldPos(400.f, 700.f);
	//ClubMonster5->SetDownTime(3.f);

	//CBoomMonster* ClubMonster6 = CreateObj<CBoomMonster>("ClubMonster6");
	//ClubMonster6->SetWorldPos(350.f, 1000.f);
	//ClubMonster6->SetDownTime(3.5f);

	//CBoomMonster* ClubMonster7 = CreateObj<CBoomMonster>("ClubMonster7");
	//ClubMonster7->SetWorldPos(400.f, 600.f);
	//ClubMonster7->SetDownTime(1.7f);

	//CBoomMonster* ClubMonster8 = CreateObj<CBoomMonster>("ClubMonster8");
	//ClubMonster8->SetWorldPos(-200.f, 600.f);
	//ClubMonster8->SetDownTime(1.3f);

	//CBoomMonster* ClubMonster9 = CreateObj<CBoomMonster>("ClubMonster9");
	//ClubMonster9->SetWorldPos(-400.f, 800.f);
	//ClubMonster9->SetDownTime(2.2f);

	// 관통 테스트
	//MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint6");
	//MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	//MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	//MonsterPoint->SetSpawnTime(5.f);
	//MonsterPoint->SetWorldPos(1000.f, 200.f);

	//MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint7");
	//MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	//MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	//MonsterPoint->SetSpawnTime(5.f);
	//MonsterPoint->SetWorldPos(1110.f, 200.f);

	//MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint8");
	//MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	//MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	//MonsterPoint->SetSpawnTime(5.f);
	//MonsterPoint->SetWorldPos(1210.f, 200.f);

	//CGunnerMonster* Monster = CreateObj<CGunnerMonster>("GunnerMonster1");
	//Monster->SetWorldPos(-400.f, 300.f);
	//Monster->SetTarget(Player);

	//CNearingMonster* Monster2 = CreateObj<CNearingMonster>("NearingMonster");
	//Monster2->SetWorldPos(500.f, 300.f);
	//Monster2->SetTarget(Player);

	//CGunnerMonster* Monster3 = CreateObj<CGunnerMonster>("GunnerMonster3");
	//Monster3->SetWorldPos(400.f, -300.f);
	//Monster3->SetTarget(Player);

	//CGunnerMonster* Monster4 = CreateObj<CGunnerMonster>("GunnerMonster4");
	//Monster4->SetWorldPos(0.f, -300.f);
	//Monster4->SetTarget(Player);



	//CMonsterSpawner* Spawner = CreateObj<CMonsterSpawner>("MonsterSpawner");
	//Spawner->SetWorldPos(0.f, 0.f);
	//Spawner->SetTarget(Player);

	return true;
}