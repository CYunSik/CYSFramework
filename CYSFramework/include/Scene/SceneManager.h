#pragma once

#include "../GameInfo.h"

class CSceneManager
{
	DECLARE_SINGLETON(CSceneManager)

private:
	class CScene* mCurrentScene = nullptr;

public:
	bool Init();
	void Update(float DeltaTime);
	void Collision(float DeltaTime);
	void Render();

public:
	// 씬 만들기
	template<typename T>
	T* CreateScene()
	{
		T* Scene = new T;

		if (!Scene->Init())
		{
			SAFE_DELETE(Scene);
			return nullptr;
		}

		return Scene;
	}
};

