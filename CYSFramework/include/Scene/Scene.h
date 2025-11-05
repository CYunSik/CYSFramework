#pragma once

#include "../GameInfo.h"

#include "../Share/SharedPtr.h"  // CSharedPtr 템플릿 인식

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
	// 카메라 매니저
	class CCameraManager* mCameraManager = nullptr;

	// 충돌
	class CSceneCollision* mCollision = nullptr;

	// 오브젝트
	// 리스트로 관리 : 중간 삽입 삭제가 용이하기 때문
	std::list<CSharedPtr<class CSceneObject>> mObjList;

	bool mDebugQuadTree = true;

public:
	class CInput* GetInput() const
	{
		return mInput;
	}

	class CCameraManager* GetCameraManager() const
	{
		return mCameraManager;
	}

	class CSceneCollision* GetCollision() const
	{
		return mCollision;
	}

	const std::list<CSharedPtr<CSceneObject>>& GetObjectList() const
	{
		return mObjList;
	}

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

	template<typename T>
	void FindObjectsFromType(std::list<CSharedPtr<T>>& result)
	{
		auto iter = mObjList.begin();
		auto iterEnd = mObjList.end();

		for (; iter != iterEnd; ++iter)
		{
			T* Obj = dynamic_cast<T*>((*iter).Get());

			if (Obj)
			{
				result.push_back(Obj);
			}
		}
	}
};

