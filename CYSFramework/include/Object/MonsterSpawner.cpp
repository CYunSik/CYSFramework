#include "MonsterSpawner.h"
#include "../Component/StaticMeshComponent.h"
#include "../Object/PlayerObject.h"
#include "../Object/MonsterObject.h"
#include "../Object/GunnerMonster.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneMain.h"

CMonsterSpawner::CMonsterSpawner()
{
}

CMonsterSpawner::CMonsterSpawner(const CMonsterSpawner& Obj)
	: CSceneObject(Obj)
{
}

CMonsterSpawner::CMonsterSpawner(CMonsterSpawner&& Obj)
	: CSceneObject(Obj)
{
}

CMonsterSpawner::~CMonsterSpawner()
{
}

bool CMonsterSpawner::Init()
{
	if (!CSceneObject::Init())
	{
		return false;
	}

	mRoot = CreateComponent<CStaticMeshComponent>();
	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");
	mRoot->SetWorldScale(0.f, 0.f);

	SetRootComponent(mRoot);

	return true;
}

void CMonsterSpawner::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	mTimeAcc += DeltaTime;

	// 씬에서 몬스터들 리스트로 찾기
	std::list<CSharedPtr<CMonsterObject>> MonsterList;
	mScene->FindObjectsFromType<CMonsterObject>(MonsterList);

	// 5번만 생성
	if (mSpawnCount < 5)
	{
		// 몬스터가 한마리도 없을 때만 새로 생성
		if (MonsterList.empty())
		{
			if (mTimeAcc >= mTime)
			{
				// 한번에 3마리 생성
				for (int i = 0; i < 3; ++i)
				{
					// 랜덤 좌표
					float RandX = static_cast<float>((rand() % 1000) - 500);
					float RandY = static_cast<float>((rand() % 600) - 300);

					// 몬스터 생성
					CGunnerMonster* Monster = mScene->CreateObj<CGunnerMonster>("GunnerMonster");
					Monster->SetWorldPos(RandX, RandY);
					if (mTarget)
					{
						Monster->SetTarget(mTarget.Get());
					}
				}

				// 타이머 초기화
				mTimeAcc = 0.f;
				++mSpawnCount;
			}
		}
	}
}