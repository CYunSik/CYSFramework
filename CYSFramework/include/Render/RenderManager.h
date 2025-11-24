#pragma once

#include "../GameInfo.h"

class CRenderManager
{
	DECLARE_SINGLETON(CRenderManager);

private:
	class CRenderStateManager* mStateManager = nullptr;

	// Render할 SceneComponent를 모아둘 것이다.
	std::list<CSharedPtr<class CSceneComponent>> mRenderList;

	// 정렬타입
	ERenderSortType mRenderSortType = ERenderSortType::Y;

public:
	class CRenderStateManager* GetStateManager()
	{
		return mStateManager;
	}

	// RenderList 등록함수
	void AddRenderList(class CSceneComponent* Component);
	void ClearRenderList();

public:
	bool Init();
	void Render();

private:
	static bool SortY(const CSharedPtr<class CSceneComponent>& Src, const CSharedPtr<class CSceneComponent>& Dest);
	static bool SortAlpha(const CSharedPtr<class CSceneComponent>& Src, const CSharedPtr<class CSceneComponent>& Dest);
};

