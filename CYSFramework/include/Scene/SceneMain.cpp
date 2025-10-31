#include "SceneMain.h"
#include "../Object/PlayerObject.h"
#include "../Object/MonsterObject.h"
#include "../Object/GunnerMonster.h"
#include "../Object/NearingMonster.h"

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

	CGunnerMonster* Monster = CreateObj<CGunnerMonster>("GunnerMonster");
	Monster->SetWorldPos(-500.f, 300.f);
	Monster->SetTarget(Player);

	CNearingMonster* Monster2 = CreateObj<CNearingMonster>("NearingMonster");
	Monster2->SetWorldPos(500.f, 300.f);
	Monster2->SetTarget(Player);

	return true;
}