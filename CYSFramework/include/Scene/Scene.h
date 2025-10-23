#pragma once

#include "../GameInfo.h"

// 월드를 구상하는 클래스이다.
class CScene
{
protected:
	CScene();
	virtual ~CScene();

protected:
	// 오브젝트
	// 리스트로 관리 : 중간 삽입 삭제가 용이하기 때문
	std::list<CSharedPtr<class CSceneObject>> mObjList;


public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();


};

