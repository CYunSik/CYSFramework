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

void CSceneUIManager::Render()
{
}
