#pragma once
#include "SceneObject.h"

class CPlayerObject : public CSceneObject
{
	friend class CScene;

protected:
	CPlayerObject();
	CPlayerObject(const CPlayerObject& Obj);
	CPlayerObject(CPlayerObject&& Obj);
	virtual ~CPlayerObject();

protected:
	CSharedPtr<class CStaticMeshComponent> mRoot;
	CSharedPtr<class CSceneComponent> mRotationPivot;
	CSharedPtr<class CStaticMeshComponent> mSub;
	// 위성 반대편 방향에 하나더 출력
	CSharedPtr<class CStaticMeshComponent> mSub2;

	// 총알용 오브젝트
	// 스킬 1
	CSharedPtr<class CBulletObject> mSkill1Object;

	// 스킬 3 : 위성에서 발사하기
	bool mSkill3Enable = false;
	float mSkill3Time = 3.f;		// 3초동안
	float mSkill3TimeAcc = 0.f;		// 시간 측정용
	float mSkill3Interval = 0.3f;	// 0.3초마다 총알을 발사

	// 스킬 4
	bool mSkill4Enable = false;
	float mSkill4Time = 6.f;
	float mSkill4TimeAcc = 0.f;

	// 스킬 5
	bool mSkill5Enable = false;
	float mSkill5Time = 6.f;
	float mSkill5TimeAcc = 0.f;
	std::vector<CBulletObject*> mSkill5Bullets;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);

	void RotationZ(float DeltaTime);
	void RotationZInv(float DeltaTime);

	void Fire(float DeltaTime);
	
	// 스킬
	void Skill1(float DeltaTime);
	void Skill1Fire(float DeltaTime);

	// 스킬 2 : 토네이도 샷
	void Skill2(float DeltaTime);

	// 스킬 3 : 위성 2개에서 각각 총알이 생성된다. 날아가는 방향은 플레이어 바라보는 방향
	void Skill3(float DeltaTime);
	void Skill3Update(float DeltaTime);

	// 스킬 4 : 돌아가는 위성의 범위를 늘렸다가 몇초후 다시 되돌아오기, 가능하면 위성의 속도도 늘렸다가 줄이기
	void Skill4(float DeltaTime);
	void Skill4Update(float DeltaTime);

	// 스킬 5 : 롤 탈론 궁극기 만들기 (플레이어 기준으로 8방향으로 총알을 발사하고 해당 총알이 몇초 돌다가 플레이어에게 다시 되돌아오는 부메랑 기능)
	void Skill5(float DeltaTime);
	void Skill5Update(float DeltaTime);
};

