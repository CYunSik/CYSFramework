#pragma once

#include "../GameInfo.h"

// 월드를 구상하는 클래스이다.
class CScene
{
	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene();

protected:
	// 입력
	class CInput* mInput = nullptr;


	// 오브젝트
	// 리스트로 관리 : 중간 삽입 삭제가 용이하기 때문
	std::list<CSharedPtr<class CSceneObject>> mObjList;


public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void Input(float DeletaTime);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

public:
	template<typename T>
	T* CreateObj(const std::string& Name)
	{
		T* Obj = new T;

		Obj->mScene = this;
		Obj->SetName(Name);

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}
		
		mObjList.push_back(Obj);
		return Obj;
	}
};

