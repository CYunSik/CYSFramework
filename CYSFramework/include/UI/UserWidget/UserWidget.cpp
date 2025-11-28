#include "UserWidget.h"

CUserWidget::CUserWidget()
{
}

CUserWidget::~CUserWidget()
{
}

bool CUserWidget::Init()
{
	return CWidget::Init();
}

void CUserWidget::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);
}

void CUserWidget::Render()
{
	CWidget::Render();

	// 그려줄 위젯 정렬
	if (mWidgetList.size() > 2)
	{
		// vector
		// Z오더는 숫자가 클수록 나중에 그려진다.
		// UI는 나중에 그려지는애가 가장 맨 위에 그려진다.
		std::sort(mWidgetList.begin(), mWidgetList.end(), CUserWidget::SortRender);
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
}

bool CUserWidget::CollisionMouse(const FVector2D& MousePos)
{
	return CWidget::CollisionMouse(MousePos);
}

bool CUserWidget::SortRender(const CSharedPtr<CWidget>& Src, const CSharedPtr<CWidget>& Dest)
{
	return Src->GetZOrder() > Dest->GetZOrder();
}
