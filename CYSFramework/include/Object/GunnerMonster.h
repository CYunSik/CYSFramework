#pragma once
#include "MonsterObject.h"

class CGunnerMonster : public CMonsterObject
{
	friend class CScene;

protected:
	CGunnerMonster();
	CGunnerMonster(const CGunnerMonster& Obj);
	CGunnerMonster(CGunnerMonster&& Obj);
	virtual ~CGunnerMonster();

protected:
	float mFireInterval = 0.f;
	float mFireTime = 2.f;
	int mFireCount = 0;

public:
	void SetFireInterval(float FireInterval)
	{
		mFireInterval = FireInterval;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

