#include "SceneMain.h"
#include "../Object/PlayerObject.h"
#include "../Object/MonsterObject.h"
#include "../Object/GunnerMonster.h"
#include "../Object/NearingMonster.h"
#include "../Object/MonsterSpawner.h"
#include "../Object/ObjectSpawnPoint.h"

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

	CPlayerObject* Player = CreateObj<CPlayerObject>("Player");

	if (Player == nullptr)
	{
		return false;
	}

	CObjectSpawnPoint* MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint1");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
	MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::CountDestroy);
	MonsterPoint->SetDestroySpawnCount(3);
	MonsterPoint->SetWorldPos(400.f, 300.f);

	MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint2");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::CountDestroy);
	MonsterPoint->SetImmediateSpawn(false);
	MonsterPoint->SetSpawnTime(5.f);
	MonsterPoint->SetDestroySpawnCount(3);
	MonsterPoint->SetWorldPos(-400.f, 300.f);

	MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint3");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetImmediateSpawn(false);
	MonsterPoint->SetSpawnTime(5.f);
	MonsterPoint->SetWorldPos(400.f, -300.f);

	MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint4");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetImmediateSpawn(false);
	MonsterPoint->SetSpawnTime(3.5f);
	MonsterPoint->SetWorldPos(-400.f, -300.f);

	MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint5");
	MonsterPoint->SetSpawnType(EObjectSpawnType::NearingMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetImmediateSpawn(true);
	MonsterPoint->SetSpawnTime(10.f);
	MonsterPoint->SetWorldPos(200.f, 0.f);

	//CGunnerMonster* Monster = CreateObj<CGunnerMonster>("GunnerMonster1");
	//Monster->SetWorldPos(-500.f, 300.f);
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