#include "SceneMain.h"

#include "SceneAssetManager.h"
#include "../Asset/Material/Material.h"
#include "../Object/PlayerObject.h"
#include "../Object/MonsterObject.h"
#include "../Object/GunnerMonster.h"
#include "../Object/NearingMonster.h"
#include "../Object/MonsterSpawner.h"
#include "../Object/ObjectSpawnPoint.h"
#include "../Object/BlockObject.h"
#include "../Object/BoomMonster.h"

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

	CObjectSpawnPoint* MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint1");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::CountDestroy);
	MonsterPoint->SetSpawnTime(5.f);
	MonsterPoint->SetDestroySpawnCount(3);
	MonsterPoint->SetWorldPos(400.f, 200.f);

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

	MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint5");
	MonsterPoint->SetSpawnType(EObjectSpawnType::NearingMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetImmediateSpawn(true);
	MonsterPoint->SetSpawnTime(10.f);
	MonsterPoint->SetWorldPos(200.f, 0.f);

	CBlockObject* Block = CreateObj<CBlockObject>("TestAnimation");
	Block->SetWorldPos(0.f, 0.f, 2.f);

	// 클로버 폭탄
	CBoomMonster* ClubMonster = CreateObj<CBoomMonster>("ClubMonster");
	ClubMonster->SetWorldPos(-200.f, 300.f);
	ClubMonster->SetDownTime(1.f);

	CBoomMonster* ClubMonster2 = CreateObj<CBoomMonster>("ClubMonster2");
	ClubMonster2->SetWorldPos(-350.f, 500.f);
	ClubMonster2->SetDownTime(1.5f);

	CBoomMonster* ClubMonster3 = CreateObj<CBoomMonster>("ClubMonster3");
	ClubMonster3->SetWorldPos(200.f, 400.f);
	ClubMonster3->SetDownTime(0.8f);

	CBoomMonster* ClubMonster4 = CreateObj<CBoomMonster>("ClubMonster4");
	ClubMonster4->SetWorldPos(350.f, 500.f);
	ClubMonster4->SetDownTime(2.f);

	CBoomMonster* ClubMonster5 = CreateObj<CBoomMonster>("ClubMonster5");
	ClubMonster5->SetWorldPos(400.f, 700.f);
	ClubMonster5->SetDownTime(3.f);

	CBoomMonster* ClubMonster6 = CreateObj<CBoomMonster>("ClubMonster6");
	ClubMonster6->SetWorldPos(350.f, 1000.f);
	ClubMonster6->SetDownTime(3.5f);

	CBoomMonster* ClubMonster7 = CreateObj<CBoomMonster>("ClubMonster7");
	ClubMonster7->SetWorldPos(400.f, 600.f);
	ClubMonster7->SetDownTime(1.7f);

	CBoomMonster* ClubMonster8 = CreateObj<CBoomMonster>("ClubMonster8");
	ClubMonster8->SetWorldPos(-200.f, 600.f);
	ClubMonster8->SetDownTime(1.3f);

	CBoomMonster* ClubMonster9 = CreateObj<CBoomMonster>("ClubMonster9");
	ClubMonster9->SetWorldPos(-400.f, 800.f);
	ClubMonster9->SetDownTime(2.2f);

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