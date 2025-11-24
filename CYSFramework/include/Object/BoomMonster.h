#pragma once
#include "MonsterObject.h"

class CBoomMonster : public CMonsterObject
{
	friend class CScene;

protected:
	CBoomMonster();
	CBoomMonster(const CBoomMonster& Obj);
	CBoomMonster(CBoomMonster&& Obj);
	virtual ~CBoomMonster();

protected:
	float mDownTime = 0.f;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void SetDownTime(float Time)
	{
		mDownTime = Time;
	}
};

