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
	//CSharedPtr<class CStaticMeshComponent> mRoot;
	CSharedPtr<class CSpriteComponent> mRoot;
	CSharedPtr<class CColliderAABB2D> mBody;
	//CSharedPtr<class CColliderSphere2D> mBody;
	//CSharedPtr<class CColliderOBB2D> mBody;

	// 방향키로 움직일때 충돌여부
	bool mIsLeftCollision = false;
	bool mIsRightCollision = false;
	bool mIsUpCollision = false;
	bool mIsDownCollision = false;

	CSharedPtr<CSpriteComponent> mSusie;	// 수지
	CSharedPtr<CSpriteComponent> mRalsei;	// 랄세이

	// Trail
	std::vector<FVector3D> mPlayerTrail;
	std::vector<FVector3D> mSusieTrail;

	CSharedPtr<class CSceneComponent> mRotationPivot;
	CSharedPtr<class CSpriteComponent> mSub;
	// 위성 반대편 방향에 하나더 출력
	CSharedPtr<class CSpriteComponent> mSub2;

	// MovementComponent
	CSharedPtr<class CMovementComponent> mMovement;

	// RotationComponent
	CSharedPtr<class CRotationComponent> mRotation;

	// CameraComponent
	CSharedPtr<class CCameraComponent> mCamera;

	// 애니메이션
	class CAnimation2D* mAnimation = nullptr;
	class CAnimation2D* mAnimationSusie = nullptr;

	// Idle 상태값으로 돌아갈건지 여부
	bool mAutoBasePose = true;

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

	float mHp = 100.f;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	void Damage(float Damage);

	const std::vector<FVector3D>& GetTrail() const
	{
		return mPlayerTrail;
	}

private:
	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);
	void MoveLeft(float DeltaTime);
	void MoveRight(float DeltaTime);

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

	// 스킬 6 : 오버워치 자리야 궁 (MonsterObject 끌어당기기)
	void Skill6(float DeltaTime);

	// 스킬 7 : MonsterObject 모두 밀쳐내기
	void Skill7(float DeltaTime);

	// 스킬 8 : 지속데미지 총알
	void Skill8(float DeltaTime);

	// 스킬 9 : 관통 총알
	void Skill9(float DeltaTime);

	// 애니메이션 바인드 함수
	void AttackEnd();
	void AttackNotify();

	// 충돌 바인드 함수
	void OnCollisionBegin(const FVector3D& HitPoint, class CColliderBase* Dest);
	void OnCollisionEnd(class CColliderBase* Dest);
};
