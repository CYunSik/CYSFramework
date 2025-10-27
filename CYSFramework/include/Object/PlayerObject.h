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
	float mSkill3Interval = 0.2f;	// 0.2초마다 총알을 발사

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
};

