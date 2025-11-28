#include "SceneUIManager.h"

CSceneUIManager::CSceneUIManager()
{
}

CSceneUIManager::~CSceneUIManager()
{
}

void CSceneUIManager::AddToViewport(CWidget* Widget)
{
	mWidgetList.emplace_back(Widget);
}

bool CSceneUIManager::Init()
{
	return true;
}

void CSceneUIManager::Update(float DeltaTime)
{
	auto iter = mWidgetList.begin();
	auto iterEnd = mWidgetList.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mWidgetList.erase(iter);
			iterEnd = mWidgetList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Update(DeltaTime);
		++iter;
	}
}

void CSceneUIManager::Collision(float DeltaTime)
{
	// UI 충돌을 해줄것이다.
}

void CSceneUIManager::Render()
{
	// 그려줄 위젯 정렬
	if (mWidgetList.size() > 2)
	{
		// vector
		// Z오더는 숫자가 클수록 나중에 그려진다.
		// UI는 나중에 그려지는애가 가장 맨 위에 그려진다.
		std::sort(mWidgetList.begin(), mWidgetList.end(), &CSceneUIManager::SortRender); 
	}

	auto iter = mWidgetList.begin();
	auto iterEnd = mWidgetList.end();

	for (; iter != iterEnd;)
	{
		// Active
		if (!(*iter)->IsActive())
		{
			iter = mWidgetList.erase(iter);
			iterEnd = mWidgetList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		// UI 그려줘
		(*iter)->Render();
		++iter;
	}

	iter = mWidgetList.begin();
	iterEnd = mWidgetList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->EndFrame();
	}
}

bool CSceneUIManager::SortRender(const CSharedPtr<CWidget>& Src, const CSharedPtr<CWidget>& Dest)
{
	// 내림차순
	return Src->GetZOrder() > Dest->GetZOrder();
}
