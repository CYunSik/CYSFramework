#include "SceneMain.h"
#include "../Object/PlayerObject.h"
#include "../Object/MonsterObject.h"

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

	CMonsterObject* Monster = CreateObj<CMonsterObject>("Monster");
	Monster->SetWorldPos(-400.f, 300.f);
	Monster->SetTarget(Player);

	CMonsterObject* Monster1 = CreateObj<CMonsterObject>("Monster");
	Monster1->SetWorldPos(400.f, 300.f);
	Monster1->SetTarget(Player);

	return true;
}